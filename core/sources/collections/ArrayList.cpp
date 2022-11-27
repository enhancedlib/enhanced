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
        other.elements = null;
        other.size = INVALID_SIZE;
        other.capacity = INVALID_SIZE;
    }

    $NoIgnoreReturn
    func ArrayListImpl::getFirst0() const -> void* {
        if (size == 0) throw UnsupportedOperationException("The list is empty");

        return elements[0];
    }

    $NoIgnoreReturn
    func ArrayListImpl::getLast0() const -> void* {
        if (size == 0) throw UnsupportedOperationException("The list is empty");

        return elements[size - 1];
    }

    $NoIgnoreReturn
    func ArrayListImpl::get0(sizetype index) const -> void* {
        if (index >= size) throw IndexOutOfBoundsException(index, size);

        return elements[index];
    }

    $NoIgnoreReturn
    func ArrayListImpl::indexOf0(void* value, OpEqual opEqual) const -> sizetype {
        for (sizetype index = 0; index < size; ++index) {
            if (opEqual(elements[index], value)) {
                return index;
            }
        }

        return INVALID_SIZE;
    }

    func ArrayListImpl::addFirst0(void* element, OpCopy opCopy) -> void {
        NOT_IMPLEMENTED();
    }

    func ArrayListImpl::addFirst1(void* element, OpMove opMove) -> void {
        NOT_IMPLEMENTED();
    }

    func ArrayListImpl::addLast0(void* element, OpCopy opCopy) -> void {
        if (size == capacity) {
            expand0();
        }

        elements[size] = opCopy(element);
        ++size;
    }

    func ArrayListImpl::addLast1(void* element, OpMove opMove) -> void {
        if (size == capacity) {
            expand0();
        }

        elements[size] = opMove(element);
        ++size;
    }

    func ArrayListImpl::removeFirst0(OpDestroy opDestroy) -> void {
        NOT_IMPLEMENTED();
    }

    func ArrayListImpl::removeLast0(OpDestroy opDestroy) -> void {
        assert(size > 0);

        opDestroy(elements[--size]);
    }

    func ArrayListImpl::setCapacity0(sizetype newCapacity) -> void {
        void** array = new void*[newCapacity];

        arrayCopy(array, elements, size, sizeof(void*));
        delete[] elements;

        elements = array;
        capacity = newCapacity;
    }

    func ArrayListImpl::expand0() -> void {
        expand0(expSizeFallback(capacity));
    }

    func ArrayListImpl::expand0(sizetype expSize) -> void {
        setCapacity0(capacity + expSize);
    }

    func ArrayListImpl::shrink0() -> void {
        setCapacity0(size);
    }

    func ArrayListImpl::shrink0(sizetype shrSize) -> void {
        setCapacity0(capacity - shrSize);
    }

    func ArrayListImpl::clear0(OpDestroy opDestroy) -> void {
        while (size > 0) {
            opDestroy(elements[--size]);
        }
    }

    ArrayListImpl::ArrayListIteratorImpl::ArrayListIteratorImpl(const ArrayListImpl* arrayList) :
        arrayList(arrayList), indexer(arrayList->elements) {}

    $NoIgnoreReturn
    func ArrayListImpl::ArrayListIteratorImpl::hasNext0() const -> bool {
        return indexer != (arrayList->elements + arrayList->size);
    }

    func ArrayListImpl::ArrayListIteratorImpl::next0() const -> void {
        if (!hasNext0()) throw UnsupportedOperationException("The iterator is at the end of the list");

        ++indexer;
    }

    $NoIgnoreReturn
    func ArrayListImpl::ArrayListIteratorImpl::get0() const -> void* {
        if (arrayList->size == 0) throw UnsupportedOperationException("The list is empty");

        return *indexer;
    }

    func ArrayListImpl::ArrayListIteratorImpl::reset0() const -> void {
        indexer = arrayList->elements;
    }
}
