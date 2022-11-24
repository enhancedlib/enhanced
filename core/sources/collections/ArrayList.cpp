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

#include <enhanced/core/collections/ArrayList.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/array.h>
#include <enhanced/core/assert.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/exceptions/IndexOutOfBoundsException.h>
#include <enhanced/core/exceptions/UnsupportedOperationException.h>

using enhanced::core::arrayCopy;
using enhanced::core::exceptions::IndexOutOfBoundsException;
using enhanced::core::exceptions::UnsupportedOperationException;

namespace enhancedInternal::core::collections {
    ArrayListImpl::ArrayListImpl(const sizetype capacity) :
        elements(new void*[capacity]), size(0), capacity(capacity), fallbackExpSize([](sizetype capacity) {return capacity;}) {}

    ArrayListImpl::ArrayListImpl(const ArrayListImpl& other, OpCopy opCopy) : elements(new void*[other.capacity]), size(other.size),
        capacity(other.capacity), fallbackExpSize([](sizetype capacity) {return capacity;}) {
        assert(other.capacity >= other.size);
        for (sizetype index = 0; index < other.size; ++index) {
            elements[index] = opCopy(other.elements[index]);
        }
    }

    ArrayListImpl::ArrayListImpl(ArrayListImpl&& other) noexcept : elements(other.elements), size(other.size),
        capacity(other.capacity), fallbackExpSize([](sizetype capacity) {return capacity;}) {
        other.elements = null;
        other.size = INVALID_SIZE;
        other.capacity = INVALID_SIZE;
    }

    func ArrayListImpl::destruct0(OpDestroy opDestroy) noexcept -> void {
        clear0(opDestroy);
        delete[] elements;
    }

    $(NoIgnoreReturn)
    func ArrayListImpl::get0(sizetype index) const -> void* {
        if (index >= size) throw IndexOutOfBoundsException(index, size);

        return elements[index];
    }

    $(NoIgnoreReturn)
    func ArrayListImpl::indexOf0(void* value, OpEqual opEqual) const -> sizetype {
        for (sizetype index = 0; index < size; ++index) {
            if (opEqual(elements[index], value)) {
                return index;
            }
        }

        return INVALID_SIZE;
    }

    func ArrayListImpl::add0(void* element, OpCopy opCopy) -> void {
        if (size == capacity) {
            expand0();
        }

        elements[size] = opCopy(element);
        ++size;
    }

    func ArrayListImpl::addMoved0(void* element, OpMove opMove) -> void {
        if (size == capacity) {
            expand0();
        }

        elements[size] = opMove(element);
        ++size;
    }

    func ArrayListImpl::remove0(OpDestroy opDestroy) -> void {
        if (size == 0) throw UnsupportedOperationException("The list is empty");

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
        expand0(fallbackExpSize(capacity));
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

    $(NoIgnoreReturn)
    func ArrayListImpl::ArrayListIteratorImpl::hasNext0() const -> bool {
        return indexer != (arrayList->elements + arrayList->size);
    }

    func ArrayListImpl::ArrayListIteratorImpl::next0() const -> void {
        if (!hasNext0()) throw UnsupportedOperationException("The iterator is at the end of the list");

        ++indexer;
    }

    $(NoIgnoreReturn)
    func ArrayListImpl::ArrayListIteratorImpl::get0() const -> void* {
        if (arrayList->size == 0) throw UnsupportedOperationException("The list is empty");

        return *indexer;
    }

    func ArrayListImpl::ArrayListIteratorImpl::reset0() const -> void {
        indexer = arrayList->elements;
    }
}
