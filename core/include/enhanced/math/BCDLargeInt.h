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
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/collections/ArrayList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/math/LargeInt.h>

namespace enhanced::math {
    class ENHANCED_CORE_API BCDLargeInt : public LargeInt {
    private:
        MSVC_WARNING_PUSH MSVC_WARNING_DISABLE(4251)

        collections::ArrayList<byte> storage;

        MSVC_WARNING_POP

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

        func compare(const Comparable& other) const -> ComparisonResult override;

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
}

#define BCD_LARGE_INT(number) enhanced::math::BCDLargeInt(#number)
