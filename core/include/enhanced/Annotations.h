/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/Types.h>

#define $Unused [[maybe_unused]]

#define $NoReturn [[noreturn]]

#define $NoIgnoreReturn [[nodiscard]]
#define $NoIgnoreReturnExt(...) [[nodiscard(__VA_ARGS__)]]

#define $RetRequiresRelease $NoIgnoreReturnExt("The return value needs to be released")
#define $RetRequiresReleaseExt(...) $NoIgnoreReturnExt(__VA_ARGS__)

#define $Deprecated [[deprecated]]
#define $DeprecatedExt(...) [[deprecated(__VA_ARGS__)]]

#define $FallThrough [[fallthrough]]

#ifdef CLANG_COMPILER
    #define $ForceInline [[clang::always_inline]]
    #define $NoInline [[clang::noinline]]
#elif defined(MSVC_COMPILER)
    #define $ForceInline __forceinline
    #define $NoInline __declspec(noinline)
#elif defined(GCC_COMPILER)
    #define $ForceInline [[gnu::always_inline]]
    #define $NoInline [[gnu::noinline]]
#endif

#ifdef MSVC_ABI
    #define $Allocator $RetRequiresRelease __declspec(allocator)
#else
    #define $Allocator $RetRequiresRelease
#endif

#ifdef MSVC_ABI
    #define $RetRestrict __declspec(restrict)
#elif defined(GCC_ABI) || defined(CLANG_COMPILER)
    #define $RetRestrict [[gnu::malloc]]
#endif

#define $MaybeRequireRelease(FUNCTION)

#define $ReturnSelf

#if defined(GCC_ABI) || defined(CLANG_COMPILER)
    #define $RetNotNull [[gnu::returns_nonnull]]
#else
    #define $RetNotNull
#endif
#define $RetNullable
#define $MustInspectResult
#define $SuccessIf(CONDITION)

#define $Optional
#define $Out
#define $InOut
#define $OutOptional
#define $InOutOptional
