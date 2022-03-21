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

#ifndef ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0LINKED0LIST_HPP
#define ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0LINKED0LIST_HPP

#include "EnhancedBasic/collection/referenced/ReferencedLinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#ifdef CXX_LANGUAGE

namespace EnhancedBasic {
    namespace collection{
        namespace referenced {
            template <typename Type>
            ReferencedLinkedList<Type>::ReferencedLinkedListIterator::ReferencedLinkedListIterator(
                const ReferencedLinkedList<Type> *referenceLinkedList) :
                ReferencedLinkedListIteratorImpl(referenceLinkedList) {}

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedLinkedList<Type>::ReferencedLinkedListIterator::hasNext() const {
                return ReferencedLinkedListIteratorImpl::hasNext0();
            }

            template <typename Type>
            const core::Iterator<Type> *ReferencedLinkedList<Type>::ReferencedLinkedListIterator::next() const {
                ReferencedLinkedListIteratorImpl::next0();
                return this;
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedLinkedList<Type>::ReferencedLinkedListIterator::each() const {
                return ReferencedLinkedListIteratorImpl::each0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedLinkedList<Type>::ReferencedLinkedListIterator::get() const {
                return (Type &) ReferencedLinkedListIteratorImpl::get0();
            }

            template <typename Type>
            void ReferencedLinkedList<Type>::ReferencedLinkedListIterator::reset() const {
                ReferencedLinkedListIteratorImpl::reset0();
            }

            template <typename Type>
            $RetNotIgnored()
            Size ReferencedLinkedList<Type>::ReferencedLinkedListIterator::count() const {
                return ReferencedLinkedListIteratorImpl::count0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedLinkedList<Type>::equals(GenericReference element, GenericReference value) {
                return ((Type &) (element)) == ((Type &) value);
            }

            template <typename Type>
            ReferencedLinkedList<Type>::ReferencedLinkedList() :
                ReferencedLinkedListImpl({ReferencedLinkedList::equals}) {}

            template <typename Type>
            ReferencedLinkedList<Type>::ReferencedLinkedList(const ReferencedLinkedList<Type> &other) :
                ReferencedLinkedListImpl(other) {}

            template <typename Type>
            $RetNotIgnored()
            Size ReferencedLinkedList<Type>::getLength() const {
                return ReferencedLinkedListImpl::getLength0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedLinkedList<Type>::isEmpty() const {
                return ReferencedLinkedListImpl::isEmpty0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedLinkedList<Type>::getLast() const {
                return (Type &) ReferencedLinkedListImpl::getLast0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedLinkedList<Type>::getFirst() const {
                return reinterpret_cast<Type &>(ReferencedLinkedListImpl::getFirst0());
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedLinkedList<Type>::get(Size index) const {
                return (Type &) ReferencedLinkedListImpl::get0(index);
            }

            template <typename Type>
            $RetNotIgnored()
            Type &ReferencedLinkedList<Type>::operator[](Size index) const {
                return reinterpret_cast<Type &>(ReferencedLinkedListImpl::get0(index));
            }

            template <typename Type>
            core::Iterator<Type> *ReferencedLinkedList<Type>::iterator() const {
                return List<Type>::template getIterator<ReferencedLinkedListIterator>
                    (ReferencedLinkedListImpl::iterator, this);
            }

            template <typename Type>
            $RetNotIgnored()
            bool ReferencedLinkedList<Type>::contain(const Type &value) const {
                return ReferencedLinkedListImpl::contain0((GenericReference) value);
            }

            template <typename Type>
            ReferencedLinkedList<Type> *ReferencedLinkedList<Type>::copy() const {
                return new ReferencedLinkedList<Type>(*this);
            }

            template <typename Type>
            $RetNotIgnored()
            typename core::Iterable<Type>::ForeachIterator ReferencedLinkedList<Type>::begin() const {
                return List<Type>::begin();
            }

            template <typename Type>
            $RetNotIgnored()
            UnusedType ReferencedLinkedList<Type>::end() const {
                return List<Type>::end();
            }

            template <typename Type>
            void ReferencedLinkedList<Type>::addLast(const Type &element) {
                ReferencedLinkedListImpl::addLast0((GenericReference) element);
            }

            template <typename Type>
            Type ReferencedLinkedList<Type>::removeLast() {
                Type value = this->getLast();
                ReferencedLinkedListImpl::removeLast0();
                return value;
            }

            template <typename Type>
            void ReferencedLinkedList<Type>::addFirst(const Type &element) {
                ReferencedLinkedListImpl::addFirst0((GenericReference) element);
            }

            template <typename Type>
            Type ReferencedLinkedList<Type>::removeFirst() {
                Type value = this->getFirst();
                ReferencedLinkedListImpl::removeFirst0();
                return value;
            }

            template <typename Type>
            void ReferencedLinkedList<Type>::add(const Type &element) {
                this->addLast(element);
            }

            template <typename Type>
            Type ReferencedLinkedList<Type>::remove() {
                return this->removeLast();
            }

            template <typename Type>
            void ReferencedLinkedList<Type>::push(const Type &element) {
                this->addFirst(element);
            }

            template <typename Type>
            Type ReferencedLinkedList<Type>::popup() {
                return this->removeFirst();
            }
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0LINKED0LIST_HPP
