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

#include <enhanced/exceptions/IndexOutOfBoundsException.h>

#include <enhanced/exceptions/RuntimeException.h>

namespace enhanced::exceptions {
    IndexOutOfBoundsException::IndexOutOfBoundsException(const String& message) noexcept : RuntimeException(message) {}

    IndexOutOfBoundsException::IndexOutOfBoundsException(sizetype index, sizetype size) noexcept :
        RuntimeException(String {"Index ", String::from(index), " out of bounds (size: ", String::from(size), ")"}) {}
}
