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

#include "enhanced/basic/collection/ArrayList.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"
#include "enhanced/core/array.h"
#include "enhanced/core/assert.h"
#include "enhanced/core/memory.h"

#include "enhanced/basic/util/generic.h"

using enhanced::basic::generic_impl::collection::ArrayListImpl;

ArrayListImpl::ArrayListIteratorImpl::ArrayListIteratorImpl(const ArrayListImpl* const arrayList) :
    arrayList(arrayList), indexer(arrayList->elements), isFirst(true), end(arrayList->elements + arrayList->getLength0()) {}

ArrayListImpl::ArrayListIteratorImpl::~ArrayListIteratorImpl() noexcept = default;

RetCannotIgnored()
bool ArrayListImpl::ArrayListIteratorImpl::hasNext0() const {
    return indexer != end;
}

void ArrayListImpl::ArrayListIteratorImpl::next0() const {
    ++indexer;
}

RetCannotIgnored()
bool ArrayListImpl::ArrayListIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !arrayList->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetCannotIgnored()
GenericReference ArrayListImpl::ArrayListIteratorImpl::get0() const {
    return generic_cast(*indexer);
}

void ArrayListImpl::ArrayListIteratorImpl::reset0() const {
    isFirst = true;
    indexer = arrayList->elements;
}

RetCannotIgnored()
Size ArrayListImpl::ArrayListIteratorImpl::count0() const {
    return arrayList->getLength0();
}

ArrayListImpl::ArrayListImpl(const Size maxCount, const GenericOperator genericOperator) :
    length(0), elements(new void*[maxCount]), maxCount(maxCount), genericOperator(genericOperator), iterator(null) {}

ArrayListImpl::ArrayListImpl(const ArrayListImpl& other) :
    length(other.length), elements(new void*[other.maxCount]), maxCount(other.maxCount), genericOperator(other.genericOperator), iterator(null) {
    assert(other.maxCount >= other.length);
    for (Size index = 0; index < other.length; ++index) {
        elements[index] = genericOperator.allocate(generic_cast(other.elements[index]));
    }
}

ArrayListImpl::~ArrayListImpl() noexcept {
    while (length > 0) {
        remove0();
    }
    delete[] elements;
    delete iterator;
}

RetCannotIgnored()
Size ArrayListImpl::getLength0() const {
    return length;
}

RetCannotIgnored()
bool ArrayListImpl::isEmpty0() const {
    return length == 0;
}

RetCannotIgnored()
GenericReference ArrayListImpl::get0(Size index) const {
    return generic_cast(elements[index]);
}

RetCannotIgnored()
bool ArrayListImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < length; ++index) {
        if (genericOperator.equals(generic_cast(elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ArrayListImpl::add0(GenericReference element) {
    if (length == maxCount) {
        expand0(maxCount);
    }

    elements[length] = genericOperator.allocate(element);
    ++length;
}

void ArrayListImpl::remove0() {
    genericOperator.destroy(elements[--length]);
}

void ArrayListImpl::expand0(const Size size) {
    Size count = maxCount + size;
    void** array = new void*[count];

    arrayCopy(array, elements, length, sizeof(void*));
    delete[] elements;

    elements = array;
    maxCount = count;
}

void ArrayListImpl::shrink0(const Size size) {
    Size count = maxCount - size;
    assert(count > length);

    void** array = new void*[count];

    arrayCopy(array, elements, count, sizeof(void*));
    delete[] elements;

    elements = array;
    maxCount = count;
}
