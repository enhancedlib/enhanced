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
#include <enhanced/util/Comparable.h>

namespace enhanced::math {
    enum class TIntMode {
        POSITIVE, NEGATIVE
    };

    template <typename UIntTypeNs, TIntMode mode>
    requires util::isIntegralTypeNs<UIntTypeNs> && util::isUnsigned<UIntTypeNs>
    class TInt : public util::Comparable<TInt<UIntTypeNs, mode>> {
    private:
        UIntTypeNs value;

    public:
        inline constexpr TInt() noexcept : value() {}

        inline constexpr TInt(UIntTypeNs value) noexcept : value(value) {}

        inline constexpr TInt(const TInt& other) noexcept = default;

        inline constexpr TInt(TInt&& other) noexcept = default;

        [[RetNotIgnored]]
        inline constexpr util::ComparisonResult compare(const TInt& other) const {
            return value == other.value ? util::ComparisonResult::EQUAL :
                (value > other.value ? util::ComparisonResult::GREATER : util::ComparisonResult::LESS);
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator+() const noexcept {
            return +value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator-() const noexcept {
            return -value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator+(const TInt& other) const noexcept {
            return value + other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator-(const TInt& other) const noexcept {
            return value - other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator*(const TInt& other) const noexcept {
            return value * other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator/(const TInt& other) const noexcept {
            return value / other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator%(const TInt& other) const noexcept {
            return value % other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator~() const noexcept {
            return ~value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator&(const TInt& other) const noexcept {
            return value & other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator|(const TInt& other) const noexcept {
            return value | other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator^(const TInt& other) const noexcept {
            return value ^ other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator<<(const TInt& other) const noexcept {
            return value << other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator>>(const TInt& other) const noexcept {
            return value >> other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator!() const noexcept {
            return !value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator&&(const TInt& other) const noexcept {
            return value && other.value;
        }

        [[RetNotIgnored]]
        inline constexpr TInt operator||(const TInt& other) const noexcept {
            return value || other.value;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator==(const TInt& other) const noexcept {
            return value == other.value;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator!=(const TInt& other) const noexcept {
            return value != other.value;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator<(const TInt& other) const noexcept {
            return value < other.value;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator>(const TInt& other) const noexcept {
            return value > other.value;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator<=(const TInt& other) const noexcept {
            return value <= other.value;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator>=(const TInt& other) const noexcept {
            return value >= other.value;
        }

        inline constexpr const TInt operator++(int) const noexcept {
            return value++;
        }

        inline constexpr const TInt operator--(int) const noexcept {
            return value--;
        }

        inline constexpr operator UIntTypeNs() const {
            return value;
        }

        inline constexpr operator const UIntTypeNs() const {
            return value;
        }

        inline constexpr operator UIntTypeNs&() const {
            return value;
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
    };

    using PInt8 = TInt<uint8, TIntMode::POSITIVE>;
    using PInt16 = TInt<uint16, TIntMode::POSITIVE>;
    using PInt32 = TInt<uint32, TIntMode::POSITIVE>;
    using PInt64 = TInt<uint64, TIntMode::POSITIVE>;

    using NInt8 = TInt<uint8, TIntMode::NEGATIVE>;
    using NInt16 = TInt<uint16, TIntMode::NEGATIVE>;
    using NInt32 = TInt<uint32, TIntMode::NEGATIVE>;
    using NInt64 = TInt<uint64, TIntMode::NEGATIVE>;

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
