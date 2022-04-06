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

#ifndef ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_HPP
#define ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_HPP

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
                MixedLinkedListIteratorImpl(mixedLinkedList) {}

            template <typename Type>
            $RetNotIgnored()
            bool MixedLinkedList<Type>::MixedLinkedListIterator::hasNext() const {
                return MixedLinkedListIteratorImpl::hasNext0();
            }

            template <typename Type>
            const core::Iterator<Type> *MixedLinkedList<Type>::MixedLinkedListIterator::next() const {
                MixedLinkedListIteratorImpl::next0();
                return this;
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedLinkedList<Type>::MixedLinkedListIterator::each() const {
                return MixedLinkedListIteratorImpl::each0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedLinkedList<Type>::MixedLinkedListIterator::get() const {
                return (Type &) MixedLinkedListIteratorImpl::get0();
            }

            template <typename Type>
            void MixedLinkedList<Type>::MixedLinkedListIterator::reset() const {
                MixedLinkedListIteratorImpl::reset0();
            }

            template <typename Type>
            $RetNotIgnored()
            Size MixedLinkedList<Type>::MixedLinkedListIterator::count() const {
                return MixedLinkedListIteratorImpl::count0();
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
            MixedLinkedList<Type>::MixedLinkedList() : MixedLinkedListImpl(
                {MixedLinkedListImpl::allocate, MixedLinkedListImpl::destroy, MixedLinkedListImpl::equals}
            ) {}

            template <typename Type>
            MixedLinkedList<Type>::MixedLinkedList(const MixedLinkedList <Type> &other) :
                MixedLinkedListImpl(other) {}

            template <typename Type>
            $RetNotIgnored()
            Size MixedLinkedList<Type>::getLength() const {
                return MixedLinkedListImpl::getLength0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedLinkedList<Type>::isEmpty() const {
                return MixedLinkedListImpl::isEmpty0();
            }

            template <typename Type>
            $RetNotIgnored()
            bool MixedLinkedList<Type>::contain(const Type &value) const {
                return MixedLinkedListImpl::contain0((GenericReference) value);
            }

            template <typename Type>
            $RetRequiresRelease()
            MixedLinkedList <Type> *MixedLinkedList<Type>::copy() const {
                return new MixedLinkedList<Type>(*this);
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedLinkedList<Type>::getLast() const {
                return (Type &) MixedLinkedListImpl::getLast0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedLinkedList<Type>::getFirst() const {
                return (Type &) MixedLinkedListImpl::getFirst0();
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedLinkedList<Type>::get(Size index) const {
                return reinterpret_cast<Type &>(MixedLinkedListImpl::get0(index));
            }

            template <typename Type>
            $RetNotIgnored()
            Type &MixedLinkedList<Type>::operator[](Size index) const {
                return (Type &) MixedLinkedListImpl::get0(index);
            }

            template <typename Type>
            core::Iterator<Type> *MixedLinkedList<Type>::iterator() const {
                return List<Type>::
                    template getIterator<MixedLinkedListIterator>(MixedLinkedListImpl::iterator, this);
            }

            template <typename Type>
            $RetNotIgnored()
            typename core::Iterable<Type>::ForeachIterator MixedLinkedList<Type>::begin() const {
                return MixedList<Type>::begin();
            }

            template <typename Type>
            $RetNotIgnored()
            UnusedType MixedLinkedList<Type>::end() const {
                return MixedList<Type>::end();
            }

            template <typename Type>
            void MixedLinkedList<Type>::addLast(const Type &element) {
                MixedLinkedListImpl::addLast0((GenericReference) element);
            }

            template <typename Type>
            void MixedLinkedList<Type>::addLastReferenced(const Type &element) {
                MixedLinkedListImpl::addLastReferenced0((GenericReference) element);
            }

            template <typename Type>
            Type MixedLinkedList<Type>::removeLast() {
                Type value = this->getLast();
                MixedLinkedListImpl::removeLast0();
                return value;
            }

            template <typename Type>
            void MixedLinkedList<Type>::addFirst(const Type &element) {
                MixedLinkedListImpl::addFirst0((GenericReference) element);
            }

            template <typename Type>
            void MixedLinkedList<Type>::addFirstReferenced(const Type &element) {
                MixedLinkedListImpl::addFirstReferenced0((GenericReference) element);
            }

            template <typename Type>
            Type MixedLinkedList<Type>::removeFirst() {
                Type value = this->getFirst();
                MixedLinkedListImpl::removeFirst0();
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

#endif // !ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_HPP
