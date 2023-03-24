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

#include <enhanced/exceptions/OperationException.h>

#include <enhanced/exceptions/Exception.h>

namespace enhanced::exceptions {
    OperationException::OperationException(const String& message) noexcept : Exception(message) {}

    OperationException::OperationException(const Exception* cause) noexcept : Exception(cause) {}

    OperationException::OperationException(const String& message, const Exception* cause) noexcept : Exception(message, cause) {}
}
