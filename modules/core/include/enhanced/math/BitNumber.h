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
#include <enhanced/String.h>
#include <enhanced/util/Traits.h>
#include <enhanced/util/Comparable.h>
#include <enhanced/collections/ArrayList.h>

#define E_BIT_NUM(NUMBER) enhanced::math::BitNumber(#NUMBER)

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define BIT_NUM E_BIT_NUM
#endif

namespace enhanced::math {
    class E_CORE_API BitNumber : public util::Comparable<BitNumber> {
    private:
        collections::ArrayList<byte> bits;

    public:
        template <typename NumberType>
        requires util::isIntegralType<NumberType>
        static inline BitNumber from(NumberType number) {
            return {number};
        }

        BitNumber(const String& number);

        BitNumber(const BitNumber& number);

        BitNumber(BitNumber&& number) noexcept;

        E_ANNOTATE(RetNotIgnored)
        util::ComparisonResult compare(const BitNumber& other) const;
    };
}
