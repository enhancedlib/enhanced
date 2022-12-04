/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <enhanced/collections/ArrayList.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Array.h>
#include <enhanced/Assert.h>
#include <enhanced/Memory.h>
#include <enhanced/exceptions/IndexOutOfBoundsException.h>
#include <enhanced/exceptions/UnsupportedOperationException.h>
#include <enhanced/exceptions/NotImplementedError.h>

using enhanced::arrayCopy;
using enhanced::exceptions::IndexOutOfBoundsException;
using enhanced::exceptions::UnsupportedOperationException;

namespace enhancedInternal::collections {
    ArrayListImpl::ArrayListImpl(sizetype capacity) :
        elements(new void*[capacity]), size(0), capacity(capacity), expSizeFallback([](sizetype capacity) {return capacity;}) {}

    ArrayListImpl::ArrayListImpl(const ArrayListImpl& other, OpCopy opCopy) : elements(new void*[other.capacity]), size(other.size),
        capacity(other.capacity), expSizeFallback([](sizetype capacity) {return capacity;}) {
        assert(other.capacity >= other.size);
        for (sizetype index = 0; index < other.size; ++index) {
            elements[index] = opCopy(other.elements[index]);
        }
    }

    ArrayListImpl::ArrayListImpl(ArrayListImpl&& other) noexcept : elements(other.elements), size(other.size),
        capacity(other.capacity), expSizeFallback([](sizetype capacity) {return capacity;}) {
        other.elements = nullptr;
        other.size = INVALID_SIZE;
        other.capacity = INVALID_SIZE;
    }

    $NoIgnoreReturn
    void* ArrayListImpl::getFirst0() const {
        if (size == 0) throw UnsupportedOperationException("The list is empty");

        return elements[0];
    }

    $NoIgnoreReturn
    void* ArrayListImpl::getLast0() const {
        if (size == 0) throw UnsupportedOperationException("The list is empty");

        return elements[size - 1];
    }

    $NoIgnoreReturn
    void* ArrayListImpl::get0(sizetype index) const {
        if (index >= size) throw IndexOutOfBoundsException(index, size);

        return elements[index];
    }

    $NoIgnoreReturn
    sizetype ArrayListImpl::indexOf0(void* value, OpEqual opEqual) const {
        for (sizetype index = 0; index < size; ++index) {
            if (opEqual(elements[index], value)) {
                return index;
            }
        }

        return INVALID_SIZE;
    }

    void ArrayListImpl::addFirst0(void* element, OpCopy opCopy) {
        NOT_IMPLEMENTED();
    }

    void ArrayListImpl::addFirst1(void* element, OpMove opMove) {
        NOT_IMPLEMENTED();
    }

    void ArrayListImpl::addLast0(void* element, OpCopy opCopy) {
        if (size == capacity) {
            expand0();
        }

        elements[size] = opCopy(element);
        ++size;
    }

    void ArrayListImpl::addLast1(void* element, OpMove opMove) {
        if (size == capacity) {
            expand0();
        }

        elements[size] = opMove(element);
        ++size;
    }

    void ArrayListImpl::removeFirst0(OpDestroy opDestroy) {
        NOT_IMPLEMENTED();
    }

    void ArrayListImpl::removeLast0(OpDestroy opDestroy) {
        assert(size > 0);

        opDestroy(elements[--size]);
    }

    void ArrayListImpl::clear0(OpDestroy opDestroy) {
        while (size > 0) {
            opDestroy(elements[--size]);
        }
    }

    void ArrayListImpl::setCapacity0(sizetype newCapacity) {
        void** array = new void*[newCapacity];

        arrayCopy(array, elements, size, sizeof(void*));
        delete[] elements;

        elements = array;
        capacity = newCapacity;
    }

    void ArrayListImpl::expand0() {
        expand0(expSizeFallback(capacity));
    }

    void ArrayListImpl::expand0(sizetype expSize) {
        setCapacity0(capacity + expSize);
    }

    void ArrayListImpl::shrink0() {
        shrink0(size, nullptr);
    }

    void ArrayListImpl::shrink0(sizetype shrSize, OpDestroy opDestroy) {
        sizetype newCapacity = capacity - shrSize;
        while (newCapacity < size) {
            removeLast0(opDestroy);
        }
        setCapacity0(newCapacity);
    }

    ArrayListImpl::ArrayListIteratorImpl::ArrayListIteratorImpl(const ArrayListImpl* arrayList) :
        arrayList(arrayList), indexer(arrayList->elements) {}

    $NoIgnoreReturn
    bool ArrayListImpl::ArrayListIteratorImpl::hasNext0() const {
        return indexer != (arrayList->elements + arrayList->size);
    }

    void ArrayListImpl::ArrayListIteratorImpl::next0() const {
        if (!hasNext0()) throw UnsupportedOperationException("The iterator is at the end of the list");

        ++indexer;
    }

    $NoIgnoreReturn
    void* ArrayListImpl::ArrayListIteratorImpl::get0() const {
        if (arrayList->size == 0) throw UnsupportedOperationException("The list is empty");

        return *indexer;
    }

    void ArrayListImpl::ArrayListIteratorImpl::reset0() const {
        indexer = arrayList->elements;
    }
}
