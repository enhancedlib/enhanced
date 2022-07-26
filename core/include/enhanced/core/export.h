/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "defines.h"

#if defined(WINDOWS_OS) /* Windows OS */ && defined(ENHANCED_CORE_DYNAMIC_LIBRARY) /* Dynamic library */
#ifdef ENHANCED_CORE_EXPORTS // Export
#define ENHANCED_CORE_API __declspec(dllexport)
#else // Import
#define ENHANCED_CORE_API __declspec(dllimport)
#endif // ENHANCED_CORE_EXPORTS
#else // Static library or other operating system.
#define ENHANCED_CORE_API
#endif // defined(WINDOWS_OS) && defined(ENHANCED_CORE_DYNAMIC_LIBRARY)
