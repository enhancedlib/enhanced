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
#define $Allocator $RetRequiresRelease __declspec(restrict) __declspec(allocator)
#elif defined(GCC_ABI) || defined(CLANG_COMPILER)
#define $Allocator $RetRequiresRelease [[gnu::malloc]]
#endif

#define $MaybeRequireRelease(releaseFunction)

#ifdef WINDOWS_OS
#include <sal.h>

#if defined(GCC_ABI) || defined(CLANG_COMPILER)
#define $RetNotNull _Ret_notnull_ [[gnu::returns_nonnull]]
#else
#define $RetNotNull _Ret_notnull_
#endif
#define $RetNullable _Ret_maybenull_
#define $MustInspectResult _Must_inspect_result_
#define $SuccessIf(condition) _Success_(condition)

#define $Optional _In_opt_
#define $Out _Out_
#define $InOut _Inout_
#define $OutOptional _Out_opt_
#define $InOutOptional _Inout_opt_

#define $When(condition, annotations) _When_(condition, annotations)

#else

#if defined(GCC_ABI) || defined(CLANG_COMPILER)
#define $RetNotNull [[gnu::returns_nonnull]]
#else
#define $RetNotNull
#endif
#define $RetNullable
#define $MustInspectResult
#define $SuccessIf(condition)

#define $Optional
#define $Out
#define $InOut
#define $OutOptional
#define $InOutOptional

#define $When(condition, annotations)

#endif
