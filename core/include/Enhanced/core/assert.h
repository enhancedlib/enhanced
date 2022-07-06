/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
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
