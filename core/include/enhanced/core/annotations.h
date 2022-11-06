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

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>

#ifdef C_LANGUAGE
#define OnlyC(annotation) annotation
#define OnlyCpp(annotation)
#else
#define OnlyC(annotation)
#define OnlyCpp(annotation) annotation
#endif

#ifdef COMPILER_MSVC
#define SAL_SUPPORTED
#endif

#ifdef SAL_SUPPORTED
#include <sal.h>

#define Optional _In_opt_
#define Out _Out_opt_
#define InOut _Inout_opt_
#define OutCannotIgnored _Out_
#define InOutRequired _Inout_

#define NotNull _Notnull_
#define Nullable _Maybenull_
#define RetNotNull _Ret_notnull_
#define RetNullable _Ret_maybenull_

#define MustInspectResult _Must_inspect_result_
#define SuccessIf(expression) _Success_(expression)

#define When(expression, annotation) _When_(expression, annotation)
#else
#define Optional
#define Out
#define InOut
#define OutCannotIgnored
#define InOutRequired

#define NotNull
#define Nullable
#define RetNotNull
#define RetNullable

#define MustInspectResult
#define SuccessIf(expression)

#define When(expression, annotation)

#endif

#define Unused [[maybe_unused]]

#if defined(CXX_17_OR_MORE)
#define RetCannotIgnored [[nodiscard]]
#elif defined(SAL_SUPPORTED)
#define RetCannotIgnored _Check_return_
#else
#define RetCannotIgnored
#endif

#if defined(CXX_20_OR_MORE)
#define RetCannotIgnoredExt(cause) [[nodiscard(cause)]]
#elif defined(CXX_17_OR_MORE)
#define RetCannotIgnoredExt(cause) [[nodiscard]]
#elif defined(SAL_SUPPORTED)
#define RetCannotIgnoredExt(cause) _Check_return_
#else
#define RetCannotIgnoredExt(cause)
#endif

#define RetRequiresRelease RetCannotIgnoredExt("The return value needs to be released")

#ifdef CXX_14_OR_MORE
#define Deprecated [[deprecated]]
#define DeprecatedExt(message) [[deprecated(message)]]
#else
#define Deprecated
#define DeprecatedExt(message)
#endif

#define AbstractClass
