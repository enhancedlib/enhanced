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

using EnhancedBasic::collection::referenced::ReferencedArrayList0;

ReferencedArrayList0::ReferencedArrayListIterator0::
ReferencedArrayListIterator0(const ReferencedArrayList0 *const referenceArrayList) :
    referenceArrayList(referenceArrayList), indexer(referenceArrayList->elements), isFirst(true),
    end(referenceArrayList->elements + referenceArrayList->getLength0()) {}

ReferencedArrayList0::ReferencedArrayListIterator0::~ReferencedArrayListIterator0() noexcept = default;

$RetNotIgnored()
bool ReferencedArrayList0::ReferencedArrayListIterator0::hasNext0() const {
    return this->indexer != this->end;
}

void ReferencedArrayList0::ReferencedArrayListIterator0::next0() const {
    ++ this->indexer;
}

$RetNotIgnored()
bool ReferencedArrayList0::ReferencedArrayListIterator0::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->referenceArrayList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference ReferencedArrayList0::ReferencedArrayListIterator0::get0() const {
    return generic_cast(*this->indexer);
}

void ReferencedArrayList0::ReferencedArrayListIterator0::reset0() const {
    this->isFirst = true;
    this->indexer = this->referenceArrayList->elements;
}

$RetNotIgnored()
Size ReferencedArrayList0::ReferencedArrayListIterator0::count0() const {
    return this->referenceArrayList->getLength0();
}

ReferencedArrayList0::ReferencedArrayList0(const Size maxCount, const GenericsOperator genericsOperator) :
    length(0), elements(new GenericPointer[maxCount]), maxCount(maxCount),
    genericsOperator(genericsOperator), iterator(null) {}

ReferencedArrayList0::ReferencedArrayList0(const ReferencedArrayList0 &copy) :
    length(copy.length), elements(new GenericPointer[copy.maxCount]), maxCount(copy.maxCount),
    genericsOperator(copy.genericsOperator), iterator(null) {
    for (Size index = 0; index < copy.length; ++ index) {
        this->elements[index] = copy.elements[index];
    }
}

ReferencedArrayList0::~ReferencedArrayList0() noexcept {
    delete[] this->elements;
}

$RetNotIgnored()
Size ReferencedArrayList0::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool ReferencedArrayList0::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference ReferencedArrayList0::get0(const Size index) const {
    return generic_cast(this->elements[index]);
}

$RetNotIgnored()
bool ReferencedArrayList0::contain0(GenericReference value) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->genericsOperator.equals(generic_cast(this->elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ReferencedArrayList0::add0(GenericReference element) {
    if (this->length == this->maxCount) {
        this->expand0(this->maxCount);
    }

    this->elements[this->length] = &element;
    ++ this->length;
}

void ReferencedArrayList0::remove0() {
    -- this->length;
}

void ReferencedArrayList0::expand0(const Size size) {
    Size count = this->maxCount + size;
    GenericPointer *array = new GenericPointer[count];

    arrayCopy(array, this->elements, count, sizeof(GenericPointer));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}

void ReferencedArrayList0::shrink0(const Size size) {
    Size count = this->maxCount - size;
    assert(count > this->length);

    GenericPointer *array = new GenericPointer[count];

    arrayCopy(array, this->elements, count, sizeof(GenericPointer));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}
