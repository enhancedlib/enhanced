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
