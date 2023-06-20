/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <exception>

#include <enhanced/exceptions/Exception.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>
#include <enhanced/String.h>
#include <enhanced/TypeInfo.h>
#include <enhanced/Process.h>
#include <enhanced/io/IOStream.h>
#include <enhanced/exceptions/NotImplementedError.h>

using enhanced::move;
using enhanced::forceCast;
using enhanced::removeConst;
using enhanced::removeRefConst;
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
