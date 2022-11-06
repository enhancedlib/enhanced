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

#include <enhanced/core/exception/Exception.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/String.h>
#include <enhanced/core/exception/NotImplementedError.h>

using enhanced::core::exception::Exception;
using enhanced::core::String;

Exception::Exception(const String& message) noexcept : message((String&&) message), cause(null) {}

Exception::Exception(const Exception* cause) noexcept : message(""), cause(cause) {}

Exception::Exception(const String& message, const Exception* cause) noexcept : message((String&&) message), cause(cause) {}

Exception::~Exception() noexcept = default;

const String& Exception::getTraceback() const noexcept {
    return message;
}

const Exception* Exception::getCause() const noexcept {
    return cause;
}

const String& Exception::getMessage() const noexcept {
    return message;
}
