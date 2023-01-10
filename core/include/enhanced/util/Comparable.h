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

namespace enhanced::util {
    template <typename Type>
    struct ENHANCED_CORE_API Comparable {
        enum class ComparisonResult : int8 {
            EQUAL = 0, LESS = -1, GREATER = 1
        };

        [[RetNotIgnored]]
        inline constexpr bool equal(const Type& other) const {
            return Type::compare(other) == ComparisonResult::EQUAL;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator==(const Type& other) const {
            return equal(other);
        }

        [[RetNotIgnored]]
        inline constexpr bool operator!=(const Type& other) const {
            return !equal(other);
        }

        [[RetNotIgnored]]
        inline constexpr bool operator<(const Type& other) const {
            return Type::compare(other) == ComparisonResult::LESS;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator>(const Type& other) const {
            return Type::compare(other) == ComparisonResult::GREATER;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator<=(const Type& other) const {
            auto result = Type::compare(other);
            return result == ComparisonResult::LESS || result == ComparisonResult::EQUAL;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator>=(const Type& other) const {
            auto result = Type::compare(other);
            return result == ComparisonResult::GREATER || result == ComparisonResult::EQUAL;
        }

        [[RetNotIgnored]]
        inline constexpr ComparisonResult operator<=>(const Type& other) const {
            return Type::compare(other);
        }
    };
}
