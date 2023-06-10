/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
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
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
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
