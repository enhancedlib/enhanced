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

#include <enhanced/core/exceptions/IndexOutOfBoundsException.h>

#include <enhanced/core/exceptions/RuntimeException.h>

namespace enhanced::core::exceptions {
    IndexOutOfBoundsException::IndexOutOfBoundsException(const String& message) noexcept : RuntimeException(message) {}

    IndexOutOfBoundsException::IndexOutOfBoundsException(sizetype index, sizetype size) noexcept : RuntimeException("") {} // TODO
}