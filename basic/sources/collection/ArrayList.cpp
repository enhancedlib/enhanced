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
#include "EnhancedCore/memory.h"

#include "EnhancedBasic/generic/Generic.h"

using BasicGenericImpl::collection::ArrayListImpl;

ArrayListImpl::ArrayListIteratorImpl::ArrayListIteratorImpl(const ArrayListImpl *const arrayList) :
    arrayList(arrayList), indexer(arrayList->elements), isFirst(true),
    end(arrayList->elements + arrayList->getLength0()) {}

ArrayListImpl::ArrayListIteratorImpl::~ArrayListIteratorImpl() noexcept = default;

$RetNotIgnored()
bool ArrayListImpl::ArrayListIteratorImpl::hasNext0() const {
    return this->indexer != this->end;
}

void ArrayListImpl::ArrayListIteratorImpl::next0() const {
    ++ this->indexer;
}

$RetNotIgnored()
bool ArrayListImpl::ArrayListIteratorImpl::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->arrayList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference ArrayListImpl::ArrayListIteratorImpl::get0() const {
    return generic_cast(*this->indexer);
}

void ArrayListImpl::ArrayListIteratorImpl::reset0() const {
    this->isFirst = true;
    this->indexer = this->arrayList->elements;
}

$RetNotIgnored()
Size ArrayListImpl::ArrayListIteratorImpl::count0() const {
    return this->arrayList->getLength0();
}

ArrayListImpl::ArrayListImpl(const Size maxCount, const GenericOperator genericOperator) :
    length(0), elements(new void *[maxCount]), maxCount(maxCount),
    genericOperator(genericOperator), iterator(null) {}

ArrayListImpl::ArrayListImpl(const ArrayListImpl &other) :
    length(other.length), elements(new void *[other.maxCount]), maxCount(other.maxCount),
    genericOperator(other.genericOperator), iterator(null) {
    assert(other.maxCount >= other.length);
    for (Size index = 0; index < other.length; ++ index) {
        this->elements[index] = this->genericOperator.allocate(generic_cast(other.elements[index]));
    }
}

ArrayListImpl::~ArrayListImpl() noexcept {
    while (this->length > 0) {
        this->remove0();
    }
    delete[] this->elements;
    delete this->iterator;
}

$RetNotIgnored()
Size ArrayListImpl::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool ArrayListImpl::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference ArrayListImpl::get0(Size index) const {
    return generic_cast(this->elements[index]);
}

$RetNotIgnored()
bool ArrayListImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->genericOperator.equals(generic_cast(this->elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ArrayListImpl::add0(GenericReference element) {
    if (this->length == this->maxCount) {
        this->expand0(this->maxCount);
    }

    this->elements[this->length] = this->genericOperator.allocate(element);
    ++ this->length;
}

void ArrayListImpl::remove0() {
    this->genericOperator.destroy(this->elements[-- this->length]);
}

void ArrayListImpl::expand0(const Size size) {
    Size count = this->maxCount + size;
    void **array = new void *[count];

    arrayCopy(array, this->elements, this->length, sizeof(void *));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}

void ArrayListImpl::shrink0(const Size size) {
    Size count = this->maxCount - size;
    assert(count > this->length);

    void **array = new void *[count];

    arrayCopy(array, this->elements, count, sizeof(void *));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}
