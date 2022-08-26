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

#include "enhanced/core/defines.h"

#if defined(WINDOWS_OS) && defined(ENHANCED_BASIC_DYNAMIC_LIBRARY) // Dynamic library
#ifdef ENHANCED_BASIC_EXPORTS // Export
#define ENHANCED_BASIC_API __declspec(dllexport)
#else // Import
#define ENHANCED_BASIC_API __declspec(dllimport)
#endif // ENHANCED_BASIC_EXPORTS
#else // Static library or other operating system.
#define ENHANCED_BASIC_API
#endif // defined(WINDOWS_OS) && defined(ENHANCED_CORE_DYNAMIC_LIBRARY)
