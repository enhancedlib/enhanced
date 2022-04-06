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

#ifndef ENHANCED_BASIC_COLLECTION_LINKED0LIST_HPP
#define ENHANCED_BASIC_COLLECTION_LINKED0LIST_HPP

#include "EnhancedBasic/collection/LinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#ifdef CXX_LANGUAGE

namespace EnhancedBasic {
    namespace collection {
        template <typename Type>
        LinkedList<Type>::LinkedListIterator::LinkedListIterator(
            const LinkedList <Type> *linkedList) :
            LinkedListIteratorImpl(linkedList) {}

        template <typename Type>
        $RetNotIgnored()
        bool LinkedList<Type>::LinkedListIterator::hasNext() const {
            return LinkedListIteratorImpl::hasNext0();
        }

        template <typename Type>
        const core::Iterator<Type> *LinkedList<Type>::LinkedListIterator::next() const {
            LinkedListIteratorImpl::next0();
            return this;
        }

        template <typename Type>
        $RetNotIgnored()
        bool LinkedList<Type>::LinkedListIterator::each() const {
            return LinkedListIteratorImpl::each0();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &LinkedList<Type>::LinkedListIterator::get() const {
            return (Type &) LinkedListIteratorImpl::get0();
        }

        template <typename Type>
        void LinkedList<Type>::LinkedListIterator::reset() const {
            LinkedListIteratorImpl::reset0();
        }

        template <typename Type>
        $RetNotIgnored()
        Size LinkedList<Type>::LinkedListIterator::count() const {
            return LinkedListIteratorImpl::count0();
        }

        template <typename Type>
        $RetRequiresRelease()
        void *LinkedList<Type>::allocate(GenericReference element) {
            return new Type((Type &) element);
        }

        template <typename Type>
        void LinkedList<Type>::destroy(void *element) {
            delete (Type *) element;
        }

        template <typename Type>
        $RetNotIgnored()
        bool LinkedList<Type>::equals(GenericReference element, GenericReference value) {
            return ((Type &) element) == ((Type &) value);
        }

        template <typename Type>
        LinkedList<Type>::LinkedList() : LinkedListImpl(
            {LinkedList::allocate, LinkedList::destroy, LinkedList::equals}
        ) {}

        template <typename Type>
        $RetNotIgnored()
        Size LinkedList<Type>::getLength() const {
            return LinkedListImpl::getLength0();
        }

        template <typename Type>
        $RetNotIgnored()
        bool LinkedList<Type>::isEmpty() const {
            return LinkedListImpl::isEmpty0();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &LinkedList<Type>::getLast() const {
            return reinterpret_cast<Type &>(LinkedListImpl::getLast0());
        }

        template <typename Type>
        $RetNotIgnored()
        Type &LinkedList<Type>::getFirst() const {
            return (Type &) LinkedListImpl::getFirst0();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &LinkedList<Type>::get(Size index) const {
            return reinterpret_cast<Type &>(LinkedListImpl::get0(index));
        }

        template <typename Type>
        $RetNotIgnored()
        Type &LinkedList<Type>::operator[](Size index) const {
            return (Type &) LinkedListImpl::get0(index);
        }

        template <typename Type>
        $RetNotIgnored()
        core::Iterator<Type> *LinkedList<Type>::iterator() const {
            return List<Type>::template getIterator<LinkedListIterator>(LinkedListImpl::iterator, this);
        }

        template <typename Type>
        $RetNotIgnored()
        bool LinkedList<Type>::contain(const Type &value) const {
            return LinkedListImpl::contain0((GenericReference) value);
        }

        template <typename Type>
        $RetRequiresRelease()
        LinkedList<Type> *LinkedList<Type>::copy() const {
            return new LinkedList<Type>(*this);
        }

        template <typename Type>
        $RetNotIgnored()
        typename core::Iterable<Type>::ForeachIterator LinkedList<Type>::begin() const {
            return List<Type>::begin();
        }

        template <typename Type>
        $RetNotIgnored()
        UnusedType LinkedList<Type>::end() const {
            return List<Type>::end();
        }

        template <typename Type>
        void LinkedList<Type>::addLast(const Type &element) {
            LinkedListImpl::addLast0((GenericReference) element);
        }

        template <typename Type>
        Type LinkedList<Type>::removeLast() {
            Type value = this->getLast();
            LinkedListImpl::removeLast0();
            return value;
        }

        template <typename Type>
        void LinkedList<Type>::addFirst(const Type &element) {
            LinkedListImpl::addFirst0((GenericReference) element);
        }

        template <typename Type>
        Type LinkedList<Type>::removeFirst() {
            Type value = this->getFirst();
            LinkedListImpl::removeFirst0();
            return value;
        }

        template <typename Type>
        void LinkedList<Type>::add(const Type &element) {
            this->addLast(element);
        }

        template <typename Type>
        Type LinkedList<Type>::remove() {
            return this->removeLast();
        }

        template <typename Type>
        void LinkedList<Type>::push(const Type &element) {
            this->addFirst(element);
        }

        template <typename Type>
        Type LinkedList<Type>::popup() {
            return this->removeFirst();
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_LINKED0LIST_HPP
