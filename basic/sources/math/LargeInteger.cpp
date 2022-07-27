/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/basic/math/LargeInteger.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"

using enhanced::basic::math::LargeInteger;
using enhanced::basic::String;

template <typename NumberType>
LargeInteger LargeInteger::from(NumberType number) {
    return LargeInteger(number);
}

LargeInteger::LargeInteger(uint64 number) : bytes(null), isNegative(number < 0) {
    Size count = 1;
    uint64 value = number;
    while (value > 0) {
        value = value / 10;
        ++count;
    }
    size = count;
}

LargeInteger::LargeInteger(const String& number) : bytes(new byte[number.getLength()]), isNegative(false), size(number.getLength()) {}

LargeInteger LargeInteger::add(LargeInteger number) {
    return *this;
}

LargeInteger LargeInteger::sub(LargeInteger number) {
    return *this;
}

LargeInteger LargeInteger::mul(LargeInteger number) {
    return *this;
}

LargeInteger LargeInteger::div(LargeInteger number) {
    return *this;
}
