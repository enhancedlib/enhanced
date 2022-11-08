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
#define OnlyC(annotations) annotation
#define OnlyCpp(annotations)
#else
#define OnlyC(annotations)
#define OnlyCpp(annotations) annotation
#endif

#ifdef SAL_SUPPORTED
#include <sal.h>

#ifndef _Notnull_
#define _Notnull_
#endif

#ifndef _Maybenull_
#define _Maybenull_
#endif

#define NotNull _Notnull_
#define Nullable _Maybenull_

#define RetNotNull _Ret_notnull_
#define RetNullable _Ret_maybenull_
#define MustInspectResult _Must_inspect_result_
#define SuccessIf(expression) _Success_(expression)

#define Optional _In_opt_
#define Out _Out_opt_
#define InOut _Inout_opt_
#define OutCannotIgnored _Out_
#define InOutRequired _Inout_

#define When(expression, annotations) _When_(expression, annotations)

#else

#define NotNull
#define Nullable

#define RetNotNull
#define RetNullable
#define MustInspectResult
#define SuccessIf(expression)

#define Optional
#define Out
#define InOut
#define OutCannotIgnored
#define InOutRequired

#define When(expression, annotations)

#endif

#define Unused [[maybe_unused]]

#ifdef CXX_17_OR_LATER
#define NoIgnoreRet [[nodiscard]]
#elif defined(SAL_SUPPORTED)
#define NoIgnoreRet _Check_return_
#else
#define NoIgnoreRet
#endif

#ifdef CXX_20_OR_LATER
#define NoIgnoreRetExt(cause) [[nodiscard(cause)]]
#elif defined(CXX_17_OR_LATER)
#define NoIgnoreRetExt(cause) [[nodiscard]]
#elif defined(SAL_SUPPORTED)
#define NoIgnoreRetExt(cause) _Check_return_
#else
#define NoIgnoreRetExt(cause)
#endif

#define RetRequiresRelease NoIgnoreRetExt("The return value needs to be released")

#define RetRequiresReleaseExt NoIgnoreRetExt

#ifdef CXX_14_OR_LATER
#define Deprecated [[deprecated]]
#define DeprecatedExt(message) [[deprecated(message)]]
#else
#define Deprecated
#define DeprecatedExt(message)
#endif

#define AbstractClass
