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

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>
#include <enhanced/collections/ArrayList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/util/Comparable.h>
#include <enhanced/math/LargeNumber.h>

namespace enhanced::math {
    class ENHANCED_CORE_API BinLargeNumber : public LargeNumber, public util::Comparable<BinLargeNumber> {
        template <typename NumberType>
        requires util::isIntegralType<NumberType>
        static inline BinLargeNumber from(NumberType number) {
            return {number};
        }

        BinLargeNumber(const String& number);

        BinLargeNumber(const BinLargeNumber& number);

        BinLargeNumber(BinLargeNumber&& number) noexcept;

        $NoIgnoreReturn
        ComparisonResult compare(const BinLargeNumber& other) const override;
    };
}

#define BIN_LARGE_NUM(number) enhanced::math::BinLargeNumber(#number)
