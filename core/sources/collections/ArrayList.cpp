/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#include <enhanced/collections/ArrayList.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Array.h>
#include <enhanced/Assert.h>
#include <enhanced/Memory.h>
#include <enhanced/exceptions/IndexOutOfBoundsException.h>
#include <enhanced/exceptions/InvalidStateException.h>
#include <enhanced/exceptions/NotImplementedError.h>

using enhanced::arrayCopy;
using enhanced::exceptions::IndexOutOfBoundsException;
using enhanced::exceptions::InvalidStateException;

namespace enhancedInternal::collections {
    ArrayListImpl::ArrayListImpl(sizetype capacity) :
        elements(new void*[capacity]), size(0), capacity(capacity), expSizeFallback([](sizetype capacity) {return capacity;}) {}

    ArrayListImpl::ArrayListImpl(const ArrayListImpl& other, OpCopy opCopy) : elements(new void*[other.capacity]), size(other.size),
        capacity(other.capacity), expSizeFallback([](sizetype capacity) {return capacity;}) {
        E_ASSERT(other.capacity >= other.size);
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

    [[RetNotIgnored]]
    void* ArrayListImpl::getFirst0() const {
        if (size == 0) throw InvalidStateException("The list is empty");

        return elements[0];
    }

    [[RetNotIgnored]]
    void* ArrayListImpl::getLast0() const {
        if (size == 0) throw InvalidStateException("The list is empty");

        return elements[size - 1];
    }

    [[RetNotIgnored]]
    void* ArrayListImpl::get0(sizetype index) const {
        if (index >= size) throw IndexOutOfBoundsException(index, size);

        return elements[index];
    }

    [[RetNotIgnored]]
    sizetype ArrayListImpl::indexOf0(void* value, OpEqual opEqual) const {
        for (sizetype index = 0; index < size; ++index) {
            if (opEqual(elements[index], value)) {
                return index;
            }
        }

        return INVALID_SIZE;
    }

    void ArrayListImpl::addFirst0(void* element, OpCopy opCopy) {
        if (size == capacity) {
            capacity = expSizeFallback(capacity);
        }

        void** array = new void*[capacity];
        arrayCopy(array + 1, elements, size);
        elements = array;

        elements[0] = opCopy(element);
        ++size;
    }

    void ArrayListImpl::addFirst1(void* element, OpMove opMove) {
        if (size == capacity) {
            capacity = expSizeFallback(capacity);
        }

        void** array = new void*[capacity];
        arrayCopy(array + 1, elements, size);
        elements = array;

        elements[0] = opMove(element);
        ++size;
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
        opDestroy(elements[0]);

        void** array = new void*[capacity];
        arrayCopy(array, elements + 1, size - 1);
        delete[] elements;

        elements = array;
        --size;
    }

    void ArrayListImpl::removeLast0(OpDestroy opDestroy) {
        if (size == 0) throw InvalidStateException("The list is empty");

        opDestroy(elements[--size]);
    }

    void ArrayListImpl::clear0(OpDestroy opDestroy) {
        if (elements == nullptr) return;

        while (size > 0) {
            opDestroy(elements[--size]);
        }
    }

    void ArrayListImpl::setCapacity0(sizetype newCapacity) {
        void** array = new void*[newCapacity];
        arrayCopy(array, elements, size);
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
        arrayList(arrayList), indexer(arrayList->elements - 1) {}

    [[RetNotIgnored]]
    bool ArrayListImpl::ArrayListIteratorImpl::isBegin0() const {
        return indexer == arrayList->elements - 1;
    }

    [[RetNotIgnored]]
    bool ArrayListImpl::ArrayListIteratorImpl::isEnd0() const {
        return indexer == arrayList->elements + arrayList->size;
    }

    [[RetNotIgnored]]
    bool ArrayListImpl::ArrayListIteratorImpl::hasNext0() const {
        return indexer != arrayList->elements + arrayList->size - 1;
    }

    void ArrayListImpl::ArrayListIteratorImpl::next0() const {
        if (isEnd0()) throw InvalidStateException("The iterator is at the end of the list");
        ++indexer;
    }

    void ArrayListImpl::ArrayListIteratorImpl::prev0() const {
        if (isBegin0()) throw InvalidStateException("The iterator is at the begin of the list");
        --indexer;
    }

    [[RetNotIgnored]]
    void* ArrayListImpl::ArrayListIteratorImpl::get0() const {
        if (isBegin0() || isEnd0()) throw InvalidStateException("Current location of the iterator is not valid");
        return *indexer;
    }

    void ArrayListImpl::ArrayListIteratorImpl::reset0() const {
        indexer = arrayList->elements - 1;
    }
}
