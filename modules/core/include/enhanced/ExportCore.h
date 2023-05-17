/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/Defines.h>

#if defined(OS_WINDOWS) && defined(ENHANCED_CORE_SHARED_LIBRARY)
    #ifdef ENHANCED_CORE_BUILDING
        #define ENHANCED_CORE_API __declspec(dllexport)
    #else
        #define ENHANCED_CORE_API __declspec(dllimport)
    #endif
#elif defined(COMPILER_GCC) && defined(ENHANCED_CORE_SHARED_LIBRARY)
    #define ENHANCED_CORE_API [[gnu::visibility("default")]]
#else
    #define ENHANCED_CORE_API
#endif
