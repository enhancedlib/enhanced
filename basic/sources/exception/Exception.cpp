/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/basic/exception/Exception.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"

#include "enhanced/basic/String.h"

using enhanced::basic::exception::Exception;
using enhanced::basic::String;

bool Exception::enableExceptions = true;
bool Exception::enableExceptionsTraceback = true;

Exception::Exception(String&& message) noexcept : message(message), cause(null) {
}

Exception::Exception(const Exception* cause) noexcept : message(""), cause(cause) {
}

Exception::Exception(String&& message, const Exception* cause) noexcept : message(message), cause(cause) {
}

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
