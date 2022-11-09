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

#include <enhanced/core/exception/IndexOutOfBoundsException.h>

#include <enhanced/core/exception/RuntimeException.h>

using enhanced::core::exception::IndexOutOfBoundsException;
using enhanced::core::exception::RuntimeException;

IndexOutOfBoundsException::IndexOutOfBoundsException(const String& message) noexcept : RuntimeException(message) {}

IndexOutOfBoundsException::IndexOutOfBoundsException(const Exception* cause) noexcept : RuntimeException(cause) {}

IndexOutOfBoundsException::IndexOutOfBoundsException(const String& message, const Exception* cause) noexcept : RuntimeException(message, cause) {}
