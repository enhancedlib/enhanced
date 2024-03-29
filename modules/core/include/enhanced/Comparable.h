/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software.
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
#include <enhanced/CoreAPI.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/TraitInterface.h>

namespace enhanced {
    enum class ComparisonResult : int8 {
        EQUAL = 0, LESS = -1, GREATER = 1
    };

    E_TRAIT_INTERFACE()
    class Comparable {
        E_CLASS(Comparable)

    E_CLASS_HEADER
        E_TRAIT_INTERFACE_METHOD(compare, ComparisonResult, (const E_TRAIT_INTERFACE_IMPL_CLASS&), const)

    E_CLASS_BODY
        using Type = E_TRAIT_INTERFACE_IMPL_CLASS;

        E_RET_NO_DISCARD()
        inline constexpr bool equal(const Type& other) const {
            return compare(other) == ComparisonResult::EQUAL;
        }

        E_RET_NO_DISCARD()
        inline constexpr bool notEqual(const Type& other) const {
            return !equal(other);
        }

        E_RET_NO_DISCARD()
        inline constexpr bool greater(const Type& other) const {
            return compare(other) == ComparisonResult::GREATER;
        }

        E_RET_NO_DISCARD()
        inline constexpr bool less(const Type& other) const {
            return compare(other) == ComparisonResult::LESS;
        }

        E_RET_NO_DISCARD()
        inline constexpr bool greaterOrEqual(const Type& other) const {
            auto result = compare(other);
            return result == ComparisonResult::GREATER || result == ComparisonResult::EQUAL;
        }

        E_RET_NO_DISCARD()
        inline constexpr bool lessOrEqual(const Type& other) const {
            auto result = compare(other);
            return result == ComparisonResult::LESS || result == ComparisonResult::EQUAL;
        }

        E_RET_NO_DISCARD()
        inline constexpr bool operator==(const Type& other) const {
            return equal(other);
        }

        E_RET_NO_DISCARD()
        inline constexpr bool operator!=(const Type& other) const {
            return notEqual(other);
        }

        E_RET_NO_DISCARD()
        inline constexpr bool operator>(const Type& other) const {
            return greater(other);
        }

        E_RET_NO_DISCARD()
        inline constexpr bool operator<(const Type& other) const {
            return less(other);
        }

        E_RET_NO_DISCARD()
        inline constexpr bool operator>=(const Type& other) const {
            return greaterOrEqual(other);
        }

        E_RET_NO_DISCARD()
        inline constexpr bool operator<=(const Type& other) const {
            return lessOrEqual(other);
        }

        E_RET_NO_DISCARD()
        inline constexpr ComparisonResult operator<=>(const Type& other) const {
            return compare(other);
        }
    };
}
