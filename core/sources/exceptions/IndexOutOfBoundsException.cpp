/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#include <enhanced/exceptions/IndexOutOfBoundsException.h>

#include <enhanced/exceptions/RuntimeException.h>

namespace enhanced::exceptions {
    IndexOutOfBoundsException::IndexOutOfBoundsException(const String& message) noexcept : RuntimeException(message) {}

    IndexOutOfBoundsException::IndexOutOfBoundsException(sizetype index, sizetype size) noexcept :
        RuntimeException(String::join("Index ", String::from(index), " out of bounds (size: ", String::from(size), ")")) {}
}
