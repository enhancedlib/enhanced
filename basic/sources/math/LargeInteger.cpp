/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#include "Enhanced/basic/math/LargeInteger.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"

using Enhanced::basic::math::LargeInteger;
using Enhanced::basic::core::String;

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

LargeInteger::LargeInteger(const String& number) : bytes(new Byte[number.getLength()]), isNegative(false), size(number.getLength()) {}

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
