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

#include <enhanced/math/LargeNumber.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/util/Traits.h>
#include <enhanced/exceptions/InvalidArgumentException.h>
#include <enhanced/exceptions/NotImplementedError.h>

using enhanced::util::move;
using enhanced::exceptions::InvalidArgumentException;

namespace enhanced::math {
    LargeNumber::LargeNumber(const String& number) : storage(number.getLength() + 1), isNegative(false), length(number.getLength()) {
        sizetype start;
        if (number[0] == '-') {
            start = 1;
            isNegative = true;
        } else if (number[0] == '+') start = 1;
        else start = 0;

        for (sizetype index = start; index < length; ++index) {
            if (number[index] == '.' && index != start && index != length - 1 && point == 0) {
                point = index;
            } else if (storage[index] < 10) {
                storage.add(number[index] - '0');
            } else { // Out of the range.
                throw InvalidArgumentException("Each character in the string must be a number except"
                    "the first character can be + or - and a point (.) between two number bits");
            }
        }
    }

    LargeNumber::LargeNumber(const LargeNumber& other) = default;

    LargeNumber::LargeNumber(LargeNumber&& other) noexcept :
        storage(move(other.storage)), isNegative(other.isNegative), length(other.length), point(other.point) {}

    LargeNumber::ComparisonResult LargeNumber::compare(const LargeNumber& other) const {
        NOT_IMPLEMENTED();
    }

    LargeNumber LargeNumber::operator+() const {
        return *this;
    }

    LargeNumber LargeNumber::operator-() const {
        auto result = *this;
        result.isNegative ^= result.isNegative;
        return result;
    }

    LargeNumber LargeNumber::operator+(const LargeNumber& number) const {
        NOT_IMPLEMENTED();
    }

    LargeNumber LargeNumber::operator-(const LargeNumber& number) const {
        NOT_IMPLEMENTED();
    }

    LargeNumber LargeNumber::operator*(const LargeNumber& number) const {
        NOT_IMPLEMENTED();
    }

    LargeNumber LargeNumber::operator/(const LargeNumber& number) const {
        NOT_IMPLEMENTED();
    }

    LargeNumber LargeNumber::operator%(const LargeNumber& number) const {
        NOT_IMPLEMENTED();
    }

    LargeNumber& LargeNumber::add(const LargeNumber& number) {
        NOT_IMPLEMENTED();

        //if (isNegative == number.isNegative) {
        //    for (sizetype index = 0; index < length; ++index) {
        //        storage[index] += number.storage[index];
        //        if (storage[index] >= 10) {
        //            storage[index] -= 10;
        //            storage[index + 1] += 1;
        //        }
        //    }
        //    storage[length - 1] += number.storage[length - 1];
        //    if (storage[length - 1] >= 10) {
        //        storage[length - 1] -= 10;
        //        storage.add(1);
        //        ++length;
        //    }
        //    return *this;
        //}
    }

    LargeNumber& LargeNumber::sub(const LargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    LargeNumber& LargeNumber::mul(const LargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    LargeNumber& LargeNumber::div(const LargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    LargeNumber& LargeNumber::mod(const LargeNumber &number) {
        NOT_IMPLEMENTED();
    }

    LargeNumber& LargeNumber::operator+=(const LargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    LargeNumber& LargeNumber::operator-=(const LargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    LargeNumber& LargeNumber::operator*=(const LargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    LargeNumber& LargeNumber::operator/=(const LargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    LargeNumber& LargeNumber::operator%=(const LargeNumber& number) {
        NOT_IMPLEMENTED();
    }
}
