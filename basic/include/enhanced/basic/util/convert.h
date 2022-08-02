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
