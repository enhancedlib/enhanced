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

#ifndef ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0LINKED0LIST_TCC
#define ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0LINKED0LIST_TCC

#include "EnhancedBasic/collection/referenced/ReferencedLinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

namespace EnhancedBasic {
    namespace collection{
        namespace referenced {
            template <typename Type>
            ReferencedLinkedList<Type>::ReferencedLinkedListIterator::ReferencedLinkedListIterator(
                const ReferencedLinkedList<Type> *referenceLinkedList) :
                ReferencedLinkedListIterator0(referenceLinkedList) {}

            template <typename Type>
            bool ReferencedLinkedList<Type>::ReferencedLinkedListIterator::hasNext() const {
                return ReferencedLinkedListIterator0::hasNext0();
            }

            template <typename Type>
            const core::Iterator<Type> *ReferencedLinkedList<Type>::ReferencedLinkedListIterator::next() const {
                ReferencedLinkedListIterator0::next0();
                return this;
            }

            template <typename Type>
            bool ReferencedLinkedList<Type>::ReferencedLinkedListIterator::each() const {
                return ReferencedLinkedListIterator0::each0();
            }

            template <typename Type>
            Type &ReferencedLinkedList<Type>::ReferencedLinkedListIterator::get() const {
                return reinterpret_cast<Type &>(ReferencedLinkedListIterator0::get0());
            }

            template <typename Type>
            void ReferencedLinkedList<Type>::ReferencedLinkedListIterator::reset() const {
                ReferencedLinkedListIterator0::reset0();
            }

            template <typename Type>
            Size ReferencedLinkedList<Type>::ReferencedLinkedListIterator::count() const {
                return ReferencedLinkedListIterator0::count0();
            }

            template <typename Type>
            bool ReferencedLinkedList<Type>::equals(GenericReference element, GenericReference value) {
                return reinterpret_cast<Type &>(element) == reinterpret_cast<Type &>(value);
            }

            template <typename Type>
            ReferencedLinkedList<Type>::ReferencedLinkedList(const ReferencedLinkedList<Type> &copy) :
                ReferencedLinkedList0(copy) {}

            template <typename Type>
            Size ReferencedLinkedList<Type>::getLength() const {
                return ReferencedLinkedList0::getLength0();
            }

            template <typename Type>
            bool ReferencedLinkedList<Type>::isEmpty() const {
                return ReferencedLinkedList0::isEmpty0();
            }

            template <typename Type>
            bool ReferencedLinkedList<Type>::contain(const Type &value) const {
                return ReferencedLinkedList0::contain0((GenericReference) value);
            }

            template <typename Type>
            ReferencedLinkedList<Type> *ReferencedLinkedList<Type>::copy() const {
                return new ReferencedLinkedList<Type>(*this);
            }

            template <typename Type>
            Type &ReferencedLinkedList<Type>::getLast() const {
                return reinterpret_cast<Type &>(ReferencedLinkedList0::getLast0());
            }

            template <typename Type>
            Type &ReferencedLinkedList<Type>::getFirst() const {
                return reinterpret_cast<Type &>(ReferencedLinkedList0::getFirst0());
            }

            template <typename Type>
            Type &ReferencedLinkedList<Type>::get(Size index) const {
                return reinterpret_cast<Type &>(ReferencedLinkedList0::get0(index));
            }

            template <typename Type>
            Type &ReferencedLinkedList<Type>::operator[](Size index) const {
                return reinterpret_cast<Type &>(ReferencedLinkedList0::get0(index));
            }

            template <typename Type>
            core::Iterator<Type> *ReferencedLinkedList<Type>::iterator() const {
                return List<Type>::template
                getIterator<ReferencedLinkedListIterator>(ReferencedLinkedList0::iterator, this);
            }

            template <typename Type>
            typename core::Iterable<Type>::ForeachIterator ReferencedLinkedList<Type>::begin() const {
                return List<Type>::begin();
            }

            template <typename Type>
            constexpr InvalidType ReferencedLinkedList<Type>::end() const {
                return List<Type>::end();
            }

            template <typename Type>
            void ReferencedLinkedList<Type>::addLast(const Type &element) {
                ReferencedLinkedList0::addLast0((GenericReference) element);
            }

            template <typename Type>
            Type ReferencedLinkedList<Type>::removeLast() {
                Type value = this->getLast();
                ReferencedLinkedList0::removeLast0();
                return value;
            }

            template <typename Type>
            void ReferencedLinkedList<Type>::addFirst(const Type &element) {
                ReferencedLinkedList0::addFirst0((GenericReference) element);
            }

            template <typename Type>
            Type ReferencedLinkedList<Type>::removeFirst() {
                Type value = this->getFirst();
                ReferencedLinkedList0::removeFirst0();
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

#endif // !ENHANCED_BASIC_COLLECTION_REFERENCED_REFERENCED0LINKED0LIST_TCC
