/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>
#include <enhanced/String.h>
#include <enhanced/util/Traits.h>
#include <enhanced/util/Comparable.h>
#include <enhanced/collections/ArrayList.h>
#include <enhanced/math/Number.h>

namespace enhanced::math {
    class ENHANCED_CORE_API LargeNumber : public Number, public util::Comparable<LargeNumber> {
    private:
        MSVC_WARNING_PUSH_AND_DISABLE(4251)

        collections::ArrayList<byte> storage;

        MSVC_WARNING_POP

        bool isNegative;

        sizetype length = 0;

        sizetype point = 0;

        template <typename NumberType>
        requires util::isIntegralType<NumberType>
        inline LargeNumber(NumberType number) : storage(0), isNegative(util::isSigned<NumberType> && number < 0) {
            sizetype count = 1;
            for (util::Conditional<util::isSigned<NumberType>, int64, uint64> value = number; value != 0; value /= 10, ++count);

            length = count;
            storage.expand(length + 1);
        }

    public:
        template <typename NumberType>
        requires util::isIntegralType<NumberType>
        static inline LargeNumber from(NumberType number) {
            return {number};
        }

        LargeNumber(const String& number);

        LargeNumber(const LargeNumber& other);

        LargeNumber(LargeNumber&& other) noexcept;

        $NoIgnoreReturn
        ComparisonResult compare(const LargeNumber& other) const override;

        LargeNumber operator+() const;

        LargeNumber operator-() const;

        LargeNumber operator+(const LargeNumber& number) const;

        LargeNumber operator-(const LargeNumber& number) const;

        LargeNumber operator*(const LargeNumber& number) const;

        LargeNumber operator/(const LargeNumber& number) const;

        LargeNumber operator%(const LargeNumber& number) const;

        LargeNumber& add(const LargeNumber& number);

        LargeNumber& sub(const LargeNumber& number);

        LargeNumber& mul(const LargeNumber& number);

        LargeNumber& div(const LargeNumber& number);

        LargeNumber& mod(const LargeNumber& number);

        LargeNumber& operator+=(const LargeNumber& number);

        LargeNumber& operator-=(const LargeNumber& number);

        LargeNumber& operator*=(const LargeNumber& number);

        LargeNumber& operator/=(const LargeNumber& number);

        LargeNumber& operator%=(const LargeNumber& number);
    };
}

#define E_LARGE_NUM(NUMBER) enhanced::math::LargeNumber(#NUMBER)

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define LARGE_NUM E_LARGE_NUM
#endif
