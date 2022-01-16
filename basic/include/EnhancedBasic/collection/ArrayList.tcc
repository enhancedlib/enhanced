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

#ifndef ENHANCED_BASIC_COLLECTION_ARRAY0LIST_TCC
#define ENHANCED_BASIC_COLLECTION_ARRAY0LIST_TCC

#include "EnhancedBasic/collection/ArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

namespace EnhancedBasic {
    namespace collection {
        template <typename Type>
        ArrayList<Type>::ArrayListIterator::ArrayListIterator(const ArrayList<Type> *arrayList) :
            ArrayListIterator0(arrayList) {}

        template <typename Type>
        bool ArrayList<Type>::ArrayListIterator::hasNext() const {
            return ArrayListIterator0::hasNext0();
        }

        template <typename Type>
        const core::Iterator <Type> *ArrayList<Type>::ArrayListIterator::next() const {
            ArrayListIterator0::next0();
            return this;
        }

        template <typename Type>
        bool ArrayList<Type>::ArrayListIterator::each() const {
            return ArrayListIterator0::each0();
        }

        template <typename Type>
        Type &ArrayList<Type>::ArrayListIterator::get() const {
            return reinterpret_cast<Type &>(ArrayListIterator0::get0());
        }

        template <typename Type>
        void ArrayList<Type>::ArrayListIterator::reset() const {
            ArrayListIterator0::reset0();
        }

        template <typename Type>
        Size ArrayList<Type>::ArrayListIterator::count() const {
            return ArrayListIterator0::count0();
        }

        template <typename Type>
        GenericPointer ArrayList<Type>::allocate(GenericReference element) {
            return new Type(reinterpret_cast<Type &>(element));
        }

        template <typename Type>
        void ArrayList<Type>::destroy(GenericPointer element) {
            delete reinterpret_cast<Type *>(element);
        }

        template <typename Type>
        bool ArrayList<Type>::equals(GenericReference element, GenericReference value) {
            return reinterpret_cast<Type &>(element) == reinterpret_cast<Type &>(value);
        }

        template <typename Type>
        ArrayList<Type>::ArrayList() : ArrayList0(UINT8_MAX, {allocate, destroy, equals}) {}

        template <typename Type>
        ArrayList<Type>::ArrayList(Size maxCount) : ArrayList0(maxCount, {allocate, destroy, equals}) {}

        template <typename Type>
        ArrayList<Type>::ArrayList(const ArrayList<Type> &copy) : ArrayList0(copy) {}

        template <typename Type>
        Size ArrayList<Type>::getLength() const {
            return ArrayList0::getLength0();
        }

        template <typename Type>
        bool ArrayList<Type>::isEmpty() const {
            return ArrayList0::isEmpty0();
        }

        template <typename Type>
        Type &ArrayList<Type>::get(Size index) const {
            return reinterpret_cast<Type &>(ArrayList0::get0(index));
        }

        template <typename Type>
        Type &ArrayList<Type>::operator[](Size index) const {
            return reinterpret_cast<Type &>(ArrayList0::get0(index));
        }

        template <typename Type>
        core::Iterator <Type> *ArrayList<Type>::iterator() const {
            return core::Iterable<Type>::template getIterator<ArrayListIterator>(ArrayList0::iterator, this);
        }

        template <typename Type>
        bool ArrayList<Type>::contain(const Type &value) const {
            return ArrayList0::contain0((GenericReference) value);
        }

        template <typename Type>
        ArrayList<Type> *ArrayList<Type>::copy() const {
            return new ArrayList<Type>(*this);
        }

        template <typename Type>
        void ArrayList<Type>::add(const Type &element) {
            ArrayList0::add0((GenericReference) element);
        }

        template <typename Type>
        Type ArrayList<Type>::remove() {
            Type value = this->get(this->getLength() - 1);
            ArrayList0::remove0();
            return value;
        }
    }
}

#endif // !ENHANCED_BASIC_COLLECTION_ARRAY0LIST_TCC
