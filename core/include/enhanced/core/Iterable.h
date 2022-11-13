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
#include <enhanced/core/Iterator.h>

namespace enhanced::core {
    template <typename Type>
    interface Iterable {
    protected:
        class ForeachIterator final {
        private:
            const Iterator<Type>& iterator;

        public:
            explicit ForeachIterator(const Iterator<Type>& iterator) : iterator(iterator) {}

            func operator!=(byte) const -> bool {
                return iterator.hasNext();
            }

            func operator++() const -> const Iterator<Type>* {
                return iterator.next();
            }

            func operator*() const -> Type& {
                return iterator.get();
            }
        };

    public:
        $(NoIgnoreReturn)
        virtual inline func begin() const -> Iterable<Type>::ForeachIterator {
            return Iterable<Type>::ForeachIterator(iterator());
        }

        $(NoIgnoreReturn)
        virtual inline constexpr func end() const -> byte {
            return 0;
        }

        virtual func iterator() const -> const Iterator<Type>& = abstract;
    };
}
