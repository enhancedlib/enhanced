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

#include <enhanced/exceptions/IOException.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>

namespace enhanced::exceptions {
    IOException::IOException(const String& message) noexcept : Exception(message) {}

    IOException::IOException(const Exception* cause) noexcept : Exception(cause) {}

    IOException::IOException(const String& message, const Exception* cause) noexcept : Exception(message, cause) {}
}
