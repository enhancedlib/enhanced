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

#define E_ANNOTATION(NAME, PARAMS, ...) _E_META_MACRO("annotation", (NAME, PARAMS, __VA_ARGS__))

#define E_DEPRECATED_MACRO(...) \
    E_ANNOTATION(E_DEPRECATED_MACRO, ("message"), __VA_ARGS__)

#define E_DEPRECATED(...) \
    E_ANNOTATION(E_DEPRECATED, ("message"), __VA_ARGS__) \
    [[deprecated E_PACK_BRACKET_IF_NOT_EMPTY(E_EXTRACT(1, __VA_ARGS__))]]

#define E_RET_NO_DISCARD(...) \
    E_ANNOTATION(E_RET_NO_DISCARD, ("message"), __VA_ARGS__) \
    [[nodiscard E_PACK_BRACKET_IF_NOT_EMPTY(E_EXTRACT(1, __VA_ARGS__))]]

#define E_NO_RETURN() \
    E_ANNOTATION(E_NO_RETURN, ()) \
    [[noreturn]]

#define E_UNUSED() \
    E_ANNOTATION(E_UNUSED, ()) \
    [[maybe_unused]]

#define E_FALL_THROUGH() \
    E_ANNOTATION(E_FALL_THROUGH, ()) \
    [[fallthrough]]

#define E_LIKELY() \
    E_ANNOTATION(E_LIKELY, ()) \
    [[likely]]

#define E_UNLIKELY() \
    E_ANNOTATION(E_UNLIKELY, ()) \
    [[unlikely]]

#if E_HAS_CPP_ATTRIBUTE(assume)
    #define E_ASSUME(EXPRESSION) \
        E_ANNOTATION(E_ASSUME, ("expression"), EXPRESSION) \
        [[assume(EXPRESSION)]]
#else
    #define E_ASSUME(EXPRESSION) \
        E_ANNOTATION(E_ASSUME, ("expression"), EXPRESSION)
#endif

#define E_RET_NEED_RELEASE(...) \
    E_ANNOTATION(E_RET_NEED_RELEASE, ("message"), __VA_ARGS__) \
    E_RET_NO_DISCARD(E_EXTRACT(1, __VA_ARGS__))

#define E_RETURN(EXPRESSION) \
    E_ANNOTATION(E_RETURN, ("expression"), EXPRESSION)

#if defined(E_COMPILER_GCC) || defined(E_COMPILER_CLANG)
    #define E_RET_NONNULL() \
        E_ANNOTATION(E_RET_NONNULL, ()) \
        [[gnu::returns_nonnull]]
#else
    #define E_RET_NONNULL() \
        E_ANNOTATION(E_RET_NONNULL, ())
#endif

#define E_RET_NULLABLE() \
    E_ANNOTATION(E_RET_NULLABLE, ())

#define E_RET_NULLABLE_IF(CONDITION) \
    E_ANNOTATION(E_RET_NULLABLE_IF, (CONDITION))

#define E_CHECK_RET() \
    E_ANNOTATION(E_CHECK_RET, ())

#define E_RET_CONTRACT(EXPRESSION) \
    E_ANNOTATION(E_RET_CONTRACT, (EXPRESSION))

#define E_FUNC_FAILED_IF(CONDITION) \
    E_ANNOTATION(E_FUNC_FAILED_IF, (CONDITION))

#define E_PURE() \
    E_ANNOTATION(E_PURE, ())

#define E_NONNULL() \
    E_ANNOTATION(E_NONNULL, ())

#define E_NULLABLE() \
    E_ANNOTATION(E_NULLABLE, ())

#define E_OUT() \
    E_ANNOTATION(E_OUT, (), ())

#define E_IN_OUT() \
    E_ANNOTATION(E_IN_OUT, (), ())
