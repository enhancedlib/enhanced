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
 * The authors or copyright holders be not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by This software,
 * the authors or copyright holders may provide possible solutions,
 * but it does not mean that the authors or copyright holders
 * will definitely solve the problem.
 * In no event shall the author or copyright
 * owner be liable for any claims, damages or other liabilities.
 *
 * You should see the Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#ifndef ENHANCED_BASIC_CORE_VECTOR_HPP
#define ENHANCED_BASIC_CORE_VECTOR_HPP

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
            VectorIteratorImpl(vector) {}

        template <typename Type>
        $RetNotIgnored()
        bool Vector<Type>::VectorIterator::hasNext() const {
            return VectorIteratorImpl::hasNext0();
        }

        template <typename Type>
        const core::Iterator <Type> *Vector<Type>::VectorIterator::next() const {
            VectorIteratorImpl::next0();
            return this;
        }

        template <typename Type>
        $RetNotIgnored()
        bool Vector<Type>::VectorIterator::each() const {
            return VectorIteratorImpl::each0();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &Vector<Type>::VectorIterator::get() const {
            return (Type &) VectorIteratorImpl::get0();
        }

        template <typename Type>
        void Vector<Type>::VectorIterator::reset() const {
            VectorIteratorImpl::reset0();
        }

        template <typename Type>
        $RetNotIgnored()
        Size Vector<Type>::VectorIterator::count() const {
            return VectorIteratorImpl::count0();
        }

        template <typename Type>
        $RetRequiresRelease()
        void *Vector<Type>::allocateArray(const Size size) {
            return operator new(size * sizeof(Type));
        }

        template <typename Type>
        void Vector<Type>::copyArray(void *destination, void *source, const Size size) {
            for (Size index = 0; index < size; ++ index) {
                static_cast<Type *>(destination)[index] = ((Type *) (source))[index];
            }
        }

        template <typename Type>
        void Vector<Type>::moveArray(void *destination, void *source, const Size size) {
            for (Size index = 0; index < size; ++ index) {
                static_cast<Type *>(destination)[index] = (Type &&) ((Type *) (source))[index];
            }
        }

        template <typename Type>
        void *Vector<Type>::index(void *elements, const Size index) {
            return static_cast<void *>(static_cast<Type *>(elements) + index);
        }

        template <typename Type>
        GenericReference Vector<Type>::getElement(void *elements, const Size index) {
            return (GenericReference) static_cast<Type *>(elements)[index];
        }

        template <typename Type>
        void Vector<Type>::setElement(void *elements, const Size index, GenericReference value) {
            static_cast<Type *>(elements)[index] = (Type &&) (value);
        }

        template <typename Type>
        bool Vector<Type>::equals(GenericReference element, GenericReference value) {
            return ((Type &) (element)) == ((Type &) (value));
        }

        template <typename Type>
        Vector<Type>::Vector() : VectorImpl(UINT8_MAX, {
            Vector::allocateArray, Vector::copyArray, Vector::moveArray, Vector::index,
            Vector::getElement, Vector::setElement, Vector::equals
        }) {}

        template <typename Type>
        Vector<Type>::Vector(Size maxCount) : VectorImpl(maxCount, {
            Vector::allocateArray, Vector::copyArray, Vector::moveArray, Vector::index,
            Vector::getElement, Vector::setElement, Vector::equals
        }) {}

        template <typename Type>
        Vector<Type>::Vector(const Vector <Type> &other) : VectorImpl(other) {}

        template <typename Type>
        $RetNotIgnored()
        Size Vector<Type>::getLength() const {
            return VectorImpl::getLength0();
        }

        template <typename Type>
        $RetNotIgnored()
        bool Vector<Type>::isEmpty() const {
            return VectorImpl::isEmpty0();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &Vector<Type>::get(Size index) const {
            return (Type &) VectorImpl::get0(index);
        }

        template <typename Type>
        $RetNotIgnored()
        Type &Vector<Type>::operator[](Size index) const {
            return (Type &) (VectorImpl::get0(index));
        }

        template <typename Type>
        core::Iterator <Type> *Vector<Type>::iterator() const {
            return core::Iterable<Type>::template getIterator<VectorIterator>(VectorImpl::iterator, this);
        }

        template <typename Type>
        $RetNotIgnored()
        bool Vector<Type>::contain(const Type &value) const {
            return VectorImpl::contain0((GenericReference) value);
        }

        template <typename Type>
        $RetRequiresRelease()
        Vector <Type> *Vector<Type>::copy() const {
            return new Vector<Type>(*this);
        }

        template <typename Type>
        void Vector<Type>::add(const Type &element) {
            VectorImpl::add0((GenericReference) element);
        }

        template <typename Type>
        Type Vector<Type>::remove() {
            Type value = this->get(this->getLength() - 1);
            VectorImpl::remove0();
            return value;
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_CORE_VECTOR_HPP
