/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <exception>

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
using enhanced::io::eerr;

namespace enhanced::exceptions {
    void defaultExceptionHandler() noexcept {
        try {
            std::rethrow_exception(std::current_exception());
        } catch (const Exception& exception) {
            exception.printInfo();
        } catch (const std::exception& exception) {
            eerr.print("Exception [based on std::exception]: ");
            eerr.println(exception.what());
        } catch (...) {
            eerr.println("Exception [unknown]");
        }
    }

    const ExceptionHandler& setupExceptionHandler(const ExceptionHandler& handler) noexcept {
        exceptionHandler = handler;
        std::set_terminate(handler);
        return handler;
    }

    ExceptionHandler exceptionHandler = setupExceptionHandler(defaultExceptionHandler);

    Exception::Exception(const String& message) noexcept : message(move(message)), cause(nullptr) {}

    Exception::Exception(const Exception* cause) noexcept : message(""), cause(cause) {}

    Exception::Exception(const String& message, const Exception* cause) noexcept : message(move(message)), cause(cause) {}

    Exception::~Exception() noexcept = default;

    // TODO: Implementes for tracing exceptions

    void Exception::printInfo() const {
        eerr.println(getInfo());
    }

    String Exception::getInfo() const noexcept {
        return String {"Exception [", getName(), "]: ", message};
    }

    const Exception* Exception::getCause() const noexcept {
        return cause;
    }

    const String& Exception::getMessage() const noexcept {
        return message;
    }
}
