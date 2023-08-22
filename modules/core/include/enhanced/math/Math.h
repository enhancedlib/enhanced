/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software.
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
#include <enhanced/Traits.h>
#include <enhanced/Integral.h>
#include <enhanced/Comparable.h>

namespace enhanced::math {
    enum class TIntMode : bool {
        POSITIVE, NEGATIVE
    };

    template <typename UIntTypeNs, TIntMode mode>
    requires isIntegralTypeNs<UIntTypeNs> && isUnsigned<UIntTypeNs>
    class TInt : public Integral<UIntTypeNs> {
        E_CLASS(TInt)

    E_CLASS_BODY
        E_INTEGRAL_DEFAULT_METHODS(TInt, UIntTypeNs)
    };

    using PInt8 = TInt<uint8, TIntMode::POSITIVE>;
    using PInt16 = TInt<uint16, TIntMode::POSITIVE>;
    using PInt32 = TInt<uint32, TIntMode::POSITIVE>;
    using PInt64 = TInt<uint64, TIntMode::POSITIVE>;

    using NInt8 = TInt<uint8, TIntMode::NEGATIVE>;
    using NInt16 = TInt<uint16, TIntMode::NEGATIVE>;
    using NInt32 = TInt<uint32, TIntMode::NEGATIVE>;
    using NInt64 = TInt<uint64, TIntMode::NEGATIVE>;

#ifdef E_OS_WINDOWS
    #undef max
    #undef min
#endif

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr const Type& max(const Type& x, const Type& y) noexcept(noexcept(x > y)) {
        return (x > y) ? x : y;
    }

    template <typename X, typename Y>
    requires isIntegralType<X> && isIntegralType<Y>
    E_RET_NO_DISCARD()
    inline constexpr Conditional<(sizeof(X) > sizeof(Y)), X, Y> max(const X& x, const Y& y) noexcept {
        return (x > y) ? x : y;
    }

    template <typename Type>
    E_RET_NO_DISCARD()
    inline constexpr const Type& min(const Type& x, const Type& y) noexcept(noexcept(x < y)) {
        return (x < y) ? x : y;
    }

    template <typename X, typename Y>
    requires isIntegralType<X> && isIntegralType<Y>
    E_RET_NO_DISCARD()
    inline constexpr Conditional<(sizeof(X) > sizeof(Y)), X, Y> min(const X& x, const Y& y) noexcept {
        return (x < y) ? x : y;
    }

    template <typename IntegralType>
    requires isIntegralType<IntegralType>
    E_RET_NO_DISCARD()
    inline constexpr ToUnsigned<IntegralType> abs(IntegralType number) noexcept {
        return (number >= 0) ? number : -number;
    }

    template <typename X, typename Y>
    requires isIntegralType<X> && isIntegralType<Y>
    E_RET_NO_DISCARD()
    inline constexpr ToUnsigned<Conditional<(sizeof(X) > sizeof(Y)), X, Y>> difference(X x, Y y) noexcept(noexcept(x < y)) {
        E_CLANG_WARNING_PAD("-Wsign-compare") E_GCC_WARNING_PAD("-Wsign-compare")

        return (x < y) ? y - x : x - y;

        E_CLANG_WARNING_POP E_GCC_WARNING_POP
    }
}
