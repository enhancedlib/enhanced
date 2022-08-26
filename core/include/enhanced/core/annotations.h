/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "defines.h"
#include "types.h"

#ifdef COMPILER_MSVC
#include <sal.h>

#define Optional _In_opt_
#define Out _Out_opt_
#define InOut _Inout_opt_
#define OutCannotIgnored _Out_
#define InOutRequired  _Inout_

#define NotNull _Notnull_
#define Nullable _Maybenull_

#define MustInspectResult _Must_inspect_result_
#define SuccessIf(expression) _Success_(expression)

#define When(expression, annotations) _When_(expression, annotations)

#else

#define Optional
#define Out
#define InOut
#define OutCannotIgnored
#define InOutRequired

#define NotNull
#define Nullable

#define MustInspectResult
#define SuccessIf(expression)

#define When(expression, annotations)

#endif // COMPILER_MSVC

#define Unsupported(...)

#define Unused [[maybe_unused]]

#if defined(CXX_17_OR_MORE)
#define RetCannotIgnored [[nodiscard]]
#elif defined(COMPILER_MSVC)
#define RetCannotIgnored _Check_return_
#else
#define RetCannotIgnored
#endif // CXX_20_OR_MORE

#if defined(CXX_20_OR_MORE)
#define RetCannotIgnoredExt(cause) [[nodiscard(cause)]]
#elif defined(CXX_17_OR_MORE)
#define RetCannotIgnoredExt(cause) [[nodiscard]]
#elif defined(COMPILER_MSVC)
#define RetCannotIgnoredExt(cause) _Check_return_
#else
#define RetCannotIgnoredExt(cause)
#endif // CXX_20_OR_MORE

#define RetRequiresRelease RetCannotIgnoredExt("The return value needs to be released")

#ifdef CXX_14_OR_MORE
#define Deprecated [[deprecated]]
#else
#define Deprecated
#endif // CXX_14_OR_MORE

#ifdef CXX_14_OR_MORE
#define DeprecatedExt(message) [[deprecated(message)]]
#else
#define DeprecatedExt(message)
#endif // CXX_14_OR_MORE
