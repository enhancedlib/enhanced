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

#define $(...) __VA_ARGS__

#ifdef WINDOWS_OS
#include <sal.h>

#define RetNotNull _Ret_notnull_
#define RetNullable _Ret_maybenull_
#define MustInspectResult _Must_inspect_result_
#define SuccessIf(condition) _Success_(condition)

#define Optional _In_opt_
#define Out _Out_
#define InOut _Inout_
#define OutOptional _Out_opt_
#define InOutOptional _Inout_opt_

#define When(condition, annotations) _When_(condition, annotations)

#else

#define RetNotNull
#define RetNullable
#define MustInspectResult
#define SuccessIf(condition)

#define Optional
#define Out
#define InOut
#define OutOptional
#define InOutOptional

#define When(condition, annotations)

#endif

#define Unused [[maybe_unused]]

#define NoReturn [[noreturn]]
#define NoIgnoreReturn [[nodiscard]]

#ifdef CXX_20_OR_LATER
#define NoIgnoreReturnExt(...) [[nodiscard(__VA_ARGS__)]]
#else
#define NoIgnoreReturnExt(...) [[nodiscard]]
#endif

#define RetRequiresRelease NoIgnoreReturnExt("The return value needs to be released")
#define RetRequiresReleaseExt NoIgnoreReturnExt

#define Deprecated [[deprecated]]
#define DeprecatedExt(...) [[deprecated(__VA_ARGS__)]]
