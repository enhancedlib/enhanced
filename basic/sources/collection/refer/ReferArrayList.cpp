/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/basic/collection/refer/ReferArrayList.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"
#include "enhanced/core/array.h"
#include "enhanced/core/assert.h"

#include "enhanced/basic/util/generic.h"

using enhanced::basic::generic_impl::collection::refer::ReferArrayListImpl;

ReferArrayListImpl::ReferArrayListIteratorImpl::
ReferArrayListIteratorImpl(const ReferArrayListImpl* const referenceArrayList) :
    referenceArrayList(referenceArrayList), indexer(referenceArrayList->elements), isFirst(true),
    end(referenceArrayList->elements + referenceArrayList->getLength0()) {}

ReferArrayListImpl::ReferArrayListIteratorImpl::~ReferArrayListIteratorImpl() noexcept = default;

RetCannotIgnored()
bool ReferArrayListImpl::ReferArrayListIteratorImpl::hasNext0() const {
    return indexer != end;
}

void ReferArrayListImpl::ReferArrayListIteratorImpl::next0() const {
    ++indexer;
}

RetCannotIgnored()
bool ReferArrayListImpl::ReferArrayListIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !referenceArrayList->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetCannotIgnored()
GenericReference ReferArrayListImpl::ReferArrayListIteratorImpl::get0() const {
    return generic_cast(*indexer);
}

void ReferArrayListImpl::ReferArrayListIteratorImpl::reset0() const {
    isFirst = true;
    indexer = referenceArrayList->elements;
}

RetCannotIgnored()
Size ReferArrayListImpl::ReferArrayListIteratorImpl::count0() const {
    return referenceArrayList->getLength0();
}

ReferArrayListImpl::ReferArrayListImpl(const Size maxCount, const GenericOperator genericOperator) :
    length(0), elements(new void* [maxCount]), maxCount(maxCount),
    genericOperator(genericOperator), iterator(null) {}

ReferArrayListImpl::ReferArrayListImpl(const ReferArrayListImpl& other) :
    length(other.length), elements(new void* [other.maxCount]), maxCount(other.maxCount),
    genericOperator(other.genericOperator), iterator(null) {
    assert(other.maxCount >= other.length);
    for (Size index = 0; index < other.length; ++index) {
        elements[index] = other.elements[index];
    }
}

ReferArrayListImpl::~ReferArrayListImpl() noexcept {
    delete[] elements;
}

RetCannotIgnored()
Size ReferArrayListImpl::getLength0() const {
    return length;
}

RetCannotIgnored()
bool ReferArrayListImpl::isEmpty0() const {
    return length == 0;
}

RetCannotIgnored()
GenericReference ReferArrayListImpl::get0(const Size index) const {
    return generic_cast(elements[index]);
}

RetCannotIgnored()
bool ReferArrayListImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < length; ++index) {
        if (genericOperator.equals(generic_cast(elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ReferArrayListImpl::add0(GenericReference element) {
    if (length == maxCount) {
        expand0(maxCount);
    }

    elements[length] = &element;
    ++length;
}

void ReferArrayListImpl::remove0() {
    --length;
}

void ReferArrayListImpl::expand0(const Size size) {
    Size count = maxCount + size;
    void** array = new void* [count];

    arrayCopy(array, elements, length, sizeof(void*));
    delete[] elements;

    elements = array;
    maxCount = count;
}

void ReferArrayListImpl::shrink0(const Size size) {
    Size count = maxCount - size;
    assert(count > length);

    void** array = new void* [count];

    arrayCopy(array, elements, count, sizeof(void*));
    delete[] elements;

    elements = array;
    maxCount = count;
}
