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
#include <enhanced/core/annotations.h>
#include <enhanced/core/util/Comparable.h>
#include <enhanced/core/util/Pair.h>
#include <enhanced/core/exception/UnsupportedOperationException.h>

namespace enhanced::core::util {
    interface SizeComparable : Comparable {
        scopedenum ComparisonResult : uint8 {
            EQUAL, MORE, LESS
        };

        $(NoIgnoreReturn)
        virtual func compare(const SizeComparable& other) const -> ComparisonResult = abstract;

        $(NoIgnoreReturn)
        inline func equal(const Comparable& other) const -> bool override {
            return compare((const SizeComparable&) other) == ComparisonResult::EQUAL;
        }

        $(NoIgnoreReturn)
        inline func operator<(const SizeComparable& other) const -> bool {
            return compare(other) == ComparisonResult::LESS;
        }

        $(NoIgnoreReturn)
        inline func operator>(const SizeComparable& other) const -> bool {
            return compare(other) == ComparisonResult::MORE;
        }

        $(NoIgnoreReturn)
        inline func operator<=(const SizeComparable& other) const -> bool {
            let result = compare(other);
            return result == ComparisonResult::LESS || result == ComparisonResult::EQUAL;
        }

        $(NoIgnoreReturn)
        inline func operator>=(const SizeComparable& other) const -> bool {
            let result = compare(other);
            return result == ComparisonResult::MORE || result == ComparisonResult::EQUAL;
        }
    };
}
