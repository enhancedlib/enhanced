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
#include <enhanced/math/LargeNumber.h>

namespace enhanced::math {
    class ENHANCED_CORE_API BcdLargeNumber : public LargeNumber {
    private:
        MSVC_WARNING_PUSH MSVC_WARNING_DISABLE(4251)

        collections::ArrayList<byte> storage;

        MSVC_WARNING_POP

        bool isNegative;

        sizetype length = 0;

        template <typename NumberType>
        requires util::isIntegralType<NumberType>
        inline BcdLargeNumber(NumberType number) : storage(0), isNegative(util::isSigned<NumberType> && number < 0) {
            sizetype count = 1;
            for (util::Conditional<util::isSigned<NumberType>, int64, uint64> value = number; value != 0; value /= 10, ++count);

            length = count;
            storage.expand(length + 1);
        }

    public:
        template <typename NumberType>
        requires util::isIntegralType<NumberType>
        static inline func from(NumberType number) -> BcdLargeNumber {
            return {number};
        }

        BcdLargeNumber(const String& number);

        BcdLargeNumber(const BcdLargeNumber& number);

        BcdLargeNumber(BcdLargeNumber&& number) noexcept;

        func compare(const Comparable& other) const -> ComparisonResult override;

        func operator+() const -> BcdLargeNumber;

        func operator-() const -> BcdLargeNumber;

        func operator+(const BcdLargeNumber& number) const -> BcdLargeNumber;

        func operator-(const BcdLargeNumber& number) const -> BcdLargeNumber;

        func operator*(const BcdLargeNumber& number) const -> BcdLargeNumber;

        func operator/(const BcdLargeNumber& number) const -> BcdLargeNumber;

        func operator%(const BcdLargeNumber& number) const -> BcdLargeNumber;

        func add(const BcdLargeNumber& number) -> BcdLargeNumber&;

        func sub(const BcdLargeNumber& number) -> BcdLargeNumber&;

        func mul(const BcdLargeNumber& number) -> BcdLargeNumber&;

        func div(const BcdLargeNumber& number) -> BcdLargeNumber&;

        func mod(const BcdLargeNumber& number) -> BcdLargeNumber&;

        func operator+=(const BcdLargeNumber& number) -> BcdLargeNumber&;

        func operator-=(const BcdLargeNumber& number) -> BcdLargeNumber&;

        func operator*=(const BcdLargeNumber& number) -> BcdLargeNumber&;

        func operator/=(const BcdLargeNumber& number) -> BcdLargeNumber&;

        func operator%=(const BcdLargeNumber& number) -> BcdLargeNumber&;
    };
}

#define BCD_LARGE_NUM(number) enhanced::math::BcdLargeNumber(#number)
