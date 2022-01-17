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

#include "EnhancedBasic/generic/Generic.h"

using EnhancedBasic::collection::Vector0;

Vector0::VectorIterator0::VectorIterator0(const Vector0 *const vector) :
    vector(vector), indexer(vector->elements), isFirst(true),
    end(vector->genericsOperator.index(vector->elements, vector->getLength0())) {}

Vector0::VectorIterator0::~VectorIterator0() noexcept = default;

$RetNotIgnored()
bool Vector0::VectorIterator0::hasNext0() const {
    return this->indexer != this->end;
}

void Vector0::VectorIterator0::next0() const {
    this->indexer = this->vector->genericsOperator.index(this->indexer, 1);
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
GenericReference Vector0::VectorIterator0::get0() const {
    return generic_cast(this->indexer);
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

Vector0::Vector0(const Vector0 &copy) :
    maxCount(copy.maxCount), length(copy.length), elements(copy.genericsOperator.allocateArray(copy.maxCount)),
    genericsOperator(copy.genericsOperator), iterator(null) {
    for (Size index = 0; index < copy.length; ++ index) {
        this->genericsOperator.setElement(this->elements, index,
            this->genericsOperator.getElement(copy.elements, index));
    }
}

Vector0::~Vector0() noexcept {
    this->genericsOperator.destroyArray(this->elements, this->length);
    delete this->iterator;
}

$RetNotIgnored()
Size Vector0::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool Vector0::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference Vector0::get0(const Size index) const {
    return this->genericsOperator.getElement(this->elements, index);
}

$RetNotIgnored()
bool Vector0::contain0(GenericReference value) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->genericsOperator.equals(this->get0(index), value)) {
            return true;
        }
    }

    return false;
}

void Vector0::add0(GenericReference element) {
    if (this->length == this->maxCount) {
        this->expand0(this->maxCount);
    }

    this->genericsOperator.setElement(this->elements, this->length, element);
    ++ this->length;
}

void Vector0::remove0() {
    -- this->length;
}

void Vector0::expand0(const Size size) {
    Size count = this->maxCount + size;
    GenericPointer array = this->genericsOperator.allocateArray(count);

    this->genericsOperator.copyArray(array, this->elements, this->length);
    this->genericsOperator.destroyArray(this->elements, this->length);

    this->elements = array;
    this->maxCount = count;
}

void Vector0::shrink0(const Size size) {
    Size count = this->maxCount - size;
    assert(count > this->length);

    GenericPointer array = this->genericsOperator.allocateArray(count);

    this->genericsOperator.copyArray(array, this->elements, this->length);
    this->genericsOperator.destroyArray(this->elements, this->length);

    this->elements = array;
    this->maxCount = count;
}
