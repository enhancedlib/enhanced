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

#include <enhanced/exceptions/InvalidStateException.h>

#include <enhanced/exceptions/RuntimeException.h>

namespace enhanced::exceptions {
    InvalidStateException::InvalidStateException(const String& message) noexcept : RuntimeException(message) {}

    InvalidStateException::InvalidStateException(const Exception* cause) noexcept : RuntimeException(cause) {}

    InvalidStateException::InvalidStateException(const String& message, const Exception* cause) noexcept : RuntimeException(message, cause) {}
}
