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
