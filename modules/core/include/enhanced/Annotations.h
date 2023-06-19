/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
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
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
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

#define _E_ANNOTATE_IMPL(NAME, ARGS)

#define _E_ANNOTATE(NAME, ARGS, CXX_DECLARATION) _E_ANNOTATE_IMPL(NAME, ARGS) CXX_DECLARATION

#define E_RET_NO_DISCARD(...) _E_ANNOTATE(RET_NO_DISCARD, (MESSAGE), [[nodiscard E_PACK_BRACKET_IF(__VA_ARGS__)]])

#define E_DEPRECATED(...) _E_ANNOTATE(DEPRECATED, (MESSAGE), [[deprecated E_PACK_BRACKET_IF(__VA_ARGS__)]])

#define E_NO_RETURN() _E_ANNOTATE(NO_RETURN, (), [[noreturn]])

#define E_UNUSED() _E_ANNOTATE(UNUSED, (), [[maybe_unused]])

#define E_FALL_THROUGH() _E_ANNOTATE(FALL_THROUGH, (), [[fallthrough]])

#define E_LIKELY() _E_ANNOTATE(LIKELY, (), [[likely]])

#define E_UNLIKELY() _E_ANNOTATE(UNLIKELY, (), [[unlikely]])

#if E_HAS_CPP_ATTRIBUTE(assume)
    #define E_ASSUME(EXPRESSION) _E_ANNOTATE(ASSUME, (EXPRESSION), [[assume(EXPRESSION)]])
#else
    #define E_ASSUME(EXPRESSION) _E_ANNOTATE(ASSUME, (EXPRESSION),)
#endif

#define E_RET_NEED_RELEASE(...) _E_ANNOTATE(RET_NEED_RELEASE, (MESSAGE), E_RET_NO_DISCARD(__VA_ARGS__))

#define E_RETURN_SELF() _E_ANNOTATE(RETURN_SELF, (),)

#if defined(E_SM_COMPILER_GCC) || defined(E_SM_COMPILER_CLANG)
    #define E_RET_NOT_NULL() _E_ANNOTATE(RET_NOT_NULL, (), [[gnu::returns_nonnull]])
#else
    #define E_RET_NOT_NULL() _E_ANNOTATE(RET_NOT_NULL, (),)
#endif

#define E_RET_NULLABLE() _E_ANNOTATE(RET_NULLABLE, (),)

#define E_RET_NULLABLE_IF(CONDITION) _E_ANNOTATE(RET_NULLABLE_IF, (CONDITION),)

#define E_RET_INSPECT() _E_ANNOTATE(RET_INSPECT, (),)

#define E_FUNC_SUCCESS_IF(CONDITION) _E_ANNOTATE(FUNC_SUCCESS_IF, (CONDITION),)

#define E_NULLABLE() _E_ANNOTATE(NULLABLE, (),)

#define E_RELEASE_FUNC(FUNCTION) _E_ANNOTATE(RELEASE_FUNC, (FUNCTION),)

#define E_OUT() _E_ANNOTATE(OUT, (),)

#define E_IN_OUT() _E_ANNOTATE(IN_OUT, (),)

#define E_OUT_OPT() _E_ANNOTATE(OUT_OPT, (),)

#define E_IN_OUT_OPT() _E_ANNOTATE(IN_OUT_OPT, (),)
