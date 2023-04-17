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

#pragma once

#include <enhanced/Defines.h>

// Clang
#ifdef COMPILER_CLANG
    #define CLANG_WARNING_PUSH PRAGMA(clang diagnostic push)
    #define CLANG_WARNING_DISABLE(ID) PRAGMA(clang diagnostic ignored ID)
    #define CLANG_WARNING_POP PRAGMA(clang diagnostic pop)
#else
    #define CLANG_WARNING_PUSH
    #define CLANG_WARNING_DISABLE(ID)
    #define CLANG_WARNING_POP
#endif

// MSVC
#ifdef COMPILER_MSVC
    #define MSVC_WARNING_PUSH PRAGMA(warning(push))
    #define MSVC_WARNING_DISABLE(ID) PRAGMA(warning(disable: ID))
    #define MSVC_WARNING_POP PRAGMA(warning(pop))
#else
    #define MSVC_WARNING_PUSH
    #define MSVC_WARNING_DISABLE(ID)
    #define MSVC_WARNING_POP
#endif

// GCC
#ifdef COMPILER_GCC
    #define GCC_WARNING_PUSH PRAGMA(GCC diagnostic push)
    #define GCC_WARNING_DISABLE(ID) PRAGMA(GCC diagnostic ignored ID)
    #define GCC_WARNING_POP PRAGMA(GCC diagnostic pop)
#else
    #define GCC_WARNING_PUSH
    #define GCC_WARNING_DISABLE(ID)
    #define GCC_WARNING_POP
#endif

// clang-tidy
#define CTIDY_NOLINT_ALL
#define CTIDY_NOLINT(...)
#define CTIDY_NOLINTNEXTLINE_ALL
#define CTIDY_NOLINTNEXTLINE(...)
#define CTIDY_NOLINTBEGIN_ALL
#define CTIDY_NOLINTBEGIN(...)
#define CTIDY_NOLINTEND_ALL
#define CTIDY_NOLINTEND(...)

#define CLANG_WARNING_PAD(ID) CLANG_WARNING_PUSH CLANG_WARNING_DISABLE(ID)
#define MSVC_WARNING_PAD(ID) MSVC_WARNING_PUSH MSVC_WARNING_DISABLE(ID)
#define GCC_WARNING_PAD(ID) GCC_WARNING_PUSH GCC_WARNING_DISABLE(ID)

#define ALLOW_DEPRECATED_BEGIN \
    CLANG_WARNING_PAD("-Wdeprecated") MSVC_WARNING_PAD(4996) GCC_WARNING_PAD("-Wdeprecated-declarations")

#define ALLOW_DEPRECATED_END CLANG_WARNING_POP MSVC_WARNING_POP GCC_WARNING_POP
