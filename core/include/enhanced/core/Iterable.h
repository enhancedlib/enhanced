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
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/Iterator.h>

#ifdef CXX_LANGUAGE

namespace enhanced::core {
    template <typename Type>
    struct AbstractClass Iterable {
    protected:
        class ForeachIterator final {
        private:
            Iterator<Type>* iterator;

        public:
            explicit ForeachIterator(Iterator<Type>* iterator) : iterator(iterator) {}

            bool operator!=(byte) {
                return iterator->hasNext();
            }

            const Iterator<Type>* operator++() {
                return iterator->next();
            }

            Type& operator*() {
                return iterator->get();
            }
        };

        template <typename IteratorType, typename IteratorImplType, typename DerivedClass>
        inline IteratorType* getIterator(IteratorImplType*& iterator, const DerivedClass* derivedClassObject) const {
            if (iterator == null) iterator = new IteratorType(derivedClassObject);
            else static_cast<IteratorType*>(iterator)->reset();

            return static_cast<IteratorType*>(iterator);
        }

    public:
        RetCannotIgnored
        virtual inline Iterable<Type>::ForeachIterator begin() const {
            return Iterable<Type>::ForeachIterator(iterator());
        }

        RetCannotIgnored
        virtual inline byte end() const {
            return 0;
        }

        virtual Iterator<Type>* iterator() const = 0;
    };
}

#endif
