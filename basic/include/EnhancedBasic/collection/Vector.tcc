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

#ifndef ENHANCED_BASIC_CORE_VECTOR_TCC
#define ENHANCED_BASIC_CORE_VECTOR_TCC

#include "EnhancedBasic/collection/Vector.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/memory.h"

#ifdef CXX_LANGUAGE

namespace EnhancedBasic {
    namespace collection {
        template <typename Type>
        Vector<Type>::VectorIterator::VectorIterator(const Vector<Type> *vector) :
            VectorIterator0(vector) {}

        template <typename Type>
        $RetNotIgnored()
        bool Vector<Type>::VectorIterator::hasNext() const {
            return VectorIterator0::hasNext0();
        }

        template <typename Type>
        const core::Iterator <Type> *Vector<Type>::VectorIterator::next() const {
            VectorIterator0::next0();
            return this;
        }

        template <typename Type>
        $RetNotIgnored()
        bool Vector<Type>::VectorIterator::each() const {
            return VectorIterator0::each0();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &Vector<Type>::VectorIterator::get() const {
            return reinterpret_cast<Type &>(VectorIterator0::get0());
        }

        template <typename Type>
        void Vector<Type>::VectorIterator::reset() const {
            VectorIterator0::reset0();
        }

        template <typename Type>
        $RetNotIgnored()
        Size Vector<Type>::VectorIterator::count() const {
            return VectorIterator0::count0();
        }

        template <typename Type>
        $RetRequiresRelease()
        GenericPointer Vector<Type>::allocateArray(const Size size) {
            return operator new(size * sizeof(Type));
        }

        template <typename Type>
        void Vector<Type>::destroyArray(GenericPointer elements, Size length) {
            for (Size index = 0; index < length; ++ index) {
                static_cast<Type *>(elements)[index].~Type();
            }
            operator delete(elements);
        }

        template <typename Type>
        void Vector<Type>::copyArray(GenericPointer destination, GenericPointer source, const Size size) {
            for (Size index = 0; index < size; ++ index) {
                static_cast<Type *>(destination)[index] = reinterpret_cast<Type *>(source)[index];
            }
        }

        template <typename Type>
        GenericPointer Vector<Type>::index(GenericPointer elements, const Size index) {
            return static_cast<GenericPointer>((static_cast<Type *>(elements) + index));
        }

        template <typename Type>
        GenericReference Vector<Type>::getElement(GenericPointer elements, const Size index) {
            return (GenericReference) static_cast<Type *>(elements)[index];
        }

        template <typename Type>
        void Vector<Type>::setElement(GenericPointer elements, const Size index, GenericReference value) {
            memoryCopy(&static_cast<Type *>(elements)[index],
                &reinterpret_cast<Type &>(value), sizeof(Type));
        }

        template <typename Type>
        bool Vector<Type>::equals(GenericReference element, GenericReference value) {
            return reinterpret_cast<Type &>(element) == reinterpret_cast<Type &>(value);
        }

        template <typename Type>
        Vector<Type>::Vector() : Vector0(UINT8_MAX, {
            allocateArray, destroyArray, copyArray, index, getElement, setElement, equals
        }) {}

        template <typename Type>
        Vector<Type>::Vector(Size maxCount) : Vector0(maxCount, {
            allocateArray, destroyArray, copyArray, index, getElement, setElement, equals
        }) {}

        template <typename Type>
        Vector<Type>::Vector(const Vector <Type> &copy) : Vector0(copy) {}

        template <typename Type>
        $RetNotIgnored()
        Size Vector<Type>::getLength() const {
            return Vector0::getLength0();
        }

        template <typename Type>
        $RetNotIgnored()
        bool Vector<Type>::isEmpty() const {
            return Vector0::isEmpty0();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &Vector<Type>::get(Size index) const {
            return reinterpret_cast<Type &>(Vector0::get0(index));
        }

        template <typename Type>
        $RetNotIgnored()
        Type &Vector<Type>::operator[](Size index) const {
            return reinterpret_cast<Type &>(Vector0::get0(index));
        }

        template <typename Type>
        core::Iterator <Type> *Vector<Type>::iterator() const {
            return core::Iterable<Type>::template getIterator<VectorIterator>(Vector0::iterator, this);
        }

        template <typename Type>
        $RetNotIgnored()
        bool Vector<Type>::contain(const Type &value) const {
            return Vector0::contain0((GenericReference) value);
        }

        template <typename Type>
        $RetRequiresRelease()
        Vector <Type> *Vector<Type>::copy() const {
            return new Vector<Type>(*this);
        }

        template <typename Type>
        void Vector<Type>::add(const Type &element) {
            Vector0::add0((GenericReference) element);
        }

        template <typename Type>
        Type Vector<Type>::remove() {
            Type value = this->get(this->getLength() - 1);
            Vector0::remove0();
            return value;
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_CORE_VECTOR_TCC
