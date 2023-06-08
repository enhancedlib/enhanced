/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute, subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not charge any fees or receive other compensation for the
 *    distribution of the Software.
 *
 * 3. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 4. If you use this Software in your product, you should indicate the it in
 *    the product documentation.
 *
 * Unless you have obtained the written consent of the copyright holders,
 * you may not break these restrictions.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
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
