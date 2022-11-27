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
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Iterator.h>

namespace enhanced {
    template <typename Type>
    interface Iterable {
    protected:
        class ForeachIterator final {
        private:
            const Iterator<Type>& iterator;

        public:
            inline explicit ForeachIterator(const Iterator<Type>& iterator) : iterator(iterator) {}

            inline func operator!=(byte) const -> bool {
                return iterator.hasNext();
            }

            inline func operator++() const -> const Iterator<Type>* {
                return iterator.next();
            }

            inline func operator*() const -> Type& {
                return iterator.get();
            }
        };

    public:
        $NoIgnoreReturn
        inline func begin() const -> Iterable<Type>::ForeachIterator {
            return Iterable<Type>::ForeachIterator(iterator());
        }

        $NoIgnoreReturn
        inline constexpr func end() const -> byte {
            return 0;
        }

        $NoIgnoreReturn
        virtual func iterator() const -> const Iterator<Type>& abstract;
    };
}
