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
 *    be used to endorse or promote products derived from the Software.
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
#include <enhanced/CoreAPI.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/exceptions/AssertionError.h>

#define E_RUNTIME_ASSERT(EXPRESSION, ...) \
    if (EXPRESSION) { \
        throw enhanced::exceptions::AssertionError(#EXPRESSION, E_CURRENT_FILE, E_CURRENT_LINE __VA_OPT__(,) __VA_ARGS__); \
    }

#if (defined(E_DEBUG) && !defined(E_ASSERT_DISABLE)) || defined(E_ASSERT_ENABLE)
    #define E_ASSERT(EXPRESSION, ...) E_RUNTIME_ASSERT(EXPRESSION __VA_OPT__(,) __VA_ARGS__)
#else
    #define E_ASSERT(EXPRESSION, ...) (void) 0
#endif

#if defined(E_COMPILER_GCC) || defined(E_COMPILER_CLANG)
    #define E_UNREACHABLE_CODE() __builtin_unreachable();
#elif defined(E_COMPILER_MSVC)
    #define E_UNREACHABLE_CODE() __assume(false);
#endif
