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
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/String.h>
#include <enhanced/core/collections/ArrayList.h>
#include <enhanced/core/util/traits.h>
#include <enhanced/core/math/LargeInt.h>

namespace enhanced::core::math {
    class ENHANCED_CORE_API BCDLargeInt : public LargeInt {
    private:
        collections::ArrayList<byte> storage;

        bool isNegative;

        sizetype length = 0;

        template <typename NumberType>
        requires util::isIntegralType<NumberType>
        inline BCDLargeInt(NumberType number) : storage(0), isNegative(util::isSigned<NumberType> && number < 0) {
            sizetype count = 1;
            for (util::Conditional<util::isSigned<NumberType>, int64, uint64> value = number; value != 0; value /= 10, ++count);

            length = count;
            storage.expand(length + 1);
        }

    public:
        template <typename NumberType>
        requires util::isIntegralType<NumberType>
        static inline func from(NumberType number) -> BCDLargeInt {
            return {number};
        }

        BCDLargeInt(const String& number);

        BCDLargeInt(const BCDLargeInt& number);

        BCDLargeInt(BCDLargeInt&& number) noexcept;

        func compare(const SizeComparable& other) const -> ComparisonResult override;

        func operator+() const -> BCDLargeInt;

        func operator-() const -> BCDLargeInt;

        func operator+(const BCDLargeInt& number) const -> BCDLargeInt;

        func operator-(const BCDLargeInt& number) const -> BCDLargeInt;

        func operator*(const BCDLargeInt& number) const -> BCDLargeInt;

        func operator/(const BCDLargeInt& number) const -> BCDLargeInt;

        func operator%(const BCDLargeInt& number) const -> BCDLargeInt;

        func add(const BCDLargeInt& number) -> BCDLargeInt&;

        func sub(const BCDLargeInt& number) -> BCDLargeInt&;

        func mul(const BCDLargeInt& number) -> BCDLargeInt&;

        func div(const BCDLargeInt& number) -> BCDLargeInt&;

        func mod(const BCDLargeInt& number) -> BCDLargeInt&;

        func operator+=(const BCDLargeInt& number) -> BCDLargeInt&;

        func operator-=(const BCDLargeInt& number) -> BCDLargeInt&;

        func operator*=(const BCDLargeInt& number) -> BCDLargeInt&;

        func operator/=(const BCDLargeInt& number) -> BCDLargeInt&;

        func operator%=(const BCDLargeInt& number) -> BCDLargeInt&;
    };

    inline namespace literals {
        func operator""_li(const char* string, sizetype size) -> BCDLargeInt {
            return {String {string, size}};
        }
    }
}
