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

#ifdef CLANG_COMPILER
    #define CLANG_WARNING_PUSH PRAGMA(clang diagnostic push)
    #define CLANG_WARNING_DISABLE(id) PRAGMA(clang diagnostic ignored id)
    #define CLANG_WARNING_POP PRAGMA(clang diagnostic pop)
#else
    #define CLANG_WARNING_PUSH
    #define CLANG_WARNING_DISABLE(id)
    #define CLANG_WARNING_POP
#endif

#ifdef MSVC_COMPILER
    #define MSVC_WARNING_PUSH PRAGMA(warning(push))
    #define MSVC_WARNING_DISABLE(id) PRAGMA(warning(disable: id))
    #define MSVC_WARNING_POP PRAGMA(warning(pop))
#else
    #define MSVC_WARNING_PUSH
    #define MSVC_WARNING_DISABLE(id)
    #define MSVC_WARNING_POP
#endif

#ifdef GCC_COMPILER
    #define GCC_WARNING_PUSH PRAGMA(GCC diagnostic push)
    #define GCC_WARNING_DISABLE(id) PRAGMA(GCC diagnostic ignored id)
    #define GCC_WARNING_POP PRAGMA(GCC diagnostic pop)
#else
    #define GCC_WARNING_PUSH
    #define GCC_WARNING_DISABLE(id)
    #define GCC_WARNING_POP
#endif

#define CLANG_WARNING_PUSH_AND_DISABLE(id) CLANG_WARNING_PUSH CLANG_WARNING_DISABLE(id)
#define MSVC_WARNING_PUSH_AND_DISABLE(id) MSVC_WARNING_PUSH MSVC_WARNING_DISABLE(id)
#define GCC_WARNING_PUSH_AND_DISABLE(id) GCC_WARNING_PUSH GCC_WARNING_DISABLE(id)

#define ALLOW_DEPRECATED_BEGIN \
    CLANG_WARNING_PUSH_AND_DISABLE("-Wdeprecated") MSVC_WARNING_PUSH_AND_DISABLE(4996) GCC_WARNING_PUSH_AND_DISABLE("-Wdeprecated-declarations")

#define ALLOW_DEPRECATED_END CLANG_WARNING_POP MSVC_WARNING_POP GCC_WARNING_POP
