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

#if defined(WINDOWS_OS) && defined(ENHANCED_CORE_SHARED_LIB)
#ifdef ENHANCED_CORE_BUILDING
#define ENHANCED_CORE_API __declspec(dllexport)
#else
#define ENHANCED_CORE_API __declspec(dllimport)
#endif
#elif defined(GCC_COMPILER) && defined(ENHANCED_CORE_SHARED_LIB)
#define ENHANCED_CORE_API [[gnu::visibility("default")]]
#else
#define ENHANCED_CORE_API
#endif
