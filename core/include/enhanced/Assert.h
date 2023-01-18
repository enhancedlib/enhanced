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

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/exceptions/AssertionError.h>

// TODO: In the future, don't need to provide the current file and the current line for arguments
#define E_DYNAMIC_ASSERT(EXPRESSION, ...) \
    if (EXPRESSION) { \
        throw enhanced::exceptions::AssertionError(#EXPRESSION, CURRENT_FILE, CURRENT_LINE __VA_OPT__(,) __VA_ARGS__); \
    }

#if (defined(DEBUG) && !defined(ENHANCED_ASSERT_DISABLE)) || defined(ENHANCED_ASSERT_ENABLE)
    #define E_ASSERT(EXPRESSION, ...) E_DYNAMIC_ASSERT(EXPRESSION __VA_OPT__(,) __VA_ARGS__)
#else
    #define E_ASSERT(EXPRESSION, ...) (void) 0
#endif

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define DYNAMIC_ASSERT E_DYNAMIC_ASSERT
    #define ASSERT E_ASSERT
#endif

#if defined(COMPILER_GNU) || defined(COMPILER_CLANG)
    #define E_UNREACHABLE_CODE() __builtin_unreachable();
#elif defined(COMPILER_MSVC)
    #define E_UNREACHABLE_CODE() __assume(false);
#endif
