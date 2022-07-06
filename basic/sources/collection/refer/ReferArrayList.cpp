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

#include "Enhanced/basic/collection/refer/ReferArrayList.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"
#include "Enhanced/core/array.h"
#include "Enhanced/core/assert.h"

#include "Enhanced/basic/util/Generic.h"

using EnhancedGenericImpl::basic::collection::refer::ReferArrayListImpl;

ReferArrayListImpl::ReferArrayListIteratorImpl::
ReferArrayListIteratorImpl(const ReferArrayListImpl* const referenceArrayList) :
    referenceArrayList(referenceArrayList), indexer(referenceArrayList->elements), isFirst(true),
    end(referenceArrayList->elements + referenceArrayList->getLength0()) {}

ReferArrayListImpl::ReferArrayListIteratorImpl::~ReferArrayListIteratorImpl() noexcept = default;

RetNotIgnored()
bool ReferArrayListImpl::ReferArrayListIteratorImpl::hasNext0() const {
    return indexer != end;
}

void ReferArrayListImpl::ReferArrayListIteratorImpl::next0() const {
    ++ indexer;
}

RetNotIgnored()
bool ReferArrayListImpl::ReferArrayListIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !referenceArrayList->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetNotIgnored()
GenericReference ReferArrayListImpl::ReferArrayListIteratorImpl::get0() const {
    return generic_cast(*indexer);
}

void ReferArrayListImpl::ReferArrayListIteratorImpl::reset0() const {
    isFirst = true;
    indexer = referenceArrayList->elements;
}

RetNotIgnored()
Size ReferArrayListImpl::ReferArrayListIteratorImpl::count0() const {
    return referenceArrayList->getLength0();
}

ReferArrayListImpl::ReferArrayListImpl(const Size maxCount, const GenericOperator genericOperator) :
    length(0), elements(new void* [maxCount]), maxCount(maxCount),
    genericOperator(genericOperator), iterator(null) {}

ReferArrayListImpl::ReferArrayListImpl(const ReferArrayListImpl& other) :
    length(other.length), elements(new void* [other.maxCount]), maxCount(other.maxCount),
    genericOperator(other.genericOperator), iterator(null) {
    assert(other.maxCount >= other.length);
    for (Size index = 0; index < other.length; ++ index) {
        elements[index] = other.elements[index];
    }
}

ReferArrayListImpl::~ReferArrayListImpl() noexcept {
    delete[] elements;
}

RetNotIgnored()
Size ReferArrayListImpl::getLength0() const {
    return length;
}

RetNotIgnored()
bool ReferArrayListImpl::isEmpty0() const {
    return length == 0;
}

RetNotIgnored()
GenericReference ReferArrayListImpl::get0(const Size index) const {
    return generic_cast(elements[index]);
}

RetNotIgnored()
bool ReferArrayListImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < length; ++ index) {
        if (genericOperator.equals(generic_cast(elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ReferArrayListImpl::add0(GenericReference element) {
    if (length == maxCount) {
        expand0(maxCount);
    }

    elements[length] = &element;
    ++ length;
}

void ReferArrayListImpl::remove0() {
    --length;
}

void ReferArrayListImpl::expand0(const Size size) {
    Size count = maxCount + size;
    void** array = new void* [count];

    arrayCopy(array, elements, length, sizeof(void*));
    delete[] elements;

    elements = array;
    maxCount = count;
}

void ReferArrayListImpl::shrink0(const Size size) {
    Size count = maxCount - size;
    assert(count > length);

    void** array = new void* [count];

    arrayCopy(array, elements, count, sizeof(void*));
    delete[] elements;

    elements = array;
    maxCount = count;
}
