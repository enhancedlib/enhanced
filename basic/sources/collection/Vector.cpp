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

#include "Enhanced/basic/collection/Vector.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"
#include "Enhanced/core/assert.h"

#include "Enhanced/basic/util/Generic.h"

using EnhancedGenericImpl::basic::collection::VectorImpl;

VectorImpl::VectorIteratorImpl::VectorIteratorImpl(const VectorImpl* const vector) :
    vector(vector), indexer(vector->elements), isFirst(true),
    end(vector->genericOperator.index(vector->elements, vector->getLength0())) {}

VectorImpl::VectorIteratorImpl::~VectorIteratorImpl() noexcept = default;

RetNotIgnored()
bool VectorImpl::VectorIteratorImpl::hasNext0() const {
    return indexer != end;
}

void VectorImpl::VectorIteratorImpl::next0() const {
    indexer = vector->genericOperator.index(indexer, 1);
}

RetNotIgnored()
bool VectorImpl::VectorIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !vector->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetNotIgnored()
GenericReference VectorImpl::VectorIteratorImpl::get0() const {
    return generic_cast(indexer);
}

void VectorImpl::VectorIteratorImpl::reset0() const {
    isFirst = true;
    indexer = vector->elements;
}

RetNotIgnored()
Size VectorImpl::VectorIteratorImpl::count0() const {
    return vector->getLength0();
}

VectorImpl::VectorImpl(const Size maxCount, const GenericOperator genericOperator) :
    maxCount(maxCount), length(0), elements(genericOperator.allocateArray(maxCount)),
    genericOperator(genericOperator), iterator(null) {}

VectorImpl::VectorImpl(const VectorImpl& other) :
    maxCount(other.maxCount), length(other.length), elements(other.genericOperator.allocateArray(other.maxCount)),
    genericOperator(other.genericOperator), iterator(null) {
    genericOperator.copyArray(elements, other.elements, other.length);
}

VectorImpl::~VectorImpl() noexcept {
    operator delete(elements);
    delete iterator;
}

RetNotIgnored()
Size VectorImpl::getLength0() const {
    return length;
}

RetNotIgnored()
bool VectorImpl::isEmpty0() const {
    return length == 0;
}

RetNotIgnored()
GenericReference VectorImpl::get0(const Size index) const {
    return genericOperator.getElement(elements, index);
}

RetNotIgnored()
bool VectorImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < length; ++index) {
        if (genericOperator.equals(get0(index), value)) {
            return true;
        }
    }

    return false;
}

void VectorImpl::add0(GenericReference element) {
    if (length == maxCount) {
        expand0(maxCount);
    }

    genericOperator.setElement(elements, length, element);
    ++length;
}

void VectorImpl::remove0() {
    --length;
}

void VectorImpl::expand0(const Size size) {
    Size count = maxCount + size;
    void* array = genericOperator.allocateArray(count);

    genericOperator.moveArray(array, elements, length);
    operator delete(elements);

    elements = array;
    maxCount = count;
}

void VectorImpl::shrink0(const Size size) {
    Size count = maxCount - size;
    assert(count > length);

    void* array = genericOperator.allocateArray(count);

    genericOperator.moveArray(array, elements, length);
    operator delete(elements);

    elements = array;
    maxCount = count;
}
