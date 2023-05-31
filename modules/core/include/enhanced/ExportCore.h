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

#ifdef E_SM_CORE_SHARED_LIBRARY
    #ifdef E_SM_CORE_BUILDING
        #define E_CORE_API E_LIB_EXPORT
    #else
        #define E_CORE_API E_LIB_IMPORT
    #endif
#else
    #define E_CORE_API
#endif
