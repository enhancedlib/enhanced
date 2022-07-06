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

#include "Enhanced/basic/collection/mixed/MixedArrayList.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"
#include "Enhanced/core/array.h"
#include "Enhanced/core/assert.h"

#include "Enhanced/basic/util/Generic.h"

using EnhancedGenericImpl::basic::collection::mixed::MixedArrayListImpl;

MixedArrayListImpl::MixedArrayListIteratorImpl::MixedArrayListIteratorImpl(const MixedArrayListImpl* mixedArrayList) :
    mixedArrayList(mixedArrayList), indexer(mixedArrayList->elements), isFirst(true),
    end((const Node*) mixedArrayList->elements + mixedArrayList->getLength0()) {}

MixedArrayListImpl::MixedArrayListIteratorImpl::~MixedArrayListIteratorImpl() noexcept = default;

RetNotIgnored()
bool MixedArrayListImpl::MixedArrayListIteratorImpl::hasNext0() const {
    return indexer != end;
}

void MixedArrayListImpl::MixedArrayListIteratorImpl::next0() const {
    ++ indexer;
}

RetNotIgnored()
bool MixedArrayListImpl::MixedArrayListIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !mixedArrayList->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetNotIgnored()
GenericReference MixedArrayListImpl::MixedArrayListIteratorImpl::get0() const {
    return generic_cast((*indexer).value);
}

void MixedArrayListImpl::MixedArrayListIteratorImpl::reset0() const {
    isFirst = true;
    indexer = mixedArrayList->elements;
}

RetNotIgnored()
Size MixedArrayListImpl::MixedArrayListIteratorImpl::count0() const {
    return mixedArrayList->getLength0();
}

MixedArrayListImpl::MixedArrayListImpl(const Size maxCount, const GenericOperator genericOperator) :
    length(0), elements(new Node[maxCount]), maxCount(maxCount),
    genericOperator(genericOperator), iterator(null) {}

MixedArrayListImpl::MixedArrayListImpl(const MixedArrayListImpl& other) :
    length(other.length), elements(new Node[other.maxCount]), maxCount(other.maxCount),
    genericOperator(other.genericOperator), iterator(null) {
    assert(other.maxCount >= other.length);
    for (Size index = 0; index < other.length; ++ index) {
        if (other.elements[index].dynamic) {
            elements[index].value = genericOperator.allocate(generic_cast(other.elements[index].value));
        } else {
            elements[index] = other.elements[index];
        }
    }
}

MixedArrayListImpl::~MixedArrayListImpl() noexcept {
    while (length > 0) {
        remove0();
    }

    delete[] elements;
    delete iterator;
}

RetNotIgnored()
Size MixedArrayListImpl::getLength0() const {
    return length;
}

RetNotIgnored()
bool MixedArrayListImpl::isEmpty0() const {
    return length == 0;
}

RetNotIgnored()
GenericReference MixedArrayListImpl::get0(const Size index) const {
    return generic_cast(elements[index].value);
}

RetNotIgnored()
bool MixedArrayListImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < length; ++ index) {
        if (genericOperator.equals(generic_cast(elements[index].value), value)) {
            return true;
        }
    }

    return false;
}

void MixedArrayListImpl::add0(GenericReference element) {
    if (length == maxCount) {
        expand0(maxCount);
    }

    elements[length] = {genericOperator.allocate(element), true};
    ++ length;
}

void MixedArrayListImpl::addReference0(GenericReference element) {
    if (length == maxCount) {
        expand0(maxCount);
    }

    elements[length] = {&element, false};
    ++ length;
}

void MixedArrayListImpl::remove0() {
    if (elements[--length].dynamic) {
        genericOperator.destroy(elements[length].value);
    }
}

void MixedArrayListImpl::expand0(const Size size) {
    Size count = maxCount + size;
    Node* array = new Node[count];

    arrayCopy(array, elements, length, sizeof(Node));
    delete[] elements;

    elements = array;
    maxCount = count;
}

void MixedArrayListImpl::shrink0(const Size size) {
    Size count = maxCount - size;
    assert(count > length);

    Node* array = new Node[count];

    arrayCopy(array, elements, count, sizeof(Node));
    delete[] elements;

    elements = array;
    maxCount = count;
}
