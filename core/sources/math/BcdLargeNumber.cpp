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

using enhanced::exceptions::InvalidArgumentException;
using enhanced::util::move;

namespace enhanced::math {
    BcdLargeNumber::BcdLargeNumber(const String& number) : storage(number.getLength() + 1), isNegative(false), length(number.getLength()) {
        sizetype index;
        if (number[0] == '-') {
            index = 1;
            isNegative = true;
        } else if (number[0] == '+') index = 1;
        else index = 0;

        for (; index < length; ++index) {
            storage.add(number[index] - '0');
            if (storage[index] >= 10) { // Out of the range.
                throw InvalidArgumentException("Each character in the string must be a number except the first character can be + or -");
            }
        }
    }

    BcdLargeNumber::BcdLargeNumber(const BcdLargeNumber& number) = default;

    BcdLargeNumber::BcdLargeNumber(BcdLargeNumber&& number) noexcept :
        storage(move(number.storage)), isNegative(number.isNegative), length(number.length) {}

    func BcdLargeNumber::compare(const Comparable& other) const -> ComparisonResult {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::operator+() const -> BcdLargeNumber {
        return *this;
    }

    func BcdLargeNumber::operator-() const -> BcdLargeNumber {
        let result = *this;
        result.isNegative ^= result.isNegative;
        return result;
    }

    func BcdLargeNumber::operator+(const BcdLargeNumber& number) const -> BcdLargeNumber {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::operator-(const BcdLargeNumber& number) const -> BcdLargeNumber {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::operator*(const BcdLargeNumber& number) const -> BcdLargeNumber {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::operator/(const BcdLargeNumber& number) const -> BcdLargeNumber {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::operator%(const BcdLargeNumber& number) const -> BcdLargeNumber {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::add(const BcdLargeNumber& number) -> BcdLargeNumber& {
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

    func BcdLargeNumber::sub(const BcdLargeNumber& number) -> BcdLargeNumber& {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::mul(const BcdLargeNumber& number) -> BcdLargeNumber& {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::div(const BcdLargeNumber& number) -> BcdLargeNumber& {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::mod(const BcdLargeNumber &number) -> BcdLargeNumber& {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::operator+=(const BcdLargeNumber& number) -> BcdLargeNumber& {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::operator-=(const BcdLargeNumber& number) -> BcdLargeNumber& {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::operator*=(const BcdLargeNumber& number) -> BcdLargeNumber& {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::operator/=(const BcdLargeNumber& number) -> BcdLargeNumber& {
        NOT_IMPLEMENTED();
    }

    func BcdLargeNumber::operator%=(const BcdLargeNumber& number) -> BcdLargeNumber& {
        NOT_IMPLEMENTED();
    }
}
