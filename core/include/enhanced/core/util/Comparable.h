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

namespace enhanced::core::util {
    interface Comparable {
        struct CompareResult {
            scopedenum ResultType {
                EQUAL, MORE, LESS
            };

            ResultType type;

            sizetype difference;

            inline CompareResult(ResultType type, sizetype difference) : type(type), difference(difference) {}

            $(NoIgnoreReturn)
            inline func equal() const -> bool {
                return type == ResultType::EQUAL;
            }

            $(NoIgnoreReturn)
            inline func more() const -> bool {
                return type == ResultType::MORE;
            }

            $(NoIgnoreReturn)
            inline func moreOrEqual() const -> bool {
                return type == ResultType::MORE || type == ResultType::EQUAL;
            }

            $(NoIgnoreReturn)
            inline func less() const -> bool {
                return type == ResultType::LESS;
            }

            $(NoIgnoreReturn)
            inline func lessOrEqual() const -> bool {
                return type == ResultType::LESS || type == ResultType::EQUAL;
            }
        };

        $(NoIgnoreReturn)
        virtual func equal(const Comparable& other) const -> bool = abstract;

        $(NoIgnoreReturn)
        virtual func compare(const Comparable& other) const -> CompareResult = abstract;

        $(NoIgnoreReturn)
        inline func operator==(const Comparable& other) const -> bool {
            return equal(other);
        }

        $(NoIgnoreReturn)
        inline func operator!=(const Comparable& other) const -> bool {
            return !equal(other);
        }

        $(NoIgnoreReturn)
        inline func operator<=(const Comparable& other) const -> bool {
            return compare(other).lessOrEqual();
        }

        $(NoIgnoreReturn)
        inline func operator>(const Comparable& other) const -> bool {
            return compare(other).moreOrEqual();
        }

        $(NoIgnoreReturn)
        inline func operator>=(const Comparable& other) const -> bool {
            return compare(other).moreOrEqual();
        }

        $(NoIgnoreReturn)
        inline func operator<(const Comparable& other) const -> bool {
            return compare(other).less();
        }
    };
}
