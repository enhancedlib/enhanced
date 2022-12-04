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

#include <enhanced/math/BcdLargeNumber.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/util/Traits.h>
#include <enhanced/exceptions/InvalidArgumentException.h>
#include <enhanced/exceptions/NotImplementedError.h>

using enhanced::util::move;
using enhanced::exceptions::InvalidArgumentException;

namespace enhanced::math {
    BcdLargeNumber::BcdLargeNumber(const String& number) : storage(number.getLength() + 1), isNegative(false), length(number.getLength()) {
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

    BcdLargeNumber::BcdLargeNumber(const BcdLargeNumber& other) = default;

    BcdLargeNumber::BcdLargeNumber(BcdLargeNumber&& other) noexcept :
        storage(move(other.storage)), isNegative(other.isNegative), length(other.length), point(other.point) {}

    BcdLargeNumber::ComparisonResult BcdLargeNumber::compare(const BcdLargeNumber& other) const {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber BcdLargeNumber::operator+() const {
        return *this;
    }

    BcdLargeNumber BcdLargeNumber::operator-() const {
        auto result = *this;
        result.isNegative ^= result.isNegative;
        return result;
    }

    BcdLargeNumber BcdLargeNumber::operator+(const BcdLargeNumber& number) const {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber BcdLargeNumber::operator-(const BcdLargeNumber& number) const {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber BcdLargeNumber::operator*(const BcdLargeNumber& number) const {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber BcdLargeNumber::operator/(const BcdLargeNumber& number) const {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber BcdLargeNumber::operator%(const BcdLargeNumber& number) const {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber& BcdLargeNumber::add(const BcdLargeNumber& number) {
        NOT_IMPLEMENTED();

        if (isNegative == number.isNegative) {
            for (sizetype index = 0; index < length; ++index) {
                storage[index] += number.storage[index];
                if (storage[index] >= 10) {
                    storage[index] -= 10;
                    storage[index + 1] += 1;
                }
            }
            storage[length - 1] += number.storage[length - 1];
            if (storage[length - 1] >= 10) {
                storage[length - 1] -= 10;
                storage.add(1);
                ++length;
            }

            return *this;
        }
    }

    BcdLargeNumber& BcdLargeNumber::sub(const BcdLargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber& BcdLargeNumber::mul(const BcdLargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber& BcdLargeNumber::div(const BcdLargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber& BcdLargeNumber::mod(const BcdLargeNumber &number) {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber& BcdLargeNumber::operator+=(const BcdLargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber& BcdLargeNumber::operator-=(const BcdLargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber& BcdLargeNumber::operator*=(const BcdLargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber& BcdLargeNumber::operator/=(const BcdLargeNumber& number) {
        NOT_IMPLEMENTED();
    }

    BcdLargeNumber& BcdLargeNumber::operator%=(const BcdLargeNumber& number) {
        NOT_IMPLEMENTED();
    }
}
