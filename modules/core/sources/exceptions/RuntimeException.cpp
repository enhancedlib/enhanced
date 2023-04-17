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

#include <enhanced/exceptions/RuntimeException.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>

namespace enhanced::exceptions {
    RuntimeException::RuntimeException(const String& message) noexcept : Exception(message) {}

    RuntimeException::RuntimeException(const Exception* cause) noexcept : Exception(cause) {}

    RuntimeException::RuntimeException(const String& message, const Exception* cause) noexcept : Exception(message, cause) {}
}
