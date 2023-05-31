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
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>
#include <enhanced/util/Traits.h>
#include <enhanced/util/Comparable.h>

#define E_INTEGRAL_EXTENSION_DEFAULT_METHODS(NAME, TYPE) \
    inline constexpr NAME() noexcept : Integral<TYPE>() {} \
    inline constexpr NAME(TYPE value) noexcept : Integral<TYPE>(value) {} \
    inline constexpr NAME(const NAME& other) noexcept = default; \
    inline constexpr NAME(NAME&& other) noexcept = default; \
    inline constexpr NAME& operator=(const NAME& other) noexcept = default; \
    inline constexpr NAME& operator=(NAME&& other) noexcept = default;

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define INTEGRAL_EXTENSION_DEFAULT_METHODS E_INTEGRAL_EXTENSION_DEFAULT_METHODS
#endif

namespace enhanced {
    template <typename IntegralType>
    requires util::isIntegralType<IntegralType>
    struct Integral : public util::Comparable<Integral<IntegralType>> {
        IntegralType value;

        inline constexpr Integral() noexcept : value() {}

        inline constexpr Integral(IntegralType value) noexcept : value(value) {}

        inline constexpr Integral(const Integral& other) noexcept = default;

        inline constexpr Integral(Integral&& other) noexcept = default;

        E_ANNOTATE(RetNotIgnored)
        inline constexpr util::ComparisonResult compare(const Integral& other) const {
            return value == other.value ? util::ComparisonResult::EQUAL :
                (value > other.value ? util::ComparisonResult::GREATER : util::ComparisonResult::LESS);
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator+() const noexcept {
            return +value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator-() const noexcept {
            return -value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator+(const Integral& other) const noexcept {
            return value + other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator-(const Integral& other) const noexcept {
            return value - other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator*(const Integral& other) const noexcept {
            return value * other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator/(const Integral& other) const noexcept {
            return value / other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator%(const Integral& other) const noexcept {
            return value % other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator~() const noexcept {
            return ~value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator&(const Integral& other) const noexcept {
            return value & other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator|(const Integral& other) const noexcept {
            return value | other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator^(const Integral& other) const noexcept {
            return value ^ other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator<<(const Integral& other) const noexcept {
            return value << other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator>>(const Integral& other) const noexcept {
            return value >> other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator!() const noexcept {
            return !value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator&&(const Integral& other) const noexcept {
            return value && other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr Integral operator||(const Integral& other) const noexcept {
            return value || other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool operator<(const Integral& other) const noexcept {
            return value < other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool operator>(const Integral& other) const noexcept {
            return value > other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool operator<=(const Integral& other) const noexcept {
            return value <= other.value;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool operator>=(const Integral& other) const noexcept {
            return value >= other.value;
        }

        inline constexpr const Integral operator++(int) const noexcept {
            return value++;
        }

        inline constexpr const Integral operator--(int) const noexcept {
            return value--;
        }

        inline constexpr Integral& operator++() noexcept {
            return ++value;
        }

        inline constexpr Integral& operator--() noexcept {
            return --value;
        }

        inline constexpr Integral& operator+=(const Integral& other) noexcept {
            value += other.value;
            return *this;
        }

        inline constexpr Integral& operator-=(const Integral& other) noexcept {
            value -= other.value;
            return *this;
        }

        inline constexpr Integral& operator*=(const Integral& other) noexcept {
            value *= other.value;
            return *this;
        }

        inline constexpr Integral& operator/=(const Integral& other) noexcept {
            value /= other.value;
            return *this;
        }

        inline constexpr Integral& operator%=(const Integral& other) noexcept {
            value %= other.value;
            return *this;
        }

        inline constexpr Integral& operator&=(const Integral& other) noexcept {
            value &= other.value;
            return *this;
        }

        inline constexpr Integral& operator|=(const Integral& other) noexcept {
            value |= other.value;
            return *this;
        }

        inline constexpr Integral& operator^=(const Integral& other) noexcept {
            value ^= other.value;
            return *this;
        }

        inline constexpr Integral& operator<<=(const Integral& other) noexcept {
            value <<= other.value;
            return *this;
        }

        inline constexpr Integral& operator>>=(const Integral& other) noexcept {
            value >>= other.value;
            return *this;
        }

        inline constexpr Integral& operator=(const Integral& other) noexcept = default;

        inline constexpr Integral& operator=(Integral&& other) noexcept = default;
    };
}
