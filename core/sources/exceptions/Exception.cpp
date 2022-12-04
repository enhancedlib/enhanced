/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <exception>
#include <thread>

#include <enhanced/exceptions/Exception.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>
#include <enhanced/TypeInfo.h>
#include <enhanced/Process.h>
#include <enhanced/io/IOStream.h>
#include <enhanced/util/Traits.h>
#include <enhanced/exceptions/NotImplementedError.h>

using enhanced::util::move;
using enhanced::util::forceCast;
using enhanced::util::removeConst;
using enhanced::util::removeRefConst;
using enhanced::io::errstream;

namespace enhanced::exceptions {
    void defaultTerminateHandler() noexcept {
        try {
            std::rethrow_exception(std::current_exception());
        } catch (const Exception& exception) {
            exception.printTraceback();
        } catch (const std::exception& exception) {
            errstream->print("Exception [based on std::exception]: ");
            errstream->println(exception.what());
        } catch (...) {
            errstream->println("Exception [unknown]");
        }
        processAbort();
    }

    const TerminateHandler& setupTerminateHandler(const TerminateHandler& terminateHandler) noexcept {
        terminateHandlerFunc = terminateHandler;
        std::set_terminate(terminateHandler);
        return terminateHandler;
    }

    TerminateHandler terminateHandlerFunc = setupTerminateHandler(defaultTerminateHandler);

    Exception::Exception(const String& message) noexcept : message(move(message)), cause(nullptr) {}

    Exception::Exception(const Exception* cause) noexcept : message(""), cause(cause) {}

    Exception::Exception(const String& message, const Exception* cause) noexcept : message(move(message)), cause(cause) {}

    Exception::~Exception() noexcept = default;

    // TODO

    void Exception::printTraceback() const {
        errstream->println(getTraceback());
    }

    String Exception::getTraceback() const noexcept {
        return String::join({"Exception [", getName(), "]: ", message});
    }

    const Exception* Exception::getCause() const noexcept {
        return cause;
    }

    const String& Exception::getMessage() const noexcept {
        return message;
    }
}
