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
#include <enhanced/Types.h>

#define Unused maybe_unused
#define NoReturn noreturn
#define RetNoDiscard nodiscard
#define Deprecated deprecated
#define FallThrough fallthrough
#define Likely likely
#define Unlikely unlikely
#if E_HAS_CPP_ATTRIBUTE(assume)
    #define Assume assume
#else
    #define Assume(EXPRESSION)
#endif

#define RetRequiresRelease RetNoDiscard("The return value needs to be released")
#define ReturnSelf
#if defined(E_SM_COMPILER_GCC) || defined(E_SM_COMPILER_CLANG)
    #define RetNotNull gnu::returns_nonnull
#else
    #define RetNotNull
#endif
#define RetNullable
#define MustInspectResult
#define SuccessIf(CONDITION)
#define Optional
#define Out
#define InOut
#define OutOpt
#define InOutOpt
#define MayRequireRelease(FUNCTION)

#define E_ANNOTATE(...) [[__VA_ARGS__]]
