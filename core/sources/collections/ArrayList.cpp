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
#include <enhanced/core/generic.h>
#include <enhanced/core/exception/UnsupportedOperationException.h>

using enhanced_internal::core::collections::ArrayListImpl;
using enhanced::core::exception::UnsupportedOperationException;

ArrayListImpl::ArrayListImpl(const sizetype capacity, const GenericOperator genericOperator) :
    elements(new void*[capacity]), size(0), capacity(capacity), genericOperator(genericOperator) {}

ArrayListImpl::ArrayListImpl(const ArrayListImpl& other) : elements(new void*[other.capacity]), size(other.size),
    capacity(other.capacity), genericOperator(other.genericOperator) {
    assert(other.capacity >= other.size);
    for (sizetype index = 0; index < other.size; ++index) {
        elements[index] = genericOperator.allocate(GET_GENERIC_VALUE(other.elements[index]));
    }
}

ArrayListImpl::~ArrayListImpl() noexcept {
    while (size > 0) {
        genericOperator.destroy(elements[--size]);
    }
    delete[] elements;
}

NoIgnoreRet
sizetype ArrayListImpl::getSize0() const {
    return size;
}

NoIgnoreRet
bool ArrayListImpl::isEmpty0() const {
    return size == 0;
}

NoIgnoreRet
Generic& ArrayListImpl::get0(sizetype index) const {
    return GET_GENERIC_VALUE(elements[index]);
}

NoIgnoreRet
bool ArrayListImpl::contain0(Generic& value) const {
    for (sizetype index = 0; index < size; ++index) {
        if (genericOperator.equals(GET_GENERIC_VALUE(elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ArrayListImpl::add0(Generic& element) {
    if (size == capacity) {
        expand0(capacity);
    }

    elements[size] = genericOperator.allocate(element);
    ++size;
}

void ArrayListImpl::remove0() {
    if (isEmpty0()) throw UnsupportedOperationException("The list is empty");

    genericOperator.destroy(elements[--size]);
}

void ArrayListImpl::expand0(const sizetype size) {
    sizetype count = capacity + size;
    void** array = new void*[count];

    arrayCopy(array, elements, size, sizeof(void*));
    delete[] elements;

    elements = array;
    capacity = count;
}

void ArrayListImpl::shrink0(const sizetype size) {
    sizetype count = capacity - size;
    if (count < size) throw UnsupportedOperationException("Cannot shrink because the size is larger than the new capacity");

    void** array = new void*[count];

    arrayCopy(array, elements, count, sizeof(void*));
    delete[] elements;

    elements = array;
    capacity = count;
}

ArrayListImpl::ArrayListIteratorImpl::ArrayListIteratorImpl(const ArrayListImpl* arrayList) :
    arrayList(arrayList), indexer(arrayList->elements) {}

ArrayListImpl::ArrayListIteratorImpl::~ArrayListIteratorImpl() noexcept = default;

NoIgnoreRet
bool ArrayListImpl::ArrayListIteratorImpl::hasNext0() const {
    return indexer != (arrayList->elements + arrayList->getSize0());
}

void ArrayListImpl::ArrayListIteratorImpl::next0() const {
    ++indexer;
}

NoIgnoreRet
Generic& ArrayListImpl::ArrayListIteratorImpl::get0() const {
    return GET_GENERIC_VALUE(*indexer);
}

void ArrayListImpl::ArrayListIteratorImpl::reset0() const {
    indexer = arrayList->elements;
}

NoIgnoreRet
sizetype ArrayListImpl::ArrayListIteratorImpl::count0() const {
    return arrayList->getSize0();
}
