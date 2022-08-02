/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#include "Iterator.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic {
    template <typename Type>
    struct Iterable {
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

        template <typename IteratorType, typename SuperIteratorType, typename Subclass>
        inline IteratorType* getIterator(SuperIteratorType*& iterator, const Subclass* subclass) const {
            if (iterator == null) {
                iterator = new IteratorType(subclass);
            } else {
                static_cast<IteratorType*>(iterator)->reset();
            }
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

#endif // CXX_LANGUAGE
