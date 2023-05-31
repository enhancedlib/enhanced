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
#include <enhanced/Types.h>

#define Unused maybe_unused
#define NoReturn noreturn
#define RetNotIgnored nodiscard
#define Deprecated deprecated
#define FallThrough fallthrough
#define Likely likely
#define Unlikely unlikely
#if E_HAS_CPP_ATTRIBUTE(assume)
    #define Assume assume
#else
    #define Assume(EXPRESSION)
#endif

#define RetRequiresRelease RetNotIgnored("The return value needs to be released")
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
