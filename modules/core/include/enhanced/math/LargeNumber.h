/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
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

#define E_LARGE_NUM(NUMBER) enhanced::math::LargeNumber(#NUMBER)

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define LARGE_NUM E_LARGE_NUM
#endif

namespace enhanced::math {
    class E_CORE_API LargeNumber : public util::Comparable<LargeNumber> {
    private:
        E_MSVC_WARNING_PAD(4251)

        collections::ArrayList<byte> storage;

        E_MSVC_WARNING_POP

        bool isNegative;

        sizetype length = 0;

        sizetype point = 0;

        template <typename NumberType>
        requires util::isIntegralType<NumberType>
        inline LargeNumber(NumberType number) : storage(0), isNegative(util::isSigned<NumberType> && number < 0) {
            sizetype count = 1;
            for (NumberType value = number; value != 0; value /= 10, ++count);

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

        E_ANNOTATE(RetNotIgnored)
        util::ComparisonResult compare(const LargeNumber& other) const;

        LargeNumber operator+() const;

        LargeNumber operator-() const;

        LargeNumber operator+(const LargeNumber& number) const;

        LargeNumber operator-(const LargeNumber& number) const;

        LargeNumber operator*(const LargeNumber& number) const;

        LargeNumber operator/(const LargeNumber& number) const;

        LargeNumber operator%(const LargeNumber& number) const;

        LargeNumber& operator+=(const LargeNumber& number);

        LargeNumber& operator-=(const LargeNumber& number);

        LargeNumber& operator*=(const LargeNumber& number);

        LargeNumber& operator/=(const LargeNumber& number);

        LargeNumber& operator%=(const LargeNumber& number);
    };
}
