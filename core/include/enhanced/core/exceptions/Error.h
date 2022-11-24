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
#include <enhanced/core/exceptions/Exception.h>

namespace enhanced::core::exceptions {
    class ENHANCED_CORE_API Error : public Exception {
    public:
        DEFINE_EXCEPTION_NAME(enhanced::core::exceptions::Error)

        explicit Error(const String& message = "") noexcept;

        explicit Error(const Exception* cause) noexcept;

        Error(const String& message, const Exception* cause) noexcept;
    };
}
