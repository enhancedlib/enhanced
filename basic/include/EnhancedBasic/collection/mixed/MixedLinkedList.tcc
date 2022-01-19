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

#ifndef ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_TCC
#define ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_TCC

#include "EnhancedBasic/collection/mixed/MixedLinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterator.h"

#ifdef CXX_LANGUAGE

namespace EnhancedBasic {
    namespace collection {
        namespace mixed {
            template <typename Type>
            MixedLinkedList<Type>::MixedLinkedListIterator::
            MixedLinkedListIterator(const EnhancedBasic::collection::mixed::MixedLinkedList<Type> *mixedLinkedList) :
                MixedLinkedListIterator0(mixedLinkedList) {}

            template <typename Type>
            $RetNotIgnored()
            bool MixedLinkedList<Type>::MixedLinkedListIterator::hasNext() const {
                return MixedLinkedListIterator0::hasNext0();
            }

            template <typename Type>
            const core::Iterator<Type> *MixedLinkedList<Type>::MixedLinkedListIterator::next() const {
                MixedLinkedListIterator0::next0();
                return this;
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedLinkedList<Type>::MixedLinkedListIterator::each() const {
                return MixedLinkedListIterator0::each0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedLinkedList<Type>::MixedLinkedListIterator::get() const {
                return (Type &) MixedLinkedListIterator0::get0();
            }

            template <typename Type>
            void MixedLinkedList<Type>::MixedLinkedListIterator::reset() const {
                MixedLinkedListIterator0::reset0();
            }

            template <typename Type>
            $RetNotIgnored()
            Size MixedLinkedList<Type>::MixedLinkedListIterator::count() const {
                return MixedLinkedListIterator0::count0();
            }

            template <typename Type>
            $RetRequiresRelease()
            void *MixedLinkedList<Type>::allocate(GenericReference element) {
                return new Type(reinterpret_cast<Type &>(element));
            }

            template <typename Type>
            void MixedLinkedList<Type>::destroy(void *element) {
                delete (Type &) element;
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedLinkedList<Type>::equals(GenericReference element, GenericReference value) {
                return ((Type &) element) == ((Type &) (value));
            }

            template <typename Type>
            MixedLinkedList<Type>::MixedLinkedList() : MixedLinkedList0({allocate, destroy, equals}) {}

            template <typename Type>
            MixedLinkedList<Type>::MixedLinkedList(const MixedLinkedList <Type> &other) :
                MixedLinkedList0(other) {}

            template <typename Type>
            $RetNotIgnored()
            Size MixedLinkedList<Type>::getLength() const {
                return MixedLinkedList0::getLength0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedLinkedList<Type>::isEmpty() const {
                return MixedLinkedList0::isEmpty0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedLinkedList<Type>::contain(const Type &value) const {
                return MixedLinkedList0::contain0((GenericReference) value);
            }

            template <typename Type>
            $RetRequiresRelease()
            MixedLinkedList <Type> *MixedLinkedList<Type>::copy() const {
                return new MixedLinkedList<Type>(*this);
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedLinkedList<Type>::getLast() const {
                return (Type &) MixedLinkedList0::getLast0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedLinkedList<Type>::getFirst() const {
                return (Type &) MixedLinkedList0::getFirst0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedLinkedList<Type>::get(Size index) const {
                return reinterpret_cast<Type &>(MixedLinkedList0::get0(index));
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedLinkedList<Type>::operator[](Size index) const {
                return (Type &) MixedLinkedList0::get0(index);
            }

            template <typename Type>
            core::Iterator<Type> *MixedLinkedList<Type>::iterator() const {
                return List<Type>::
                    template getIterator<MixedLinkedListIterator>(MixedLinkedList0::iterator, this);
            }

            template <typename Type>
            $RetNotIgnored()
            typename core::Iterable<Type>::ForeachIterator MixedLinkedList<Type>::begin() const {
                return MixedList<Type>::begin();
            }

            template <typename Type>
            $RetNotIgnored()
            constexpr InvalidType MixedLinkedList<Type>::end() const {
                return MixedList<Type>::end();
            }

            template <typename Type>
            void MixedLinkedList<Type>::addLast(const Type &element) {
                MixedLinkedList0::addLast0((GenericReference) element);
            }

            template <typename Type>
            void MixedLinkedList<Type>::addLastReferenced(const Type &element) {
                MixedLinkedList0::addLastReferenced0((GenericReference) element);
            }

            template <typename Type>
            Type MixedLinkedList<Type>::removeLast() {
                Type value = this->getLast();
                MixedLinkedList0::removeLast0();
                return value;
            }

            template <typename Type>
            void MixedLinkedList<Type>::addFirst(const Type &element) {
                MixedLinkedList0::addFirst0((GenericReference) element);
            }

            template <typename Type>
            void MixedLinkedList<Type>::addFirstReferenced(const Type &element) {
                MixedLinkedList0::addFirstReferenced0((GenericReference) element);
            }

            template <typename Type>
            Type MixedLinkedList<Type>::removeFirst() {
                Type value = this->getFirst();
                MixedLinkedList0::removeFirst0();
                return value;
            }

            template <typename Type>
            void MixedLinkedList<Type>::add(const Type &element) {
                this->addLast(element);
            }

            template <typename Type>
            void MixedLinkedList<Type>::addReferenced(const Type &element) {
                this->addLastReferenced(element);
            }

            template <typename Type>
            Type MixedLinkedList<Type>::remove() {
                return this->removeLast();
            }

            template <typename Type>
            void MixedLinkedList<Type>::push(const Type &element) {
                this->addFirst(element);
            }

            template <typename Type>
            void MixedLinkedList<Type>::pushReferenced(const Type &element) {
                this->addFirstReferenced(element);
            }

            template <typename Type>
            Type MixedLinkedList<Type>::popup() {
                return this->removeFirst();
            }
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_TCC
