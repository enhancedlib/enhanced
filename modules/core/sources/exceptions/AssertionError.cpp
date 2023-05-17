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

#include <enhanced/exceptions/AssertionError.h>


#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/exceptions/Error.h>

namespace enhanced::exceptions {
    AssertionError::AssertionError(const String& message) noexcept : Error(message) {}

    AssertionError::AssertionError(const String& expression, const String& file, sizetype line) noexcept :
        Error(String {"Failed to assert [", expression, "] at ", file, ":", String::from(line)}) {}

    AssertionError::AssertionError(const String& expression, const String& file, sizetype line, const String& message) noexcept :
        Error(String {"Failed to assert [", expression, "] at ", file, ":", String::from(line), ": ", message}) {}
}
