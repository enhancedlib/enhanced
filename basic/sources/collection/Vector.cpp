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

#include "EnhancedBasic/collection/Vector.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/assert.h"

using EnhancedBasic::collection::Vector0;

Vector0::VectorIterator0::VectorIterator0(const Vector0 *const vector) :
    vector(vector), indexer(vector->elements), isFirst(true),
    end(vector->genericsOperator.indexArray(vector->elements, vector->getLength0())) {}

Vector0::VectorIterator0::~VectorIterator0() noexcept = default;

$RetNotIgnored()
bool Vector0::VectorIterator0::hasNext0() const {
    return this->indexer != this->end;
}

void Vector0::VectorIterator0::next0() const {
    this->indexer = this->vector->genericsOperator.indexArray(this->indexer, 1);
}

$RetNotIgnored()
bool Vector0::VectorIterator0::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->vector->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
void *Vector0::VectorIterator0::get0() const {
    return this->indexer;
}

void Vector0::VectorIterator0::reset0() const {
    this->isFirst = true;
    this->indexer = this->vector->elements;
}

$RetNotIgnored()
Size Vector0::VectorIterator0::count0() const {
    return this->vector->getLength0();
}

Vector0::Vector0(const Size maxCount, const GenericsOperator genericsOperator) :
    maxCount(maxCount), length(0), elements(genericsOperator.allocateArray(maxCount)),
    genericsOperator(genericsOperator), iterator(null) {}

Vector0::~Vector0() noexcept {
    this->genericsOperator.destroyArray(this->elements);
    delete this->iterator;
}

Size Vector0::getLength0() const {
    return this->length;
}

bool Vector0::isEmpty0() const {
    return this->length == 0;
}

void *Vector0::get0(const Size index) const {
    return this->genericsOperator.indexArray(this->elements, index);
}

bool Vector0::contain0(const void *const value) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->genericsOperator.equals(this->get0(index), const_cast<void *&>(value))) {
            return true;
        }
    }

    return false;
}

void Vector0::add0(const void *const element) {
    if (this->length == this->maxCount) {
        if (this->maxCount == 1) {
            this->expand0(1);
        } else {
            this->expand0(this->maxCount >> 1);
        }
    }

    this->genericsOperator.setElement(this->elements, this->length, const_cast<void *&>(element));
    ++ this->length;
}

void Vector0::remove0() {
    -- this->length;
}

void Vector0::expand0(const Size size) {
    Size count = this->maxCount + size;
    void *array = this->genericsOperator.allocateArray(count);

    this->genericsOperator.copyArray(array, this->elements, this->length);
    this->genericsOperator.destroyArray(this->elements);

    this->elements = array;
    this->maxCount = count;
}

void Vector0::shrink0(const Size size) {
    Size count = this->maxCount - size;
    assert(count > this->length);
    void *array = this->genericsOperator.allocateArray(count);

    this->genericsOperator.copyArray(array, this->elements, this->length);
    this->genericsOperator.destroyArray(this->elements);

    this->elements = array;
    this->maxCount = count;
}
