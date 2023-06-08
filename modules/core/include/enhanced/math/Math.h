/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute, subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not charge any fees or receive other compensation for the
 *    distribution of the Software.
 *
 * 3. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 4. If you use this Software in your product, you should indicate the it in
 *    the product documentation.
 *
 * Unless you have obtained the written consent of the copyright holders,
 * you may not break these restrictions.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>
#include <enhanced/util/Traits.h>
#include <enhanced/Integral.h>
#include <enhanced/util/Comparable.h>

namespace enhanced::math {
    enum class TIntMode : bool {
        POSITIVE, NEGATIVE
    };

    template <typename UIntTypeNs, TIntMode mode>
    requires util::isIntegralTypeNs<UIntTypeNs> && util::isUnsigned<UIntTypeNs>
    struct TInt : public Integral<UIntTypeNs> {
        E_INTEGRAL_EXTENSION_DEFAULT_METHODS(TInt, UIntTypeNs)
    };

    using PInt8 = TInt<uint8, TIntMode::POSITIVE>;
    using PInt16 = TInt<uint16, TIntMode::POSITIVE>;
    using PInt32 = TInt<uint32, TIntMode::POSITIVE>;
    using PInt64 = TInt<uint64, TIntMode::POSITIVE>;

    using NInt8 = TInt<uint8, TIntMode::NEGATIVE>;
    using NInt16 = TInt<uint16, TIntMode::NEGATIVE>;
    using NInt32 = TInt<uint32, TIntMode::NEGATIVE>;
    using NInt64 = TInt<uint64, TIntMode::NEGATIVE>;

#if defined(E_SM_SUPPRESS_OVERWRITE) || defined(E_SM_CORE_SUPPRESS_OVERWRITE_MATH_MACRO)
    #pragma push_macro("max")
    #pragma push_macro("min")
#endif
#undef max
#undef min

    template <typename Type>
    E_ANNOTATE(RetNotIgnored)
    inline constexpr const Type& max(const Type& x, const Type& y) noexcept(noexcept(x > y)) {
        return (x > y) ? x : y;
    }

    template <typename X, typename Y>
    requires util::isIntegralType<X> && util::isIntegralType<Y>
    E_ANNOTATE(RetNotIgnored)
    inline constexpr util::Conditional<(sizeof(X) > sizeof(Y)), X, Y> max(const X& x, const Y& y) noexcept {
        return (x > y) ? x : y;
    }

    template <typename Type>
    E_ANNOTATE(RetNotIgnored)
    inline constexpr const Type& min(const Type& x, const Type& y) noexcept(noexcept(x < y)) {
        return (x < y) ? x : y;
    }

    template <typename X, typename Y>
    requires util::isIntegralType<X> && util::isIntegralType<Y>
    E_ANNOTATE(RetNotIgnored)
    inline constexpr util::Conditional<(sizeof(X) > sizeof(Y)), X, Y> min(const X& x, const Y& y) noexcept {
        return (x < y) ? x : y;
    }

#if defined(E_SM_SUPPRESS_OVERWRITE) || defined(E_SM_CORE_SUPPRESS_OVERWRITE_MATH_MACRO)
    #pragma pop_macro("max")
    #pragma pop_macro("min")
#endif

    template <typename IntegralType>
    requires util::isIntegralType<IntegralType>
    E_ANNOTATE(RetNotIgnored)
    inline constexpr util::ToUnsigned<IntegralType> abs(IntegralType number) noexcept {
        return (number >= 0) ? number : -number;
    }

    template <typename X, typename Y>
    requires util::isIntegralType<X> && util::isIntegralType<Y>
    E_ANNOTATE(RetNotIgnored)
    inline constexpr util::ToUnsigned<util::Conditional<(sizeof(X) > sizeof(Y)), X, Y>> difference(X x, Y y) noexcept(noexcept(x < y)) {
        E_CLANG_WARNING_PAD("-Wsign-compare") E_GCC_WARNING_PAD("-Wsign-compare")

        return (x < y) ? y - x : x - y;

        E_CLANG_WARNING_POP E_GCC_WARNING_POP
    }
}
