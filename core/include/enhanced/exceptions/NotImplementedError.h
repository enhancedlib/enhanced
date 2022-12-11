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
#include <enhanced/Warnings.h>
#include <enhanced/exceptions/AssertionError.h>

namespace enhanced::exceptions {
    class ENHANCED_CORE_API NotImplementedError : public AssertionError {
    public:
        DEFINE_EXCEPTION_NAME(enhanced::exceptions::NotImplementedError)

        explicit NotImplementedError(const String& message = "Not yet implemented") noexcept;
    };
}

#define NOT_IMPLEMENTED throw enhanced::exceptions::NotImplementedError

// Disable the 'unused parameter' warning for not implemented functions.

CLANG_WARNING_DISABLE("-Wunused-parameter")
MSVC_WARNING_DISABLE(4100)
GCC_WARNING_DISABLE("-Wunused-parameter")
