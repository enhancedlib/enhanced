/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
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
    length = count;
}

LargeInteger::LargeInteger(const String& number) : bytes(new byte[number.getLength()]), isNegative(false), length(number.getLength()) {}

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
