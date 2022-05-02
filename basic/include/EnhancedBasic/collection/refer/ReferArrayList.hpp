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

#ifndef ENHANCED_BASIC_COLLECTION_REFER_REFER0ARRAY0LIST_HPP
#define ENHANCED_BASIC_COLLECTION_REFER_REFER0ARRAY0LIST_HPP

#include "EnhancedBasic/collection/refer/ReferArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterable.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace collection {
        namespace refer {
            template <typename Type>
            ReferArrayList<Type>::ReferArrayListIterator::ReferArrayListIterator(
                const ReferArrayList<Type>* referArrayList) :
                ReferArrayListIteratorImpl(referArrayList) {}

            template <typename Type>
            $RetNotIgnored()
                bool ReferArrayList<Type>::ReferArrayListIterator::hasNext() const {
                return ReferArrayListIteratorImpl::hasNext0();
            }

            template <typename Type>
            const core::Iterator<Type>* ReferArrayList<Type>::ReferArrayListIterator::next() const {
                ReferArrayListIteratorImpl::next0();
                return this;
            }

            template <typename Type>
            $RetNotIgnored()
                bool ReferArrayList<Type>::ReferArrayListIterator::each() const {
                return ReferArrayListIteratorImpl::each0();
            }

            template <typename Type>
            $RetNotIgnored()
                Type& ReferArrayList<Type>::ReferArrayListIterator::get() const {
                return (Type&) ReferArrayListIteratorImpl::get0();
            }

            template <typename Type>
            void ReferArrayList<Type>::ReferArrayListIterator::reset() const {
                ReferArrayListIteratorImpl::reset0();
            }

            template <typename Type>
            $RetNotIgnored()
                Size ReferArrayList<Type>::ReferArrayListIterator::count() const {
                return ReferArrayListIteratorImpl::count0();
            }

            template <typename Type>
            $RetNotIgnored()
                bool ReferArrayList<Type>::equals(GenericReference element, GenericReference value) {
                return ((Type&) element) == ((Type&) (value));
            }

            template <typename Type>
            ReferArrayList<Type>::ReferArrayList() :
                ReferArrayListImpl(UINT8_MAX, { ReferArrayList::equals }) {}

            template <typename Type>
            ReferArrayList<Type>::ReferArrayList(Size maxCount) :
                ReferArrayListImpl(maxCount, { ReferArrayList::equals }) {}

            template <typename Type>
            ReferArrayList<Type>::ReferArrayList(const ReferArrayList<Type>& other) :
                ReferArrayListImpl(other) {}

            template <typename Type>
            $RetNotIgnored()
                Size ReferArrayList<Type>::getLength() const {
                return ReferArrayListImpl::getLength0();
            }

            template <typename Type>
            $RetNotIgnored()
                bool ReferArrayList<Type>::isEmpty() const {
                return ReferArrayListImpl::isEmpty0();
            }

            template <typename Type>
            $RetNotIgnored()
                Type& ReferArrayList<Type>::get(Size index) const {
                return (Type&) ReferArrayListImpl::get0(index);
            }

            template <typename Type>
            $RetNotIgnored()
                Type& ReferArrayList<Type>::operator[](Size index) const {
                return reinterpret_cast<Type&>(ReferArrayListImpl::get0(index));
            }

            template <typename Type>
            core::Iterator <Type>* ReferArrayList<Type>::iterator() const {
                return core::Iterable<Type>::
                    template getIterator<ReferArrayListIterator>(ReferArrayListImpl::iterator, this);
            }

            template <typename Type>
            $RetNotIgnored()
                bool ReferArrayList<Type>::contain(const Type& value) const {
                return ReferArrayListImpl::contain0((GenericReference) value);
            }

            template <typename Type>
            $RetRequiresRelease()
                ReferArrayList <Type>* ReferArrayList<Type>::copy() const {
                return new ReferArrayList<Type>(*this);
            }

            template <typename Type>
            void ReferArrayList<Type>::add(const Type& element) {
                ReferArrayListImpl::add0((GenericReference) element);
            }

            template <typename Type>
            Type ReferArrayList<Type>::remove() {
                Type value = this->get(this->getLength() - 1);
                ReferArrayListImpl::remove0();
                return value;
            }
        } // namespace refer
    } // namespace collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_REFER_REFER0ARRAY0LIST_HPP
