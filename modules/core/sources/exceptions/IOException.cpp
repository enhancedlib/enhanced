/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
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
