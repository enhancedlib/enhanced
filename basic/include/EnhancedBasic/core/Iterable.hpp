/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The authors or copyright holders be not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by This software,
 * the authors or copyright holders may provide possible solutions,
 * but it does not mean that the authors or copyright holders
 * will definitely solve the problem.
 * In no event shall the author or copyright
 * owner be liable for any claims, damages or other liabilities.
 *
 * You should see the Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#ifndef ENHANCED_BASIC_CORE_ITERABLE_HPP
#define ENHANCED_BASIC_CORE_ITERABLE_HPP

#include "EnhancedBasic/core/Iterable.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

namespace EnhancedBasic {
    namespace core {
        template <typename Type>
        Iterable<Type>::ForeachIterator::ForeachIterator(Iterator<Type> *iterator) : iterator(iterator) {}

        template <typename Type>
        bool Iterable<Type>::ForeachIterator::operator!=($Unused UnusedType unused) {
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
        UnusedType Iterable<Type>::end() const {
            return UNUSED_VALUE;
        }
    }
}

#endif // !ENHANCED_BASIC_CORE_ITERABLE_HPP
