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

#pragma once

#include <enhanced/core/defines.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/exception/Exception.h>

namespace enhanced::core::exception {
    class ENHANCED_CORE_API UnsupportedOperationException : public Exception {
    public:
        explicit UnsupportedOperationException(const String& message = "") noexcept;

        explicit UnsupportedOperationException(const Exception* cause) noexcept;

        UnsupportedOperationException(const String& message, const Exception* cause) noexcept;
    };
}

#define UNSUPPORTED_OPERATION() throw enhanced::core::exception::UnsupportedOperationException()
