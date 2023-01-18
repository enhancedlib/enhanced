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
#include <enhanced/String.h>
#include <enhanced/util/Traits.h>
#include <enhanced/util/Comparable.h>
#include <enhanced/collections/ArrayList.h>

namespace enhanced::math {
    class ENHANCED_CORE_API BitNumber : public util::Comparable<BitNumber> {
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

        [[RetNotIgnored]]
        util::ComparisonResult compare(const BitNumber& other) const;
    };
}

#define E_BIT_NUM(NUMBER) enhanced::math::BitNumber(#NUMBER)

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define BIT_NUM E_BIT_NUM
#endif
