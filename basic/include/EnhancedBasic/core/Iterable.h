/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
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

#include "EnhancedBasic/core/Iterator.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace core {
        template <typename Type>
        struct Iterable {
        protected:
            class ForeachIterator final {
            private:
                core::Iterator<Type> *iterator;

            public:
                ForeachIterator(core::Iterator<Type> *iterator) : iterator(iterator) {}

                bool operator!=($Unused InvalidType unused) {
                    return this->iterator->hasNext();
                }

                const core::Iterator<Type> *operator++() {
                    return this->iterator->next();
                }

                Type &operator*() {
                    return this->iterator->get();
                }
            };

            template <typename IteratorType, typename SuperType, typename Subclass>
            inline IteratorType *getIterator(SuperType *&iterator, const Subclass *self) const {
                if (iterator == null) {
                    iterator = new IteratorType(self);
                } else {
                    static_cast<IteratorType *>(iterator)->reset();
                }
                return static_cast<IteratorType *>(iterator);
            }

        public:
            $RetNotIgnored()
            virtual inline Iterable<Type>::ForeachIterator begin() const {
                return Iterable<Type>::ForeachIterator(this->iterator());
            }

            $RetNotIgnored()
            virtual inline constexpr InvalidType end() const {
                return INVALID_VALUE;
            }

            $RetNotIgnored()
            virtual core::Iterator<Type> *iterator() const = 0;
        };
    } // namespace core
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_ITERABLE_H
