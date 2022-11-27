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

#include <enhanced/math/BCDLargeInt.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/util/Traits.h>
#include <enhanced/exceptions/InvalidArgumentException.h>
#include <enhanced/exceptions/NotImplementedError.h>

using enhanced::exceptions::InvalidArgumentException;
using enhanced::util::move;

namespace enhanced::math {
    BCDLargeInt::BCDLargeInt(const String& number) : storage(number.getLength() + 1), isNegative(false), length(number.getLength()) {
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

    BCDLargeInt::BCDLargeInt(const BCDLargeInt& number) = default;

    BCDLargeInt::BCDLargeInt(BCDLargeInt&& number) noexcept :
        storage(move(number.storage)), isNegative(number.isNegative), length(number.length) {}

    func BCDLargeInt::compare(const Comparable& other) const -> ComparisonResult {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::operator+() const -> BCDLargeInt {
        return *this;
    }

    func BCDLargeInt::operator-() const -> BCDLargeInt {
        let result = *this;
        result.isNegative ^= result.isNegative;
        return result;
    }

    func BCDLargeInt::operator+(const BCDLargeInt& number) const -> BCDLargeInt {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::operator-(const BCDLargeInt& number) const -> BCDLargeInt {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::operator*(const BCDLargeInt& number) const -> BCDLargeInt {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::operator/(const BCDLargeInt& number) const -> BCDLargeInt {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::operator%(const BCDLargeInt& number) const -> BCDLargeInt {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::add(const BCDLargeInt& number) -> BCDLargeInt& {
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

    func BCDLargeInt::sub(const BCDLargeInt& number) -> BCDLargeInt& {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::mul(const BCDLargeInt& number) -> BCDLargeInt& {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::div(const BCDLargeInt& number) -> BCDLargeInt& {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::mod(const BCDLargeInt &number) -> BCDLargeInt& {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::operator+=(const BCDLargeInt& number) -> BCDLargeInt& {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::operator-=(const BCDLargeInt& number) -> BCDLargeInt& {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::operator*=(const BCDLargeInt& number) -> BCDLargeInt& {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::operator/=(const BCDLargeInt& number) -> BCDLargeInt& {
        NOT_IMPLEMENTED();
    }

    func BCDLargeInt::operator%=(const BCDLargeInt& number) -> BCDLargeInt& {
        NOT_IMPLEMENTED();
    }
}
