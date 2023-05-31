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

// Clang
#ifdef E_SM_COMPILER_CLANG
    #define E_CLANG_WARNING_DISABLE(ID) E_PRAGMA(clang diagnostic ignored ID)
    #define E_CLANG_WARNING_PUSH E_PRAGMA(clang diagnostic push)
    #define E_CLANG_WARNING_POP E_PRAGMA(clang diagnostic pop)
#else
    #define E_CLANG_WARNING_DISABLE(ID)
    #define E_CLANG_WARNING_PUSH
    #define E_CLANG_WARNING_POP
#endif

// MSVC
#ifdef E_SM_COMPILER_MSVC
    #define E_MSVC_WARNING_DISABLE(ID) E_PRAGMA(warning(disable: ID))
    #define E_MSVC_WARNING_PUSH E_PRAGMA(warning(push))
    #define E_MSVC_WARNING_POP E_PRAGMA(warning(pop))
#else
    #define E_MSVC_WARNING_DISABLE(ID)
    #define E_MSVC_WARNING_PUSH
    #define E_MSVC_WARNING_POP
#endif

// GCC
#ifdef E_SM_COMPILER_GCC
    #define E_GCC_WARNING_DISABLE(ID) E_PRAGMA(GCC diagnostic ignored ID)
    #define E_GCC_WARNING_PUSH E_PRAGMA(GCC diagnostic push)
    #define E_GCC_WARNING_POP E_PRAGMA(GCC diagnostic pop)
#else
    #define E_GCC_WARNING_DISABLE(ID)
    #define E_GCC_WARNING_PUSH
    #define E_GCC_WARNING_POP
#endif

#define E_CLANG_WARNING_PAD(ID) E_CLANG_WARNING_PUSH E_CLANG_WARNING_DISABLE(ID)
#define E_MSVC_WARNING_PAD(ID) E_MSVC_WARNING_PUSH E_MSVC_WARNING_DISABLE(ID)
#define E_GCC_WARNING_PAD(ID) E_GCC_WARNING_PUSH E_GCC_WARNING_DISABLE(ID)

// clang-tidy
#define E_CTIDY_NOLINT_ALL
#define E_CTIDY_NOLINT(...)
#define E_CTIDY_NOLINTNEXTLINE_ALL
#define E_CTIDY_NOLINTNEXTLINE(...)
#define E_CTIDY_NOLINTBEGIN_ALL
#define E_CTIDY_NOLINTBEGIN(...)
#define E_CTIDY_NOLINTEND_ALL
#define E_CTIDY_NOLINTEND(...)

#define E_ALLOW_DEPRECATED_BEGIN \
    E_CLANG_WARNING_PAD("-Wdeprecated") E_MSVC_WARNING_PAD(4996) E_GCC_WARNING_PAD("-Wdeprecated-declarations")
#define E_ALLOW_DEPRECATED_END E_CLANG_WARNING_POP E_MSVC_WARNING_POP E_GCC_WARNING_POP

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define CLANG_WARNING_DISABLE E_CLANG_WARNING_DISABLE
    #define CLANG_WARNING_PUSH E_CLANG_WARNING_PUSH
    #define CLANG_WARNING_POP E_CLANG_WARNING_POP
    #define CLANG_WARNING_PAD E_CLANG_WARNING_PAD

    #define MSVC_WARNING_DISABLE E_MSVC_WARNING_DISABLE
    #define MSVC_WARNING_PUSH E_MSVC_WARNING_PUSH
    #define MSVC_WARNING_POP E_MSVC_WARNING_POP
    #define MSVC_WARNING_PAD E_MSVC_WARNING_PAD

    #define GCC_WARNING_DISABLE E_GCC_WARNING_DISABLE
    #define GCC_WARNING_PUSH E_GCC_WARNING_PUSH
    #define GCC_WARNING_POP E_GCC_WARNING_POP
    #define GCC_WARNING_PAD E_GCC_WARNING_PAD

    #define CTIDY_NOLINT_ALL
    #define CTIDY_NOLINT(...)
    #define CTIDY_NOLINTNEXTLINE_ALL
    #define CTIDY_NOLINTNEXTLINE(...)
    #define CTIDY_NOLINTBEGIN_ALL
    #define CTIDY_NOLINTBEGIN(...)
    #define CTIDY_NOLINTEND_ALL
    #define CTIDY_NOLINTEND(...)

    #define ALLOW_DEPRECATED_BEGIN E_ALLOW_DEPRECATED_BEGIN
    #define ALLOW_DEPRECATED_END E_ALLOW_DEPRECATED_END
#endif