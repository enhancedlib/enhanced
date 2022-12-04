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

namespace enhanced::util {
    template <typename Type>
    struct ENHANCED_CORE_API Comparable {
        enum class ComparisonResult : uint8 {
            EQUAL, MORE, LESS
        };

        $NoIgnoreReturn
        virtual ComparisonResult compare(const Type& other) const = 0;

        $NoIgnoreReturn
        inline bool equal(const Type& other) const {
            return compare(other) == ComparisonResult::EQUAL;
        }

        $NoIgnoreReturn
        inline bool operator==(const Type& other) const {
            return equal(other);
        }

        $NoIgnoreReturn
        inline bool operator!=(const Type& other) const {
            return !equal(other);
        }

        $NoIgnoreReturn
        inline bool operator<(const Type& other) const {
            return compare(other) == ComparisonResult::LESS;
        }

        $NoIgnoreReturn
        inline bool operator>(const Type& other) const {
            return compare(other) == ComparisonResult::MORE;
        }

        $NoIgnoreReturn
        inline bool operator<=(const Type& other) const {
            auto result = compare(other);
            return result == ComparisonResult::LESS || result == ComparisonResult::EQUAL;
        }

        $NoIgnoreReturn
        inline bool operator>=(const Type& other) const {
            auto result = compare(other);
            return result == ComparisonResult::MORE || result == ComparisonResult::EQUAL;
        }
    };
}
