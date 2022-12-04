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

#include <enhanced/exceptions/AssertionError.h>


#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/MutString.h>
#include <enhanced/exceptions/Error.h>

namespace enhanced::exceptions {
    AssertionError::AssertionError(const String& message) noexcept : Error(message) {}

    // TODO
    AssertionError::AssertionError(const enhanced::String& expression, const enhanced::String& file, sizetype line) noexcept :
        Error(String::join({"Failed to assert [", expression, "] at ", file, ":", String::from(line)})) {}
}
