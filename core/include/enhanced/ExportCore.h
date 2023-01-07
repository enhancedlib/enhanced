/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#pragma once

#include <enhanced/Defines.h>

#if defined(WINDOWS_OS) && defined(ENHANCED_CORE_SHARED_LIBRARY)
    #ifdef ENHANCED_CORE_BUILDING
        #define ENHANCED_CORE_API __declspec(dllexport)
    #else
        #define ENHANCED_CORE_API __declspec(dllimport)
    #endif
#elif defined(GCC_COMPILER) && defined(ENHANCED_CORE_SHARED_LIBRARYRARY)
    #define ENHANCED_CORE_API [[gnu::visibility("default")]]
#else
    #define ENHANCED_CORE_API
#endif
