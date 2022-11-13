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
#include <enhanced/core/types.h>
#include <enhanced/core/String.h>
#include <enhanced/core/collections/ArrayList.h>

namespace enhanced::core::math {
    class ENHANCED_CORE_API LargeInteger {
    private:
        collections::ArrayList<byte> storage;

        bool isNegative;

        sizetype length;

        LargeInteger(uint64 number);

    public:
        template <typename NumberType>
        static func from(NumberType number) -> LargeInteger;

        LargeInteger(const enhanced::core::String& number);

        func operator+(LargeInteger& number) const -> LargeInteger;

        func operator-(LargeInteger& number) const -> LargeInteger;

        func operator*(LargeInteger& number) const -> LargeInteger;

        func operator/(LargeInteger& number) const -> LargeInteger;

        func operator%(LargeInteger& number) const -> LargeInteger;

        func add(LargeInteger& number) -> LargeInteger&;

        func sub(LargeInteger& number) -> LargeInteger&;

        func mul(LargeInteger& number) -> LargeInteger&;

        func div(LargeInteger& number) -> LargeInteger&;

        func mod(LargeInteger& number) -> LargeInteger&;

        func operator+=(LargeInteger& number) -> LargeInteger&;

        func operator-=(LargeInteger& number) -> LargeInteger&;

        func operator*=(LargeInteger& number) -> LargeInteger&;

        func operator/=(LargeInteger& number) -> LargeInteger&;

        func operator%=(LargeInteger& number) -> LargeInteger&;
    };
}
