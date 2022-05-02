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

#ifndef ENHANCED_BASIC_COLLECTION_REFER_REFER0LINKED0LIST_HPP
#define ENHANCED_BASIC_COLLECTION_REFER_REFER0LINKED0LIST_HPP

#include "EnhancedBasic/collection/refer/ReferLinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#ifdef CXX_LANGUAGE

namespace EnhancedBasic {
    namespace collection {
        namespace refer {
            template <typename Type>
            ReferLinkedList<Type>::ReferLinkedListIterator::ReferLinkedListIterator(
                const ReferLinkedList<Type>* referenceLinkedList) :
                ReferLinkedListIteratorImpl(referenceLinkedList) {}

            template <typename Type>
            $RetNotIgnored()
                bool ReferLinkedList<Type>::ReferLinkedListIterator::hasNext() const {
                return ReferLinkedListIteratorImpl::hasNext0();
            }

            template <typename Type>
            const core::Iterator<Type>* ReferLinkedList<Type>::ReferLinkedListIterator::next() const {
                ReferLinkedListIteratorImpl::next0();
                return this;
            }

            template <typename Type>
            $RetNotIgnored()
                bool ReferLinkedList<Type>::ReferLinkedListIterator::each() const {
                return ReferLinkedListIteratorImpl::each0();
            }

            template <typename Type>
            $RetNotIgnored()
                Type& ReferLinkedList<Type>::ReferLinkedListIterator::get() const {
                return (Type&) ReferLinkedListIteratorImpl::get0();
            }

            template <typename Type>
            void ReferLinkedList<Type>::ReferLinkedListIterator::reset() const {
                ReferLinkedListIteratorImpl::reset0();
            }

            template <typename Type>
            $RetNotIgnored()
                Size ReferLinkedList<Type>::ReferLinkedListIterator::count() const {
                return ReferLinkedListIteratorImpl::count0();
            }

            template <typename Type>
            $RetNotIgnored()
                bool ReferLinkedList<Type>::equals(GenericReference element, GenericReference value) {
                return ((Type&) (element)) == ((Type&) value);
            }

            template <typename Type>
            ReferLinkedList<Type>::ReferLinkedList() :
                ReferLinkedListImpl({ ReferLinkedList::equals }) {}

            template <typename Type>
            ReferLinkedList<Type>::ReferLinkedList(const ReferLinkedList<Type>& other) :
                ReferLinkedListImpl(other) {}

            template <typename Type>
            $RetNotIgnored()
                Size ReferLinkedList<Type>::getLength() const {
                return ReferLinkedListImpl::getLength0();
            }

            template <typename Type>
            $RetNotIgnored()
                bool ReferLinkedList<Type>::isEmpty() const {
                return ReferLinkedListImpl::isEmpty0();
            }

            template <typename Type>
            $RetNotIgnored()
                Type& ReferLinkedList<Type>::getLast() const {
                return (Type&) ReferLinkedListImpl::getLast0();
            }

            template <typename Type>
            $RetNotIgnored()
                Type& ReferLinkedList<Type>::getFirst() const {
                return reinterpret_cast<Type&>(ReferLinkedListImpl::getFirst0());
            }

            template <typename Type>
            $RetNotIgnored()
                Type& ReferLinkedList<Type>::get(Size index) const {
                return (Type&) ReferLinkedListImpl::get0(index);
            }

            template <typename Type>
            $RetNotIgnored()
                Type& ReferLinkedList<Type>::operator[](Size index) const {
                return reinterpret_cast<Type&>(ReferLinkedListImpl::get0(index));
            }

            template <typename Type>
            core::Iterator<Type>* ReferLinkedList<Type>::iterator() const {
                return List<Type>::template getIterator<ReferLinkedListIterator>
                    (ReferLinkedListImpl::iterator, this);
            }

            template <typename Type>
            $RetNotIgnored()
                bool ReferLinkedList<Type>::contain(const Type& value) const {
                return ReferLinkedListImpl::contain0((GenericReference) value);
            }

            template <typename Type>
            ReferLinkedList<Type>* ReferLinkedList<Type>::copy() const {
                return new ReferLinkedList<Type>(*this);
            }

            template <typename Type>
            $RetNotIgnored()
                typename core::Iterable<Type>::ForeachIterator ReferLinkedList<Type>::begin() const {
                return List<Type>::begin();
            }

            template <typename Type>
            $RetNotIgnored()
                UnusedType ReferLinkedList<Type>::end() const {
                return List<Type>::end();
            }

            template <typename Type>
            void ReferLinkedList<Type>::addLast(const Type& element) {
                ReferLinkedListImpl::addLast0((GenericReference) element);
            }

            template <typename Type>
            Type ReferLinkedList<Type>::removeLast() {
                Type value = this->getLast();
                ReferLinkedListImpl::removeLast0();
                return value;
            }

            template <typename Type>
            void ReferLinkedList<Type>::addFirst(const Type& element) {
                ReferLinkedListImpl::addFirst0((GenericReference) element);
            }

            template <typename Type>
            Type ReferLinkedList<Type>::removeFirst() {
                Type value = this->getFirst();
                ReferLinkedListImpl::removeFirst0();
                return value;
            }

            template <typename Type>
            void ReferLinkedList<Type>::add(const Type& element) {
                this->addLast(element);
            }

            template <typename Type>
            Type ReferLinkedList<Type>::remove() {
                return this->removeLast();
            }

            template <typename Type>
            void ReferLinkedList<Type>::push(const Type& element) {
                this->addFirst(element);
            }

            template <typename Type>
            Type ReferLinkedList<Type>::popup() {
                return this->removeFirst();
            }
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_REFER_REFER0LINKED0LIST_HPP
