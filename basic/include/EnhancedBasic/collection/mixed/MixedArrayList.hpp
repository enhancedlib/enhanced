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

#ifndef ENHANCED_BASIC_COLLECTION_MIXED_MIXED0ARRAY0LIST_HPP
#define ENHANCED_BASIC_COLLECTION_MIXED_MIXED0ARRAY0LIST_HPP

#include "EnhancedBasic/collection/mixed/MixedArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterable.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace collection {
        namespace mixed {
            template <typename Type>
            MixedArrayList<Type>::MixedArrayListIterator::
            MixedArrayListIterator(const MixedArrayList<Type> *arrayList) : MixedArrayListIteratorImpl(arrayList) {}

            template <typename Type>
            $RetNotIgnored()
            bool MixedArrayList<Type>::MixedArrayListIterator::hasNext() const {
                return MixedArrayListIteratorImpl::hasNext0();
            }

            template <typename Type>
            const core::Iterator<Type> *MixedArrayList<Type>::MixedArrayListIterator::next() const {
                MixedArrayListIteratorImpl::next0();
                return this;
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedArrayList<Type>::MixedArrayListIterator::each() const {
                return MixedArrayListIteratorImpl::each0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedArrayList<Type>::MixedArrayListIterator::get() const {
                return (Type &) MixedArrayListIteratorImpl::get0();
            }

            template <typename Type>
            void MixedArrayList<Type>::MixedArrayListIterator::reset() const {
                MixedArrayListIteratorImpl::reset0();
            }

            template <typename Type>
            $RetNotIgnored()
            Size MixedArrayList<Type>::MixedArrayListIterator::count() const {
                return MixedArrayListIteratorImpl::count0();
            }

            template <typename Type>
            $RetRequiresRelease()
            void *MixedArrayList<Type>::allocate(GenericReference element) {
                return new Type(reinterpret_cast<Type &>(element));
            }

            template <typename Type>
            void MixedArrayList<Type>::destroy(void *element) {
                delete (Type *) element;
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedArrayList<Type>::equals(GenericReference element, GenericReference value) {
                return ((Type &) element) == ((Type &) (value));
            }

            template <typename Type>
            MixedArrayList<Type>::MixedArrayList() : MixedArrayListImpl(
                UINT8_MAX, {MixedArrayList::allocate, MixedArrayList::destroy, MixedArrayList::equals}
            ) {}

            template <typename Type>
            MixedArrayList<Type>::MixedArrayList(Size maxCount) : MixedArrayListImpl(
                maxCount, {MixedArrayList::allocate, MixedArrayList::destroy, MixedArrayList::equals}
            ) {}

            template <typename Type>
            MixedArrayList<Type>::MixedArrayList(const MixedArrayList<Type> &other) : MixedArrayListImpl(other) {}

            template <typename Type>
            $RetNotIgnored()
            Size MixedArrayList<Type>::getLength() const {
                return MixedArrayListImpl::getLength0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedArrayList<Type>::isEmpty() const {
                return MixedArrayListImpl::isEmpty0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedArrayList<Type>::get(Size index) const {
                return ((Type &) MixedArrayListImpl::get0(index));
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedArrayList<Type>::operator[](Size index) const {
                return reinterpret_cast<Type &>(MixedArrayListImpl::get0(index));
            }

            template <typename Type>
            core::Iterator<Type> *MixedArrayList<Type>::iterator() const {
                return core::Iterable<Type>::
                    template getIterator<MixedArrayListIterator>(MixedArrayListImpl::iterator,this);
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedArrayList<Type>::contain(const Type &value) const {
                return MixedArrayListImpl::contain0((GenericReference) value);
            }

            template <typename Type>
            $RetRequiresRelease()
            MixedArrayList<Type> *MixedArrayList<Type>::copy() const {
                return new MixedArrayList<Type>(*this);
            }

            template <typename Type>
            void MixedArrayList<Type>::add(const Type &element) {
                MixedArrayListImpl::add0((GenericReference) element);
            }

            template <typename Type>
            void MixedArrayList<Type>::addReferenced(const Type &element) {
                MixedArrayListImpl::addReferenced0((GenericReference) element);
            }

            template <typename Type>
            Type MixedArrayList<Type>::remove() {
                Type value = this->get(this->getLength() - 1);
                MixedArrayListImpl::remove0();
                return value;
            }
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_MIXED_MIXED0ARRAY0LIST_HPP
