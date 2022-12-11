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
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/exceptions/AssertionError.h>

// TODO: In the future, don't need to provide the current file and the current line for arguments
#define dynamic_assert(expression) ((expression) || (throw enhanced::exceptions::AssertionError(#expression, CURRENT_FILE, CURRENT_LINE), false))

#ifdef DEBUG
    #define E_ASSERT(expression) dynamic_assert(expression)
#else
    #define E_ASSERT(expression) (void) 0
#endif

#undef assert
#define assert E_ASSERT
