/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/basic/container/Vector.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"
#include "enhanced/core/assert.h"

#include "enhanced/basic/util/generic.h"

using enhanced::basic::generic_impl::container::VectorImpl;

VectorImpl::VectorImpl(const Size maxCount, const GenericOperator genericOperator) :
    maxCount(maxCount), length(0), elements(genericOperator.allocateArray(maxCount)),
    genericOperator(genericOperator), iterator(null) {}

VectorImpl::VectorImpl(const VectorImpl& other) :
    maxCount(other.maxCount), length(other.length), elements(other.genericOperator.allocateArray(other.maxCount)),
    genericOperator(other.genericOperator), iterator(null) {
    genericOperator.copyArray(elements, other.elements, other.length);
}

VectorImpl::~VectorImpl() noexcept {
    operator delete(elements);
    delete iterator;
}

RetCannotIgnored
Size VectorImpl::getLength0() const {
    return length;
}

RetCannotIgnored
bool VectorImpl::isEmpty0() const {
    return length == 0;
}

RetCannotIgnored
GenericReference VectorImpl::get0(const Size index) const {
    return genericOperator.getElement(elements, index);
}

RetCannotIgnored
bool VectorImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < length; ++index) {
        if (genericOperator.equals(get0(index), value)) {
            return true;
        }
    }

    return false;
}

void VectorImpl::add0(GenericReference element) {
    if (length == maxCount) {
        expand0(maxCount);
    }

    genericOperator.setElement(elements, length, element);
    ++length;
}

void VectorImpl::remove0() {
    --length;
}

void VectorImpl::expand0(const Size size) {
    Size count = maxCount + size;
    void* array = genericOperator.allocateArray(count);

    genericOperator.moveArray(array, elements, length);
    operator delete(elements);

    elements = array;
    maxCount = count;
}

void VectorImpl::shrink0(const Size size) {
    Size count = maxCount - size;
    assert(count > length);

    void* array = genericOperator.allocateArray(count);

    genericOperator.moveArray(array, elements, length);
    operator delete(elements);

    elements = array;
    maxCount = count;
}

VectorImpl::VectorIteratorImpl::VectorIteratorImpl(const VectorImpl* const vector) :
    vector(vector), indexer(vector->elements), isFirst(true),
    end(vector->genericOperator.index(vector->elements, vector->getLength0())) {}

VectorImpl::VectorIteratorImpl::~VectorIteratorImpl() noexcept = default;

RetCannotIgnored
bool VectorImpl::VectorIteratorImpl::hasNext0() const {
    return indexer != end;
}

void VectorImpl::VectorIteratorImpl::next0() const {
    indexer = vector->genericOperator.index(indexer, 1);
}

RetCannotIgnored
bool VectorImpl::VectorIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !vector->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetCannotIgnored
GenericReference VectorImpl::VectorIteratorImpl::get0() const {
    return generic_cast(indexer);
}

void VectorImpl::VectorIteratorImpl::reset0() const {
    isFirst = true;
    indexer = vector->elements;
}

RetCannotIgnored
Size VectorImpl::VectorIteratorImpl::count0() const {
    return vector->getLength0();
}
