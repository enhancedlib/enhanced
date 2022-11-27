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

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/exceptions/Exception.h>

namespace enhanced::exceptions {
    class ENHANCED_CORE_API RuntimeException : public Exception {
    public:
        DEFINE_EXCEPTION_NAME(enhanced::exceptions::RuntimeException)

        explicit RuntimeException(const String& message = "") noexcept;

        explicit RuntimeException(const Exception* cause) noexcept;

        RuntimeException(const String& message, const Exception* cause) noexcept;
    };
}
