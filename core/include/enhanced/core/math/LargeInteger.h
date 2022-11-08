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

#pragma once

#include <enhanced/core/defines.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/String.h>
#include <enhanced/core/collections/ArrayList.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L3_BEGIN(enhanced, core, math)

class ENHANCED_CORE_API LargeInteger {
private:
    collections::ArrayList<byte> storage;

    bool isNegative;

    sizetype length;

    LargeInteger(uint64 number);

public:
    template <typename NumberType>
    static LargeInteger from(NumberType number);

    LargeInteger(const enhanced::core::String& number);

    LargeInteger operator+(LargeInteger& number) const;

    LargeInteger operator-(LargeInteger& number) const;

    LargeInteger operator*(LargeInteger& number) const;

    LargeInteger operator/(LargeInteger& number) const;

    LargeInteger operator%(LargeInteger& number) const;

    LargeInteger& add(LargeInteger& number);

    LargeInteger& sub(LargeInteger& number);

    LargeInteger& mul(LargeInteger& number);

    LargeInteger& div(LargeInteger& number);

    LargeInteger& mod(LargeInteger& number);

    LargeInteger& operator+=(LargeInteger& number);

    LargeInteger& operator-=(LargeInteger& number);

    LargeInteger& operator*=(LargeInteger& number);

    LargeInteger& operator/=(LargeInteger& number);

    LargeInteger& operator%=(LargeInteger& number);
};

NAMESPACE_L3_END

#endif
