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

#include <enhanced/core/collections/refer/ReferArrayList.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/types.h>
#include <enhanced/core/array.h>
#include <enhanced/core/assert.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/generic.h>
#include <enhanced/core/exception/UnsupportedOperationException.h>

using enhanced_internal::core::collections::refer::ReferArrayListImpl;
using enhanced::core::exception::UnsupportedOperationException;

ReferArrayListImpl::ReferArrayListImpl(const sizetype capacity, const GenericOperator genericOperator) :
    elements(new void*[capacity]), size(0), capacity(capacity), genericOperator(genericOperator) {}

ReferArrayListImpl::ReferArrayListImpl(const ReferArrayListImpl& other) :
    elements(new void*[other.capacity]), size(other.size), capacity(other.capacity), genericOperator(other.genericOperator) {
    assert(other.capacity >= other.size);
    for (sizetype index = 0; index < other.size; ++index) {
        elements[index] = other.elements[index];
    }
}

ReferArrayListImpl::~ReferArrayListImpl() noexcept {
    delete[] elements;
}

NoIgnoreRet
sizetype ReferArrayListImpl::getSize0() const {
    return size;
}

NoIgnoreRet
bool ReferArrayListImpl::isEmpty0() const {
    return size == 0;
}

NoIgnoreRet
Generic& ReferArrayListImpl::get0(const sizetype index) const {
    return GET_GENERIC_VALUE(elements[index]);
}

NoIgnoreRet
bool ReferArrayListImpl::contain0(Generic& value) const {
    for (sizetype index = 0; index < size; ++index) {
        if (genericOperator.equals(GET_GENERIC_VALUE(elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ReferArrayListImpl::add0(Generic& element) {
    if (size == capacity) {
        expand0(capacity);
    }

    elements[size] = &element;
    ++size;
}

void ReferArrayListImpl::remove0() {
    if (isEmpty0()) throw UnsupportedOperationException("The list is empty");

    --size;
}

void ReferArrayListImpl::expand0(const sizetype size) {
    sizetype count = capacity + size;
    void** array = new void* [count];

    arrayCopy(array, elements, size, sizeof(void*));
    delete[] elements;

    elements = array;
    capacity = count;
}

void ReferArrayListImpl::shrink0(const sizetype size) {
    sizetype count = capacity - size;
    if (count < size) throw UnsupportedOperationException("Cannot shrink because the size is larger than the new capacity");

    void** array = new void* [count];

    arrayCopy(array, elements, count, sizeof(void*));
    delete[] elements;

    elements = array;
    capacity = count;
}

ReferArrayListImpl::ReferArrayListIteratorImpl::
ReferArrayListIteratorImpl(const ReferArrayListImpl* referenceArrayList) :
    referenceArrayList(referenceArrayList), indexer(referenceArrayList->elements) {}

ReferArrayListImpl::ReferArrayListIteratorImpl::~ReferArrayListIteratorImpl() noexcept = default;

NoIgnoreRet
bool ReferArrayListImpl::ReferArrayListIteratorImpl::hasNext0() const {
    return indexer != (referenceArrayList->elements + referenceArrayList->getSize0());
}

void ReferArrayListImpl::ReferArrayListIteratorImpl::next0() const {
    ++indexer;
}

NoIgnoreRet
Generic& ReferArrayListImpl::ReferArrayListIteratorImpl::get0() const {
    return GET_GENERIC_VALUE(*indexer);
}

void ReferArrayListImpl::ReferArrayListIteratorImpl::reset0() const {
    indexer = referenceArrayList->elements;
}

NoIgnoreRet
sizetype ReferArrayListImpl::ReferArrayListIteratorImpl::count0() const {
    return referenceArrayList->getSize0();
}
