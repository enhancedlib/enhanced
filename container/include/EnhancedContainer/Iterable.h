/*
 * Copyright (C) 2021 Liu Baihao.
 * This product is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#ifndef ENHANCED_CONTAINER_ITERABLE_H
#define ENHANCED_CONTAINER_ITERABLE_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#include "EnhancedContainer/Iterator.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedContainer {
    template <typename Type>
    interface Iterable {
    protected:
        class ForeachIterator final {
        private:
            Iterator<Type> *iterator;

        public:
            ForeachIterator(Iterator<Type> *iterator) : iterator(iterator) {}

            ~ForeachIterator() {
            }

            bool operator!=($Unused void *unused) {
                return this->iterator->hasNext();
            }

            const Iterator<Type> *operator++() {
                return this->iterator->next();
            }

            Type operator*() {
                return this->iterator->get();
            }
        };

    public:
        $RetNotIgnored()
        virtual Iterable<Type>::ForeachIterator begin() const {
            return Iterable<Type>::ForeachIterator(this->iterator());
        }

        $RetNotIgnored()
        virtual void *end() const {
            return null;
        }

        $RetNotIgnored()
        virtual Iterator<Type> *iterator() const = 0;
    };
} // namespace EnhancedContainer

#endif // CXX_LANGUAGE

#endif // !ENHANCED_CONTAINER_ITERABLE_H
