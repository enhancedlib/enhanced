/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#include "EnhancedBasic/collection/refer/ReferArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/array.h"
#include "EnhancedCore/assert.h"

#include "EnhancedBasic/generic/Generic.h"

using BasicGenericImpl::collection::refer::ReferArrayListImpl;

ReferArrayListImpl::ReferArrayListIteratorImpl::
ReferArrayListIteratorImpl(const ReferArrayListImpl* const referenceArrayList) :
    referenceArrayList(referenceArrayList), indexer(referenceArrayList->elements), isFirst(true),
    end(referenceArrayList->elements + referenceArrayList->getLength0()) {}

ReferArrayListImpl::ReferArrayListIteratorImpl::~ReferArrayListIteratorImpl() noexcept = default;

$RetNotIgnored()
bool ReferArrayListImpl::ReferArrayListIteratorImpl::hasNext0() const {
    return this->indexer != this->end;
}

void ReferArrayListImpl::ReferArrayListIteratorImpl::next0() const {
    ++ this->indexer;
}

$RetNotIgnored()
bool ReferArrayListImpl::ReferArrayListIteratorImpl::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->referenceArrayList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference ReferArrayListImpl::ReferArrayListIteratorImpl::get0() const {
    return generic_cast(*this->indexer);
}

void ReferArrayListImpl::ReferArrayListIteratorImpl::reset0() const {
    this->isFirst = true;
    this->indexer = this->referenceArrayList->elements;
}

$RetNotIgnored()
Size ReferArrayListImpl::ReferArrayListIteratorImpl::count0() const {
    return this->referenceArrayList->getLength0();
}

ReferArrayListImpl::ReferArrayListImpl(const Size maxCount, const GenericOperator genericOperator) :
    length(0), elements(new void* [maxCount]), maxCount(maxCount),
    genericOperator(genericOperator), iterator(null) {}

ReferArrayListImpl::ReferArrayListImpl(const ReferArrayListImpl & other) :
    length(other.length), elements(new void* [other.maxCount]), maxCount(other.maxCount),
    genericOperator(other.genericOperator), iterator(null) {
    assert(other.maxCount >= other.length);
    for (Size index = 0; index < other.length; ++ index) {
        this->elements[index] = other.elements[index];
    }
}

ReferArrayListImpl::~ReferArrayListImpl() noexcept {
    delete[] this->elements;
}

$RetNotIgnored()
Size ReferArrayListImpl::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool ReferArrayListImpl::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference ReferArrayListImpl::get0(const Size index) const {
    return generic_cast(this->elements[index]);
}

$RetNotIgnored()
bool ReferArrayListImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->genericOperator.equals(generic_cast(this->elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ReferArrayListImpl::add0(GenericReference element) {
    if (this->length == this->maxCount) {
        this->expand0(this->maxCount);
    }

    this->elements[this->length] = &element;
    ++ this->length;
}

void ReferArrayListImpl::remove0() {
    -- this->length;
}

void ReferArrayListImpl::expand0(const Size size) {
    Size count = this->maxCount + size;
    void** array = new void* [count];

    arrayCopy(array, this->elements, this->length, sizeof(void*));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}

void ReferArrayListImpl::shrink0(const Size size) {
    Size count = this->maxCount - size;
    assert(count > this->length);

    void** array = new void* [count];

    arrayCopy(array, this->elements, count, sizeof(void*));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}
