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
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/util/Traits.h>

namespace enhanced::math {
    template <typename IntegralType>
    requires util::isIntegralType<IntegralType>
    $NoIgnoreReturn
    inline IntegralType max(IntegralType x, IntegralType y) {
        return (x > y) ? x : y;
    }

    template <typename IntegralType>
    requires util::isIntegralType<IntegralType>
    $NoIgnoreReturn
    inline IntegralType min(IntegralType x, IntegralType y) {
        return (x < y) ? x : y;
    }

    template <typename IntegralType>
    requires util::isSigned<IntegralType>
    $NoIgnoreReturn
    inline IntegralType abs(IntegralType number) {
        return (number >= 0) ? number : -number;
    }
}
