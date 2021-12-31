/*
 * Copyright (C) 2021 Liu Baihao. All rights reserved.
 * This product is licensed under Enhanced License.
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

#include "EnhancedContainer/collection/referenced/ReferencedArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/array.h"

using EnhancedContainer::Collection::Referenced::ReferencedArrayList0;

ReferencedArrayList0::ReferencedArrayListIterator0::
ReferencedArrayListIterator0(const ReferencedArrayList0 *referenceArrayList) :
    referenceArrayList(referenceArrayList), indexer(referenceArrayList->elements), isFirst(true),
    end((const void **) referenceArrayList->elements + referenceArrayList->getLength0()) {}

#ifdef CXX_11_OR_MORE

ReferencedArrayList0::ReferencedArrayListIterator0::~ReferencedArrayListIterator0() noexcept = default;

#else

ReferencedArrayList0::ReferencedArrayListIterator0::~ReferencedArrayListIterator0() noexcept {}

#endif // CXX_11_OR_MORE

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
void *ReferencedArrayList0::ReferencedArrayListIterator0::get0() const {
    return *this->indexer;
}

void ReferencedArrayList0::ReferencedArrayListIterator0::reset0() const {
    this->isFirst = true;
    this->indexer = this->referenceArrayList->elements;
}

$RetNotIgnored()
Size ReferencedArrayList0::ReferencedArrayListIterator0::count0() const {
    return this->referenceArrayList->getLength0();
}

ReferencedArrayList0::ReferencedArrayList0(const Size maxCount, const ElementOperator elementOperator) :
    maxCount(maxCount), length(0), elements(new void *[maxCount]),
    elementOperator(elementOperator), iterator(null) {}

ReferencedArrayList0::~ReferencedArrayList0() noexcept {
    delete[] this->elements;
}

Size ReferencedArrayList0::getLength0() const {
    return this->length;
}

bool ReferencedArrayList0::isEmpty0() const {
    return this->length == 0;
}

void *&ReferencedArrayList0::get0(const Size index) const {
    return this->elements[index];
}

bool ReferencedArrayList0::contain0(const void *const element) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->elementOperator.elementEqual(this->elements[index], const_cast<void *&>(element))) {
            return true;
        }
    }

    return false;
}

void ReferencedArrayList0::add0(const void *const element) {
    if (this->length == this->maxCount) {
        this->expand0(this->maxCount >> 1);
    }

    this->elements[this->length] = const_cast<void *>(element);
    ++ this->length;
}

void ReferencedArrayList0::remove0() {
    -- this->length;
}

void ReferencedArrayList0::expand0(const Size size) {
    Size count = this->maxCount + size;
    void **array = new void *[count];

    arrayCopy(array, this->elements, count, sizeof(void *));
    delete[] this->elements;

    this->elements = array;
}

void ReferencedArrayList0::shrink0(const Size size) {
    Size count = this->maxCount - size;
    if (count < this->length) {
        return;
    }

    void **array = new void *[count];

    arrayCopy(array, this->elements, count, sizeof(void *));
    delete[] this->elements;

    this->elements = array;
}
