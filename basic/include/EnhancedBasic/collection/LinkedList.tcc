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

#ifndef ENHANCED_BASIC_COLLECTION_LINKED0LIST_TCC
#define ENHANCED_BASIC_COLLECTION_LINKED0LIST_TCC

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
            LinkedListIterator0(linkedList) {}

        template <typename Type>
        $RetNotIgnored()
        bool LinkedList<Type>::LinkedListIterator::hasNext() const {
            return LinkedListIterator0::hasNext0();
        }

        template <typename Type>
        const core::Iterator<Type> *LinkedList<Type>::LinkedListIterator::next() const {
            LinkedListIterator0::next0();
            return this;
        }

        template <typename Type>
        $RetNotIgnored()
        bool LinkedList<Type>::LinkedListIterator::each() const {
            return LinkedListIterator0::each0();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &LinkedList<Type>::LinkedListIterator::get() const {
            return reinterpret_cast<Type &>(LinkedListIterator0::get0());
        }

        template <typename Type>
        void LinkedList<Type>::LinkedListIterator::reset() const {
            LinkedListIterator0::reset0();
        }

        template <typename Type>
        $RetNotIgnored()
        Size LinkedList<Type>::LinkedListIterator::count() const {
            return LinkedListIterator0::count0();
        }

        template <typename Type>
        $RetRequiresRelease()
        GenericPointer LinkedList<Type>::allocate(Generic &element) {
            return new Type(reinterpret_cast<Type &>(element));
        }

        template <typename Type>
        void LinkedList<Type>::destroy(GenericPointer element) {
            delete reinterpret_cast<Type *>(element);
        }

        template <typename Type>
        $RetNotIgnored()
        bool LinkedList<Type>::equals(Generic &element, Generic &value) {
            return reinterpret_cast<Type &>(element) == reinterpret_cast<Type &>(value);
        }

        template <typename Type>
        LinkedList<Type>::LinkedList() : LinkedList0({allocate, destroy, equals}) {}

        template <typename Type>
        $RetNotIgnored()
        Size LinkedList<Type>::getLength() const {
            return LinkedList0::getLength0();
        }

        template <typename Type>
        $RetNotIgnored()
        bool LinkedList<Type>::isEmpty() const {
            return LinkedList0::isEmpty0();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &LinkedList<Type>::getLast() const {
            return reinterpret_cast<Type &>(LinkedList0::getLast0());
        }

        template <typename Type>
        $RetNotIgnored()
        Type &LinkedList<Type>::getFirst() const {
            return reinterpret_cast<Type &>(LinkedList0::getFirst0());
        }

        template <typename Type>
        $RetNotIgnored()
        Type &LinkedList<Type>::get(Size index) const {
            return reinterpret_cast<Type &>(LinkedList0::get0(index));
        }

        template <typename Type>
        $RetNotIgnored()
        Type &LinkedList<Type>::operator[](Size index) const {
            return reinterpret_cast<Type &>(LinkedList0::get0(index));
        }

        template <typename Type>
        $RetNotIgnored()
        core::Iterator<Type> *LinkedList<Type>::iterator() const {
            return List<Type>::template getIterator<LinkedListIterator>(LinkedList0::iterator, this);
        }

        template <typename Type>
        $RetNotIgnored()
        bool LinkedList<Type>::contain(const Type &value) const {
            return LinkedList0::contain0((GenericReference) value);
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
        constexpr InvalidType LinkedList<Type>::end() const {
            return List<Type>::end();
        }

        template <typename Type>
        void LinkedList<Type>::addLast(const Type &element) {
            LinkedList0::addLast0((GenericReference) element);
        }

        template <typename Type>
        Type LinkedList<Type>::removeLast() {
            Type value = this->getLast();
            LinkedList0::removeFirst0();
            return value;
        }

        template <typename Type>
        void LinkedList<Type>::addFirst(const Type &element) {
            LinkedList0::addFirst0((GenericReference) element);
        }

        template <typename Type>
        Type LinkedList<Type>::removeFirst() {
            Type value = this->getFirst();
            LinkedList0::removeFirst0();
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

#endif // !ENHANCED_BASIC_COLLECTION_LINKED0LIST_TCC
