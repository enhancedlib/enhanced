/*
 * Copyright (C) 2021 Liu Baihao. All rights reserved.
 * This product is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#include "EnhancedBasic/math/LargeInteger.h"

using EnhancedBasic::Utility::LargeInteger;

LargeInteger::LargeInteger(Size size) :
    bytes(new Byte[size]), isNegative(0), size(size) {
}

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

template LargeInteger::LargeInteger(int number);

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
