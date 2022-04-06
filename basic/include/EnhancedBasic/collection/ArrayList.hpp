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
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#ifndef ENHANCED_BASIC_COLLECTION_ARRAY0LIST_HPP
#define ENHANCED_BASIC_COLLECTION_ARRAY0LIST_HPP

#include "EnhancedBasic/collection/ArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterable.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#ifdef CXX_LANGUAGE

namespace EnhancedBasic {
    namespace collection {
        template <typename Type>
        ArrayList<Type>::ArrayListIterator::ArrayListIterator(const ArrayList<Type> *arrayList) :
            ArrayListIteratorImpl(arrayList) {}

        template <typename Type>
        $RetNotIgnored()
        bool ArrayList<Type>::ArrayListIterator::hasNext() const {
            return ArrayListIteratorImpl::hasNext0();
        }

        template <typename Type>
        const core::Iterator <Type> *ArrayList<Type>::ArrayListIterator::next() const {
            ArrayListIteratorImpl::next0();
            return this;
        }

        template <typename Type>
        $RetNotIgnored()
        bool ArrayList<Type>::ArrayListIterator::each() const {
            return ArrayListIteratorImpl::each0();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &ArrayList<Type>::ArrayListIterator::get() const {
            return (Type &) ArrayListIteratorImpl::get0();
        }

        template <typename Type>
        void ArrayList<Type>::ArrayListIterator::reset() const {
            ArrayListIteratorImpl::reset0();
        }

        template <typename Type>
        $RetNotIgnored()
        Size ArrayList<Type>::ArrayListIterator::count() const {
            return ArrayListIteratorImpl::count0();
        }

        template <typename Type>
        $RetRequiresRelease()
        void *ArrayList<Type>::allocate(GenericReference element) {
            return new Type((Type &) element);
        }

        template <typename Type>
        void ArrayList<Type>::destroy(void *element) {
            delete (Type *) element;
        }

        template <typename Type>
        $RetNotIgnored()
        bool ArrayList<Type>::equals(GenericReference element, GenericReference value) {
            return ((Type &) element) == ((Type &) value);
        }

        template <typename Type>
        ArrayList<Type>::ArrayList() : ArrayListImpl(
            UINT8_MAX, {ArrayList::allocate, ArrayList::destroy, ArrayList::equals}
        ) {}

        template <typename Type>
        ArrayList<Type>::ArrayList(Size maxCount) : ArrayListImpl(
            maxCount, {ArrayList::allocate, ArrayList::destroy, ArrayList::equals}
        ) {}

        template <typename Type>
        ArrayList<Type>::ArrayList(const ArrayList<Type> &other) : ArrayListImpl(other) {}

        template <typename Type>
        $RetNotIgnored()
        Size ArrayList<Type>::getLength() const {
            return ArrayListImpl::getLength0();
        }

        template <typename Type>
        bool ArrayList<Type>::isEmpty() const {
            return ArrayListImpl::isEmpty0();
        }

        template <typename Type>
        Type &ArrayList<Type>::get(Size index) const {
            return (Type &) ArrayListImpl::get0(index);
        }

        template <typename Type>
        Type &ArrayList<Type>::operator[](Size index) const {
            return (Type &) ArrayListImpl::get0(index);
        }

        template <typename Type>
        core::Iterator <Type> *ArrayList<Type>::iterator() const {
            return core::Iterable<Type>::template getIterator<ArrayListIterator>(ArrayListImpl::iterator, this);
        }

        template <typename Type>
        bool ArrayList<Type>::contain(const Type &value) const {
            return ArrayListImpl::contain0((GenericReference) value);
        }

        template <typename Type>
        ArrayList<Type> *ArrayList<Type>::copy() const {
            return new ArrayList<Type>(*this);
        }

        template <typename Type>
        void ArrayList<Type>::add(const Type &element) {
            ArrayListImpl::add0((GenericReference) element);
        }

        template <typename Type>
        Type ArrayList<Type>::remove() {
            Type value = this->get(this->getLength() - 1);
            ArrayListImpl::remove0();
            return value;
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_ARRAY0LIST_HPP
