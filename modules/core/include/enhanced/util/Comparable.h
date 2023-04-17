/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>

namespace enhanced::util {
    enum class ComparisonResult : int8 {
        EQUAL = 0, LESS = -1, GREATER = 1
    };

    template <typename Type>
    struct Comparable {
        [[RetNotIgnored]]
        inline constexpr bool equal(const Type& other) const {
            return static_cast<const Type*>(this)->compare(other) == ComparisonResult::EQUAL;
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
            return static_cast<const Type*>(this)->compare(other) == ComparisonResult::LESS;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator>(const Type& other) const {
            return static_cast<const Type*>(this)->compare(other) == ComparisonResult::GREATER;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator<=(const Type& other) const {
            auto result = static_cast<const Type*>(this)->compare(other);
            return result == ComparisonResult::LESS || result == ComparisonResult::EQUAL;
        }

        [[RetNotIgnored]]
        inline constexpr bool operator>=(const Type& other) const {
            auto result = static_cast<const Type*>(this)->compare(other);
            return result == ComparisonResult::GREATER || result == ComparisonResult::EQUAL;
        }

        [[RetNotIgnored]]
        inline constexpr ComparisonResult operator<=>(const Type& other) const {
            return static_cast<const Type*>(this)->compare(other);
        }
    };
}
