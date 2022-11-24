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

#include <enhanced/core/exceptions/Exception.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/String.h>
#include <enhanced/core/TypeInfo.h>
#include <enhanced/core/io/iostream.h>
#include <enhanced/core/util/traits.h>
#include <enhanced/core/exceptions/NotImplementedError.h>

using enhanced::core::util::move;
using enhanced::core::util::removeConst;
using enhanced::core::io::errstream;

namespace enhanced::core::exceptions {
    using TerminateHandler = void(*)();

    static void terminateHandler() {
        try {
            std::rethrow_exception(std::current_exception());
        } catch (const Exception& exception) {
            errstream->print(exception.getTraceback());
        } catch (const std::exception& exception) {
            errstream->print(String(removeConst(exception.what())));
        } catch (...) {}
    }

    static TerminateHandler setupTerminateHandler() noexcept {
        std::set_terminate(terminateHandler);
        return terminateHandler;
    }

    const TerminateHandler terminateHandlerFunc = setupTerminateHandler();

    Exception::Exception(const String& message) noexcept : message(move(message)), cause(null) {}

    Exception::Exception(const Exception* cause) noexcept : message(""), cause(cause) {}

    Exception::Exception(const String& message, const Exception* cause) noexcept : message(move(message)), cause(cause) {}

    Exception::~Exception() noexcept = default;

    String Exception::getTraceback() const noexcept {
        return String::join({getName(), ": ", message});
    }

    const Exception* Exception::getCause() const noexcept {
        return cause;
    }

    const String& Exception::getMessage() const noexcept {
        return message;
    }
}
