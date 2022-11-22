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
#include <enhanced/core/exception/IndexOutOfBoundsException.h>
#include <enhanced/core/exception/UnsupportedOperationException.h>

using enhanced::core::arrayCopy;
using enhanced::core::exception::IndexOutOfBoundsException;
using enhanced::core::exception::UnsupportedOperationException;

namespace enhancedInternal::core::collections {
    ArrayListImpl::ArrayListImpl(const sizetype capacity, const GenericOperator genericOperator) :
        elements(new void*[capacity]), size(0), capacity(capacity), genericOperator(genericOperator) {}

    ArrayListImpl::ArrayListImpl(const ArrayListImpl& other) : elements(new void*[other.capacity]), size(other.size),
        capacity(other.capacity), genericOperator(other.genericOperator) {
        assert(other.capacity >= other.size);
        for (sizetype index = 0; index < other.size; ++index) {
            elements[index] = genericOperator.copy(other.elements[index]);
        }
    }

    ArrayListImpl::ArrayListImpl(ArrayListImpl&& other) noexcept : elements(other.elements), size(other.size),
        capacity(other.capacity), genericOperator(other.genericOperator) {
        other.elements = null;
        other.size = INVALID_SIZE;
        other.capacity = INVALID_SIZE;
    }

    ArrayListImpl::~ArrayListImpl() noexcept {
        clear0();
        delete[] elements;
    }

    $(NoIgnoreReturn)
    func ArrayListImpl::get0(sizetype index) const -> void* {
        if (index >= size) throw IndexOutOfBoundsException(index, size);

        return elements[index];
    }

    $(NoIgnoreReturn)
    func ArrayListImpl::contain0(void* value) const -> bool {
        for (sizetype index = 0; index < size; ++index) {
            if (genericOperator.equals(elements[index], value)) {
                return true;
            }
        }

        return false;
    }

    func ArrayListImpl::add0(void* element) -> void {
        if (size == capacity) {
            expand0(capacity);
        }

        elements[size] = genericOperator.copy(element);
        ++size;
    }

    func ArrayListImpl::addMoved0(void* element) -> void {
        if (size == capacity) {
            expand0(capacity);
        }

        elements[size] = genericOperator.move(element);
        ++size;
    }

    func ArrayListImpl::remove0() -> void {
        if (size == 0) throw UnsupportedOperationException("The list is empty");

        genericOperator.destroy(elements[--size]);
    }

    func ArrayListImpl::expand0(const sizetype expSize) -> void {
        sizetype newCapacity = capacity + expSize;
        void** array = new void*[newCapacity];

        arrayCopy(array, elements, size, sizeof(void*));
        delete[] elements;

        elements = array;
        capacity = newCapacity;
    }

    func ArrayListImpl::shrink0(const sizetype shrSize) -> void {
        sizetype newCapacity = capacity - shrSize;
        if (newCapacity < size) throw UnsupportedOperationException("Cannot shrink because the size is larger than the new capacity");

        void** array = new void*[newCapacity];

        arrayCopy(array, elements, size, sizeof(void*));
        delete[] elements;

        elements = array;
        capacity = newCapacity;
    }

    func ArrayListImpl::clear0() -> void {
        while (size > 0) {
            genericOperator.destroy(elements[--size]);
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
