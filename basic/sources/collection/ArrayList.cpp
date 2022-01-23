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

#include "EnhancedBasic/collection/ArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/array.h"
#include "EnhancedCore/assert.h"

#include "EnhancedBasic/generic/Generic.h"

using EnhancedBasic::collection::ArrayList0;

ArrayList0::ArrayListIterator0::ArrayListIterator0(const ArrayList0 *const arrayList) :
    arrayList(arrayList), indexer(arrayList->elements), isFirst(true),
    end(arrayList->elements + arrayList->getLength0()) {}

ArrayList0::ArrayListIterator0::~ArrayListIterator0() noexcept = default;

$RetNotIgnored()
bool ArrayList0::ArrayListIterator0::hasNext0() const {
    return this->indexer != this->end;
}

void ArrayList0::ArrayListIterator0::next0() const {
    ++ this->indexer;
}

$RetNotIgnored()
bool ArrayList0::ArrayListIterator0::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->arrayList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference ArrayList0::ArrayListIterator0::get0() const {
    return generic_cast(*this->indexer);
}

void ArrayList0::ArrayListIterator0::reset0() const {
    this->isFirst = true;
    this->indexer = this->arrayList->elements;
}

$RetNotIgnored()
Size ArrayList0::ArrayListIterator0::count0() const {
    return this->arrayList->getLength0();
}

ArrayList0::ArrayList0(const Size maxCount, const GenericsOperator genericsOperator) :
    length(0), elements(new void *[maxCount]), maxCount(maxCount),
    genericsOperator(genericsOperator), iterator(null) {}

ArrayList0::ArrayList0(const ArrayList0 &other) :
    length(other.length), elements(new void *[other.maxCount]), maxCount(other.maxCount),
    genericsOperator(other.genericsOperator), iterator(null) {
    for (int index = 0; index < other.length; ++ index) {
        this->elements[index] = this->genericsOperator.allocate(generic_cast(other.elements[index]));
    }
}

ArrayList0::~ArrayList0() noexcept {
    while (this->length > 0) {
        this->remove0();
    }
    delete[] this->elements;
    delete this->iterator;
}

$RetNotIgnored()
Size ArrayList0::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool ArrayList0::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference ArrayList0::get0(Size index) const {
    return generic_cast(this->elements[index]);
}

$RetNotIgnored()
bool ArrayList0::contain0(GenericReference value) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->genericsOperator.equals(generic_cast(this->elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ArrayList0::add0(GenericReference element) {
    if (this->length == this->maxCount) {
        this->expand0(this->maxCount);
    }

    this->elements[this->length] = this->genericsOperator.allocate(element);
    ++ this->length;
}

void ArrayList0::remove0() {
    this->genericsOperator.destroy(this->elements[-- this->length]);
}

void ArrayList0::expand0(const Size size) {
    Size count = this->maxCount + size;
    void **array = new void *[count];

    arrayCopy(array, this->elements, count, sizeof(void *));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}

void ArrayList0::shrink0(const Size size) {
    Size count = this->maxCount - size;
    assert(count > this->length);

    void **array = new void *[count];

    arrayCopy(array, this->elements, count, sizeof(void *));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}
