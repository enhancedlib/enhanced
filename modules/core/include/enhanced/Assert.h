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
#include <enhanced/String.h>
#include <enhanced/exceptions/AssertionError.h>

// TODO: In the future, don't need to provide the current file and the current line for arguments
#define E_DYNAMIC_ASSERT(EXPRESSION, ...) \
    if (EXPRESSION) { \
        throw enhanced::exceptions::AssertionError(#EXPRESSION, E_CURRENT_FILE, E_CURRENT_LINE, ##__VA_ARGS__); \
    }

#if (defined(E_SM_DEBUG) && !defined(E_SM_ASSERT_DISABLE)) || defined(E_SM_ASSERT_ENABLE)
    #define E_ASSERT(EXPRESSION, ...) E_DYNAMIC_ASSERT(EXPRESSION, ##__VA_ARGS__)
#else
    #define E_ASSERT(EXPRESSION, ...) (void) 0
#endif

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define DYNAMIC_ASSERT E_DYNAMIC_ASSERT
    #define ASSERT E_ASSERT
#endif

#if defined(E_SM_COMPILER_GCC) || defined(E_SM_COMPILER_CLANG)
    #define E_UNREACHABLE_CODE() __builtin_unreachable();
#elif defined(E_SM_COMPILER_MSVC)
    #define E_UNREACHABLE_CODE() __assume(false);
#endif
