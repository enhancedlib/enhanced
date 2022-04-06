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

#ifndef ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0ARRAY0LIST_HPP
#define ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0ARRAY0LIST_HPP

#include "EnhancedBasic/collection/referenced/ReferencedArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterable.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace collection {
        namespace referenced {
            template <typename Type>
            ReferencedArrayList<Type>::ReferencedArrayListIterator::ReferencedArrayListIterator(
                const ReferencedArrayList<Type> *referencedArrayList) :
                ReferencedArrayListIteratorImpl(referencedArrayList) {}

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedArrayList<Type>::ReferencedArrayListIterator::hasNext() const {
                return ReferencedArrayListIteratorImpl::hasNext0();
            }

            template <typename Type>
            const core::Iterator<Type> *ReferencedArrayList<Type>::ReferencedArrayListIterator::next() const {
                ReferencedArrayListIteratorImpl::next0();
                return this;
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedArrayList<Type>::ReferencedArrayListIterator::each() const {
                return ReferencedArrayListIteratorImpl::each0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedArrayList<Type>::ReferencedArrayListIterator::get() const {
                return (Type &) ReferencedArrayListIteratorImpl::get0();
            }

            template <typename Type>
            void ReferencedArrayList<Type>::ReferencedArrayListIterator::reset() const {
                ReferencedArrayListIteratorImpl::reset0();
            }

            template <typename Type>
            $RetNotIgnored()
            Size ReferencedArrayList<Type>::ReferencedArrayListIterator::count() const {
                return ReferencedArrayListIteratorImpl::count0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedArrayList<Type>::equals(GenericReference element, GenericReference value) {
                return ((Type &) element) == ((Type &) (value));
            }

            template <typename Type>
            ReferencedArrayList<Type>::ReferencedArrayList() :
                ReferencedArrayListImpl(UINT8_MAX, {ReferencedArrayList::equals}) {}

            template <typename Type>
            ReferencedArrayList<Type>::ReferencedArrayList(Size maxCount) :
                ReferencedArrayListImpl(maxCount, {ReferencedArrayList::equals}) {}

            template <typename Type>
            ReferencedArrayList<Type>::ReferencedArrayList(const ReferencedArrayList<Type> &other) :
                ReferencedArrayListImpl(other) {}

            template <typename Type>
            $RetNotIgnored()
            Size ReferencedArrayList<Type>::getLength() const {
                return ReferencedArrayListImpl::getLength0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedArrayList<Type>::isEmpty() const {
                return ReferencedArrayListImpl::isEmpty0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedArrayList<Type>::get(Size index) const {
                return (Type &) ReferencedArrayListImpl::get0(index);
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedArrayList<Type>::operator[](Size index) const {
                return reinterpret_cast<Type &>(ReferencedArrayListImpl::get0(index));
            }

            template <typename Type>
            core::Iterator <Type> *ReferencedArrayList<Type>::iterator() const {
                return core::Iterable<Type>::
                    template getIterator<ReferencedArrayListIterator>(ReferencedArrayListImpl::iterator, this);
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedArrayList<Type>::contain(const Type &value) const {
                return ReferencedArrayListImpl::contain0((GenericReference) value);
            }

            template <typename Type>
            $RetRequiresRelease()
            ReferencedArrayList <Type> *ReferencedArrayList<Type>::copy() const {
                return new ReferencedArrayList<Type>(*this);
            }

            template <typename Type>
            void ReferencedArrayList<Type>::add(const Type &element) {
                ReferencedArrayListImpl::add0((GenericReference) element);
            }

            template <typename Type>
            Type ReferencedArrayList<Type>::remove() {
                Type value = this->get(this->getLength() - 1);
                ReferencedArrayListImpl::remove0();
                return value;
            }
        } // namespace referenced
    } // namespace collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0ARRAY0LIST_HPP
