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

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#include "EnhancedBasic/math/LargeInteger.h"

using EnhancedBasic::Utility::LargeInteger;

LargeInteger::LargeInteger(Size size) :
    bytes(new Byte[size]), isNegative(0), size(size) {}

template <typename Type>
LargeInteger::LargeInteger(Type number) :
    bytes(null), isNegative(number < 0) {
    Size count = 1;
    Type value = number;
    while (value > 0) {
        value = value / 10;
        ++ count;
    }
    this->size = count;
}

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

LargeInteger EnhancedBasic::Utility::LargeInteger::newNumber(Size size) {
    return LargeInteger(size);
}
