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

namespace enhanced::util {
    enum class ComparisonResult : int8 {
        EQUAL = 0, LESS = -1, GREATER = 1
    };

    template <typename Type>
    struct Comparable {
        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool equal(const Type& other) const {
            return static_cast<const Type*>(this)->compare(other) == ComparisonResult::EQUAL;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool operator==(const Type& other) const {
            return equal(other);
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool operator!=(const Type& other) const {
            return !equal(other);
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool operator<(const Type& other) const {
            return static_cast<const Type*>(this)->compare(other) == ComparisonResult::LESS;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool operator>(const Type& other) const {
            return static_cast<const Type*>(this)->compare(other) == ComparisonResult::GREATER;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool operator<=(const Type& other) const {
            auto result = static_cast<const Type*>(this)->compare(other);
            return result == ComparisonResult::LESS || result == ComparisonResult::EQUAL;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr bool operator>=(const Type& other) const {
            auto result = static_cast<const Type*>(this)->compare(other);
            return result == ComparisonResult::GREATER || result == ComparisonResult::EQUAL;
        }

        E_ANNOTATE(RetNotIgnored)
        inline constexpr ComparisonResult operator<=>(const Type& other) const {
            return static_cast<const Type*>(this)->compare(other);
        }
    };
}
