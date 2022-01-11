/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
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

#include "EnhancedBasic/collection/mixed/MixedArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/array.h"
#include "EnhancedCore/assert.h"

using EnhancedBasic::Collection::Mixed::MixedArrayList0;

MixedArrayList0::MixedArrayListIterator0::MixedArrayListIterator0(const MixedArrayList0 *mixedArrayList) :
    mixedArrayList(mixedArrayList), indexer(mixedArrayList->elements), isFirst(true),
    end((const Node *) mixedArrayList->elements + mixedArrayList->getLength0()) {}

MixedArrayList0::MixedArrayListIterator0::~MixedArrayListIterator0() noexcept = default;

$RetNotIgnored()
bool MixedArrayList0::MixedArrayListIterator0::hasNext0() const {
    return this->indexer != this->end;
}

void MixedArrayList0::MixedArrayListIterator0::next0() const {
    ++ this->indexer;
}

$RetNotIgnored()
bool MixedArrayList0::MixedArrayListIterator0::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->mixedArrayList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
void *MixedArrayList0::MixedArrayListIterator0::get0() const {
    return (*this->indexer).value;
}

void MixedArrayList0::MixedArrayListIterator0::reset0() const {
    this->isFirst = true;
    this->indexer = this->mixedArrayList->elements;
}

$RetNotIgnored()
Size MixedArrayList0::MixedArrayListIterator0::count0() const {
    return this->mixedArrayList->getLength0();
}

MixedArrayList0::MixedArrayList0(const Size maxCount, const GenericsOperator genericsOperator) :
    maxCount(maxCount), length(0), elements(new Node[maxCount]),
    genericsOperator(genericsOperator), iterator(null) {}

MixedArrayList0::~MixedArrayList0() noexcept {
    while (this->length > 0) {
        this->remove0();
    }
    delete[] this->elements;
    delete this->iterator;
}

Size MixedArrayList0::getLength0() const {
    return this->length;
}

bool MixedArrayList0::isEmpty0() const {
    return this->length == 0;
}

void *MixedArrayList0::get0(const Size index) const {
    return this->elements[index].value;
}

bool MixedArrayList0::contain0(const void *const value) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->genericsOperator.genericsEquals(this->elements[index].value, const_cast<void *&>(value))) {
            return true;
        }
    }

    return false;
}

void MixedArrayList0::add0(const void *const element) {
    if (this->length == this->maxCount) {
        if (this->maxCount == 1) {
            this->expand0(1);
        } else {
            this->expand0(this->maxCount >> 1);
        }
    }

    this->elements[this->length] =
        {this->genericsOperator.genericsNew(const_cast<void *&>(element)), true};
    ++ this->length;
}

void MixedArrayList0::addReferenced0(const void *const element) {
    if (this->length == this->maxCount) {
        if (this->maxCount == 1) {
            this->expand0(1);
        } else {
            this->expand0(this->maxCount >> 1);
        }
    }

    this->elements[this->length] = {const_cast<void *>(element), false};
    ++ this->length;
}

void MixedArrayList0::remove0() {
    if (this->elements[-- this->length].requiresRelease) {
        this->genericsOperator.genericsDelete(this->elements[this->length].value);
    }
}

void MixedArrayList0::expand0(const Size size) {
    Size count = this->maxCount + size;
    Node *array = new Node[count];

    arrayCopy(array, this->elements, count, sizeof(Node));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}

void MixedArrayList0::shrink0(const Size size) {
    Size count = this->maxCount - size;
    assert(count > this->length);

    Node *array = new Node[count];

    arrayCopy(array, this->elements, count, sizeof(Node));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}
