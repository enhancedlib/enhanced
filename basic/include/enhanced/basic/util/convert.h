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
#include "enhanced/core/types.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::util::convert {
    template <typename ConvertType, typename Type>
    inline ConvertType& forceCast(Type&& value) {
        return *((ConvertType*) (void*) &value);
    }

    template <typename Type>
    inline const Type& copy(Type&& value) {
        return (const Type&) value;
    }

    template <typename Type>
    inline Type&& share(const Type& value) {
        return (Type&&) value;
    }
}

#define force_cast enhanced::basic::util::forceCast

#endif // CXX_LANGUAGE
