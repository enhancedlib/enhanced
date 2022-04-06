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

#include "EnhancedBasic/collection/mixed/MixedArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/array.h"
#include "EnhancedCore/assert.h"

#include "EnhancedBasic/generic/Generic.h"

using BasicGenericImpl::collection::mixed::MixedArrayListImpl;

MixedArrayListImpl::MixedArrayListIteratorImpl::MixedArrayListIteratorImpl(const MixedArrayListImpl *mixedArrayList) :
    mixedArrayList(mixedArrayList), indexer(mixedArrayList->elements), isFirst(true),
    end((const Node *) mixedArrayList->elements + mixedArrayList->getLength0()) {}

MixedArrayListImpl::MixedArrayListIteratorImpl::~MixedArrayListIteratorImpl() noexcept = default;

$RetNotIgnored()
bool MixedArrayListImpl::MixedArrayListIteratorImpl::hasNext0() const {
    return this->indexer != this->end;
}

void MixedArrayListImpl::MixedArrayListIteratorImpl::next0() const {
    ++ this->indexer;
}

$RetNotIgnored()
bool MixedArrayListImpl::MixedArrayListIteratorImpl::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->mixedArrayList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference MixedArrayListImpl::MixedArrayListIteratorImpl::get0() const {
    return generic_cast((*this->indexer).value);
}

void MixedArrayListImpl::MixedArrayListIteratorImpl::reset0() const {
    this->isFirst = true;
    this->indexer = this->mixedArrayList->elements;
}

$RetNotIgnored()
Size MixedArrayListImpl::MixedArrayListIteratorImpl::count0() const {
    return this->mixedArrayList->getLength0();
}

MixedArrayListImpl::MixedArrayListImpl(const Size maxCount, const GenericOperator genericOperator) :
    length(0), elements(new Node[maxCount]), maxCount(maxCount),
    genericOperator(genericOperator), iterator(null) {}

MixedArrayListImpl::MixedArrayListImpl(const MixedArrayListImpl &other) :
    length(other.length), elements(new Node[other.maxCount]), maxCount(other.maxCount),
    genericOperator(other.genericOperator), iterator(null) {
    assert(other.maxCount >= other.length);
    for (Size index = 0; index < other.length; ++ index) {
        if (other.elements[index].dynamic) {
            this->elements[index].value = this->genericOperator.allocate(generic_cast(other.elements[index].value));
        } else {
            this->elements[index] = other.elements[index];
        }
    }
}

MixedArrayListImpl::~MixedArrayListImpl() noexcept {
    while (this->length > 0) {
        this->remove0();
    }

    delete[] this->elements;
    delete this->iterator;
}

$RetNotIgnored()
Size MixedArrayListImpl::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool MixedArrayListImpl::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference MixedArrayListImpl::get0(const Size index) const {
    return generic_cast(this->elements[index].value);
}

$RetNotIgnored()
bool MixedArrayListImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->genericOperator.equals(generic_cast(this->elements[index].value), value)) {
            return true;
        }
    }

    return false;
}

void MixedArrayListImpl::add0(GenericReference element) {
    if (this->length == this->maxCount) {
        this->expand0(this->maxCount);
    }

    this->elements[this->length] = {this->genericOperator.allocate(element), true};
    ++ this->length;
}

void MixedArrayListImpl::addReferenced0(GenericReference element) {
    if (this->length == this->maxCount) {
        this->expand0(this->maxCount);
    }

    this->elements[this->length] = {&element, false};
    ++ this->length;
}

void MixedArrayListImpl::remove0() {
    if (this->elements[-- this->length].dynamic) {
        this->genericOperator.destroy(this->elements[this->length].value);
    }
}

void MixedArrayListImpl::expand0(const Size size) {
    Size count = this->maxCount + size;
    Node *array = new Node[count];

    arrayCopy(array, this->elements, this->length, sizeof(Node));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}

void MixedArrayListImpl::shrink0(const Size size) {
    Size count = this->maxCount - size;
    assert(count > this->length);

    Node *array = new Node[count];

    arrayCopy(array, this->elements, count, sizeof(Node));
    delete[] this->elements;

    this->elements = array;
    this->maxCount = count;
}
