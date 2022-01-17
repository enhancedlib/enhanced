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

#ifndef ENHANCED_BASIC_CORE_ITERABLE_TCC
#define ENHANCED_BASIC_CORE_ITERABLE_TCC

#include "EnhancedBasic/core/Iterable.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

namespace EnhancedBasic {
    namespace core {
        template <typename Type>
        Iterable<Type>::ForeachIterator::ForeachIterator(Iterator<Type> *iterator) : iterator(iterator) {}

        template <typename Type>
        bool Iterable<Type>::ForeachIterator::operator!=($Unused InvalidType unused) {
            return this->iterator->hasNext();
        }

        template <typename Type>
        const Iterator<Type> *Iterable<Type>::ForeachIterator::operator++() {
            return this->iterator->next();
        }

        template <typename Type>
        Type &Iterable<Type>::ForeachIterator::operator*() {
            return this->iterator->get();
        }

        template <typename Type>
        template <typename IteratorType, typename SuperType, typename Subclass>
        IteratorType *Iterable<Type>::getIterator(SuperType *&iterator, const Subclass *self) const {
            if (iterator == null) {
                iterator = new IteratorType(self);
            } else {
                static_cast<IteratorType *>(iterator)->reset();
            }
            return static_cast<IteratorType *>(iterator);
        }

        template <typename Type>
        typename Iterable<Type>::ForeachIterator Iterable<Type>::begin() const {
            return Iterable<Type>::ForeachIterator(this->iterator());
        }

        template <typename Type>
        constexpr InvalidType Iterable<Type>::end() const {
            return INVALID_VALUE;
        }
    }
}

#endif // !ENHANCED_BASIC_CORE_ITERABLE_TCC
