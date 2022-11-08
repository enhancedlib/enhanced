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

#include <enhanced/core/math/LargeInteger.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/exception/InvalidArgumentException.h>
#include <enhanced/core/exception/NotImplementedError.h>

using enhanced::core::math::LargeInteger;
using enhanced::core::String;
using enhanced::core::exception::InvalidArgumentException;

template <typename NumberType>
LargeInteger LargeInteger::from(NumberType number) {
    return LargeInteger(number);
}

LargeInteger::LargeInteger(uint64 number) : storage(0), isNegative(number < 0) {
    sizetype count = 1;
    for (uint64 value = number; value > 0; value /= 10) ++count;

    length = count;
    storage.expand(length + 1);
}

LargeInteger::LargeInteger(const String& number) : storage(number.getLength() + 1), isNegative(false), length(number.getLength()) {
    sizetype index;
    if (number[0] == '-') {
        index = 1;
        isNegative = true;
    } else if (number[0] == '+') index = 1;
    else index = 0;

    for (; index < length; ++index) {
        storage[index] = number[index] - '0';
        if (storage[index] >= 10) { // Out of the range.
            throw InvalidArgumentException("Each character in the string must be a number (except the first character can be + or -)");
        }
    }
}

LargeInteger LargeInteger::operator+(LargeInteger& number) const {
    NOT_IMPLEMENTED();
}

LargeInteger LargeInteger::operator-(LargeInteger& number) const {
    NOT_IMPLEMENTED();
}

LargeInteger LargeInteger::operator*(LargeInteger& number) const {
    NOT_IMPLEMENTED();
}

LargeInteger LargeInteger::operator/(LargeInteger& number) const {
    NOT_IMPLEMENTED();
}

LargeInteger LargeInteger::operator%(LargeInteger& number) const {
    NOT_IMPLEMENTED();
}

LargeInteger& LargeInteger::add(LargeInteger& number) {
    for (sizetype index = 0; index < length; ++index) {
        storage[index] += number.storage[index];
        if (storage[index] >= 10) {
            storage[index] -= 10;
            if ((index + 1) == length) {
                storage.add(1);
            } else {
                storage[index + 1] += 1;
            }
        }
    }

    return *this;
}

LargeInteger& LargeInteger::sub(LargeInteger& number) {
    NOT_IMPLEMENTED();
}

LargeInteger& LargeInteger::mul(LargeInteger& number) {
    NOT_IMPLEMENTED();
}

LargeInteger& LargeInteger::div(LargeInteger& number) {
    NOT_IMPLEMENTED();
}

LargeInteger& LargeInteger::operator+=(LargeInteger& number) {
    NOT_IMPLEMENTED();
}

LargeInteger& LargeInteger::operator-=(LargeInteger& number) {
    NOT_IMPLEMENTED();
}

LargeInteger& LargeInteger::operator*=(LargeInteger& number) {
    NOT_IMPLEMENTED();
}

LargeInteger& LargeInteger::operator/=(LargeInteger& number) {
    NOT_IMPLEMENTED();
}

LargeInteger& LargeInteger::operator%=(LargeInteger& number) {
    NOT_IMPLEMENTED();
}
