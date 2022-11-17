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

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/util/traits.h>

namespace enhanced::core::math {
    template <typename IntegralType>
    inline func max(IntegralType x, IntegralType y) -> util::EnableIf<util::isIntegralType<IntegralType>, IntegralType> {
        return (x > y) ? x : y;
    }

    template <typename IntegralType>
    inline func min(IntegralType x, IntegralType y) -> util::EnableIf<util::isIntegralType<IntegralType>, IntegralType> {
        return (x < y) ? x : y;
    }

    template <typename IntegralType>
    inline func abs(IntegralType number) -> util::EnableIf<util::isIntegralType<IntegralType>, IntegralType> {
        return (number >= 0) ? number : -number;
    }
}
