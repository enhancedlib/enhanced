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

namespace enhancedInternal {
    $NoReturn
    ENHANCED_CORE_API func assertionFailedImpl(const enhanced::String& message, const enhanced::String& file, sizetype line) -> void;
}

#define DYNAMIC_ASSERT(expression) ((expression) || (enhancedInternal::assertionFailedImpl(#expression, CURRENT_FILE, CURRENT_LINE), 0))

#define dynamic_assert DYNAMIC_ASSERT

#undef assert

#ifdef DEBUG
#define assert(expression) dynamic_assert(expression)
#else
#define assert(expression) (void) 0
#endif
