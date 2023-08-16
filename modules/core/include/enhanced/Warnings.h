/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#pragma once

#include <enhanced/Defines.h>

// Clang
#ifdef E_COMPILER_CLANG
    #define E_CLANG_WARNING_DISABLE(ID) E_PRAGMA(clang diagnostic ignored ID)
    #define E_CLANG_WARNING_PUSH E_PRAGMA(clang diagnostic push)
    #define E_CLANG_WARNING_POP E_PRAGMA(clang diagnostic pop)
#else
    #define E_CLANG_WARNING_DISABLE(ID)
    #define E_CLANG_WARNING_PUSH
    #define E_CLANG_WARNING_POP
#endif

// MSVC
#ifdef E_COMPILER_MSVC
    #define E_MSVC_WARNING_DISABLE(ID) E_PRAGMA(warning(disable: ID))
    #define E_MSVC_WARNING_PUSH E_PRAGMA(warning(push))
    #define E_MSVC_WARNING_POP E_PRAGMA(warning(pop))
#else
    #define E_MSVC_WARNING_DISABLE(ID)
    #define E_MSVC_WARNING_PUSH
    #define E_MSVC_WARNING_POP
#endif

// GCC
#ifdef E_COMPILER_GCC
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
