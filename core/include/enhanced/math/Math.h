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
    template <typename UIntTypeNs, bool = false>
    requires util::isIntegralTypeNs<UIntTypeNs> && util::isUnsigned<UIntTypeNs>
    class TInt { // TODO: Implement util::Comparable
    private:
        UIntTypeNs value;

    public:
        inline constexpr TInt() noexcept : value() {}

        inline constexpr TInt(UIntTypeNs value) noexcept : value(value) {}

        inline constexpr TInt(const TInt& other) noexcept = default;

        inline constexpr TInt(TInt&& other) noexcept = default;

        inline constexpr TInt operator+() const noexcept {
            return +value;
        }

        inline constexpr TInt operator-() const noexcept {
            return -value;
        }

        inline constexpr TInt operator+(const TInt& other) const noexcept {
            return value + other.value;
        }

        inline constexpr TInt operator-(const TInt& other) const noexcept {
            return value - other.value;
        }

        inline constexpr TInt operator*(const TInt& other) const noexcept {
            return value * other.value;
        }

        inline constexpr TInt operator/(const TInt& other) const noexcept {
            return value / other.value;
        }

        inline constexpr TInt operator%(const TInt& other) const noexcept {
            return value % other.value;
        }

        inline constexpr TInt operator~() const noexcept {
            return ~value;
        }

        inline constexpr TInt operator&(const TInt& other) const noexcept {
            return value & other.value;
        }

        inline constexpr TInt operator|(const TInt& other) const noexcept {
            return value | other.value;
        }

        inline constexpr TInt operator^(const TInt& other) const noexcept {
            return value ^ other.value;
        }

        inline constexpr TInt operator<<(const TInt& other) const noexcept {
            return value << other.value;
        }

        inline constexpr TInt operator>>(const TInt& other) const noexcept {
            return value >> other.value;
        }

        inline constexpr TInt operator!() const noexcept {
            return !value;
        }

        inline constexpr TInt operator&&(const TInt& other) const noexcept {
            return value && other.value;
        }

        inline constexpr TInt operator||(const TInt& other) const noexcept {
            return value || other.value;
        }

        inline constexpr bool operator==(const TInt& other) const noexcept {
            return value == other.value;
        }

        inline constexpr bool operator!=(const TInt& other) const noexcept {
            return value != other.value;
        }

        inline constexpr bool operator<(const TInt& other) const noexcept {
            return value < other.value;
        }

        inline constexpr bool operator>(const TInt& other) const noexcept {
            return value > other.value;
        }

        inline constexpr bool operator<=(const TInt& other) const noexcept {
            return value <= other.value;
        }

        inline constexpr bool operator>=(const TInt& other) const noexcept {
            return value >= other.value;
        }

        inline constexpr const TInt operator++(int) const noexcept {
            return value++;
        }

        inline constexpr const TInt operator--(int) const noexcept {
            return value--;
        }

        inline constexpr TInt& operator++() noexcept {
            return ++value;
        }

        inline constexpr TInt& operator--() noexcept {
            return --value;
        }

        inline constexpr TInt& operator+=(const TInt& other) noexcept {
            value += other.value;
            return *this;
        }

        inline constexpr TInt& operator-=(const TInt& other) noexcept {
            value -= other.value;
            return *this;
        }

        inline constexpr TInt& operator*=(const TInt& other) noexcept {
            value *= other.value;
            return *this;
        }

        inline constexpr TInt& operator/=(const TInt& other) noexcept {
            value /= other.value;
            return *this;
        }

        inline constexpr TInt& operator%=(const TInt& other) noexcept {
            value %= other.value;
            return *this;
        }

        inline constexpr TInt& operator&=(const TInt& other) noexcept {
            value &= other.value;
            return *this;
        }

        inline constexpr TInt& operator|=(const TInt& other) noexcept {
            value |= other.value;
            return *this;
        }

        inline constexpr TInt& operator^=(const TInt& other) noexcept {
            value ^= other.value;
            return *this;
        }

        inline constexpr TInt& operator<<=(const TInt& other) noexcept {
            value <<= other.value;
            return *this;
        }

        inline constexpr TInt& operator>>=(const TInt& other) noexcept {
            value >>= other.value;
            return *this;
        }

        inline constexpr TInt& operator=(const TInt& other) noexcept = default;

        inline constexpr TInt& operator=(TInt&& other) noexcept = default;

        inline constexpr operator UIntTypeNs() const {
            return value;
        }

        inline constexpr operator const UIntTypeNs() const {
            return value;
        }

        inline constexpr operator UIntTypeNs&() const {
            return value;
        }
    };

    using PInt8 = TInt<uint8>;
    using PInt16 = TInt<uint16>;
    using PInt32 = TInt<uint32>;
    using PInt64 = TInt<uint64>;

    using NInt8 = TInt<uint8, true>;
    using NInt16 = TInt<uint16, true>;
    using NInt32 = TInt<uint32, true>;
    using NInt64 = TInt<uint64, true>;

#if defined(ENHANCED_SUPPRESS_OVERWRITE) || defined(ENHANCED_CORE_SUPPRESS_OVERWRITE_MATH_MACRO)
    #pragma push_macro("max")
    #pragma push_macro("min")
#endif
#undef max
#undef min

    template <typename Type>
    [[RetNotIgnored]]
    inline constexpr const Type& max(Type x, Type y) {
        return (x > y) ? x : y;
    }

    template <typename X, typename Y>
    requires util::isIntegralType<X> && util::isIntegralType<Y>
    [[RetNotIgnored]]
    inline constexpr util::Conditional<(sizeof(X) > sizeof(Y)), X, Y> max(X x, Y y) {
        return (x > y) ? x : y;
    }

    template <typename Type>
    [[RetNotIgnored]]
    inline constexpr const Type& min(Type x, Type y) {
        return (x < y) ? x : y;
    }

    template <typename X, typename Y>
    requires util::isIntegralType<X> && util::isIntegralType<Y>
    [[RetNotIgnored]]
    inline constexpr util::Conditional<(sizeof(X) > sizeof(Y)), X, Y> min(X x, Y y) {
        return (x < y) ? x : y;
    }

#if defined(ENHANCED_SUPPRESS_OVERWRITE) || defined(ENHANCED_CORE_SUPPRESS_OVERWRITE_MATH_MACRO)
    #pragma pop_macro("max")
    #pragma pop_macro("min")
#endif

    template <typename IntegralType>
    requires util::isIntegralType<IntegralType>
    [[RetNotIgnored]]
    inline constexpr util::ToUnsigned<IntegralType> abs(IntegralType number) {
        return (number >= 0) ? number : -number;
    }

    template <typename X, typename Y>
    requires util::isIntegralType<X> && util::isIntegralType<Y>
    [[RetNotIgnored]]
    inline constexpr util::ToUnsigned<util::Conditional<(sizeof(X) > sizeof(Y)), X, Y>> difference(X x, Y y) {
        CLANG_WARNING_PAD("-Wsign-compare") GCC_WARNING_PAD("-Wsign-compare")

        return (x < y) ? y - x : x - y;

        CLANG_WARNING_POP GCC_WARNING_POP
    }
}
