/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
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

#ifndef ENHANCED_BASIC_ITERABLE_H
#define ENHANCED_BASIC_ITERABLE_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#include "Iterator.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace Core {
        template <typename Type>
        interface Iterable {
        protected:
            class ForeachIterator final {
            private:
                Core::Iterator<Type> *iterator;

            public:
                ForeachIterator(Core::Iterator<Type> *iterator) : iterator(iterator) {}

                bool operator!=($Unused void *unused) {
                    return this->iterator->hasNext();
                }

                const Core::Iterator<Type> *operator++() {
                    return this->iterator->next();
                }

                Type &operator*() {
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
            virtual Core::Iterator<Type> *iterator() const = 0;
        };
    } // namespace Core
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_ITERABLE_H
