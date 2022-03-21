/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#include "EnhancedBasic/collection/referenced/ReferencedArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/array.h"
#include "EnhancedCore/assert.h"

#include "EnhancedBasic/generic/Generic.h"

using BasicGenericImpl::collection::referenced::ReferencedArrayListImpl;

ReferencedArrayListImpl::ReferencedArrayListIteratorImpl::
ReferencedArrayListIteratorImpl(const ReferencedArrayListImpl *const referenceArrayList) :
    referenceArrayList(referenceArrayList), indexer(referenceArrayList->elements), isFirst(true),
    end(referenceArrayList->elements + referenceArrayList->getLength0()) {}

ReferencedArrayListImpl::ReferencedArrayListIteratorImpl::~ReferencedArrayListIteratorImpl() noexcept = default;

$RetNotIgnored()
bool ReferencedArrayListImpl::ReferencedArrayListIteratorImpl::hasNext0() const {
    return this->indexer != this->end;
}

void ReferencedArrayListImpl::ReferencedArrayListIteratorImpl::next0() const {
    ++ this->indexer;
}

$RetNotIgnored()
bool ReferencedArrayListImpl::ReferencedArrayListIteratorImpl::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->referenceArrayList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference ReferencedArrayListImpl::ReferencedArrayListIteratorImpl::get0() const {
    return generic_cast(*this->indexer);
}

void ReferencedArrayListImpl::ReferencedArrayListIteratorImpl::reset0() const {
    this->isFirst = true;
    this->indexer = this->referenceArrayList->elements;
}

$RetNotIgnored()
Size ReferencedArrayListImpl::ReferencedArrayListIteratorImpl::count0() const {
    return this->referenceArrayList->getLength0();
}

ReferencedArrayListImpl::ReferencedArrayListImpl(const Size maxCount, const GenericOperator genericOperator) :
    length(0), elements(new void *[maxCount]), maxCount(maxCount),
    genericOperator(genericOperator), iterator(null) {}

ReferencedArrayListImpl::ReferencedArrayListImpl(const ReferencedArrayListImpl &other) :
    length(other.length), elements(new void *[other.maxCount]), maxCount(other.maxCount),
    genericOperator(other.genericOperator), iterator(null) {
    assert(other.maxCount >= other.length);
    for (Size index = 0; index < other.length; ++ index) {
        this->elements[index] = other.elements[index];
    }
}

ReferencedArrayListImpl::~ReferencedArrayListImpl() noexcept {
    delete[] this->elements;
}

$RetNotIgnored()
Size ReferencedArrayListImpl::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool ReferencedArrayListImpl::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference ReferencedArrayListImpl::get0(const Size index) const {
    return generic_cast(this->elements[index]);
}

$RetNotIgnored()
bool ReferencedArrayListImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->genericOperator.equals(generic_cast(this->elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ReferencedArrayListImpl::add0(GenericReference element) {
    if (this->length == this->maxCount) {
        this->expand0(this->maxCount);
    }

    this->elements[this->length] = &element;
    ++ this->length;
}

void ReferencedArrayListImpl::remove0() {
    -- this->length;
}

void ReferencedArrayListImpl::expand0(const Size size) {
    Size count = this->maxCount + size;
    void **array = new void *[count];

    arrayCopy(array, this->elements, this->length, sizeof(void *));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}

void ReferencedArrayListImpl::shrink0(const Size size) {
    Size count = this->maxCount - size;
    assert(count > this->length);

    void **array = new void *[count];

    arrayCopy(array, this->elements, count, sizeof(void *));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}
