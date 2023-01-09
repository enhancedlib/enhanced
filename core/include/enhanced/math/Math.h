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
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>
#include <enhanced/util/Traits.h>

namespace enhanced::math {
#if defined(ENHANCED_SUPPRESS_OVERWRITE) || defined(ENHANCED_CORE_SUPPRESS_OVERWRITE_MATH_MACRO)
    #pragma push_macro("max")
    #pragma push_macro("min")
#endif
#undef max
#undef min

    template <typename Type>
    [[NoIgnoreReturn]]
    inline constexpr const Type& max(Type x, Type y) {
        return (x > y) ? x : y;
    }

    template <typename X, typename Y>
    requires util::isIntegralType<X> && util::isIntegralType<Y>
    [[NoIgnoreReturn]]
    inline constexpr util::Conditional<(sizeof(X) > sizeof(Y)), X, Y> max(X x, Y y) {
        return (x > y) ? x : y;
    }

    template <typename Type>
    [[NoIgnoreReturn]]
    inline constexpr const Type& min(Type x, Type y) {
        return (x < y) ? x : y;
    }

    template <typename X, typename Y>
    requires util::isIntegralType<X> && util::isIntegralType<Y>
    [[NoIgnoreReturn]]
    inline constexpr util::Conditional<(sizeof(X) > sizeof(Y)), X, Y> min(X x, Y y) {
        return (x < y) ? x : y;
    }

#if defined(ENHANCED_SUPPRESS_OVERWRITE) || defined(ENHANCED_CORE_SUPPRESS_OVERWRITE_MATH_MACRO)
    #pragma pop_macro("max")
    #pragma pop_macro("min")
#endif

    template <typename IntegralType>
    requires util::isIntegralType<IntegralType>
    [[NoIgnoreReturn]]
    inline constexpr util::ToUnsigned<IntegralType> abs(IntegralType number) {
        return (number >= 0) ? number : -number;
    }

    template <typename X, typename Y>
    requires util::isIntegralType<X> && util::isIntegralType<Y>
    [[NoIgnoreReturn]]
    inline constexpr util::ToUnsigned<util::Conditional<(sizeof(X) > sizeof(Y)), X, Y>> difference(X x, Y y) {
        CLANG_WARNING_PAD("-Wsign-compare") GCC_WARNING_PAD("-Wsign-compare")

        return (x < y) ? y - x : x - y;

        CLANG_WARNING_POP GCC_WARNING_POP
    }
}
