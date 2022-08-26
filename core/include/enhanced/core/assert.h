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
#include "export.h"
#include "types.h"

EXTERN_C_START

ENHANCED_CORE_API void assertionFailed(const char* message, const char* file, uint line);

#ifdef assert
#undef assert
#endif // assert

#define dynamicAssert(expression) \
    ((expression) || (assertionFailed(#expression, __FILE__, __LINE__), 0))

#define dynamic_assert dynamicAssert

#ifdef DEBUG
#define assert(expression) dynamic_assert(expression)
#else
#define assert(expression) (void) 0
#endif // DEBUG

EXTERN_C_END
