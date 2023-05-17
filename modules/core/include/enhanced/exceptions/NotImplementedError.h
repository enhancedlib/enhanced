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

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Warnings.h>
#include <enhanced/exceptions/AssertionError.h>

#define E_NOT_IMPLEMENTED throw enhanced::exceptions::NotImplementedError

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define NOT_IMPLEMENTED throw enhanced::exceptions::NotImplementedError
#endif

namespace enhanced::exceptions {
    class ENHANCED_CORE_API NotImplementedError : public AssertionError {
    public:
        E_DEFINE_EXCEPTION_NAME(enhanced::exceptions::NotImplementedError)

        explicit NotImplementedError(const String& message = "Not yet implemented") noexcept;
    };
}

// Disable the 'unused parameter' warning for not implemented functions.
CLANG_WARNING_DISABLE("-Wunused-parameter")
MSVC_WARNING_DISABLE(4100)
GCC_WARNING_DISABLE("-Wunused-parameter")
