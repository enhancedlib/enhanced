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

#include "Enhanced/basic/collection/ArrayList.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"
#include "Enhanced/core/array.h"
#include "Enhanced/core/assert.h"
#include "Enhanced/core/memory.h"

#include "Enhanced/basic/util/Generic.h"

using EnhancedGenericImpl::basic::collection::ArrayListImpl;

ArrayListImpl::ArrayListIteratorImpl::ArrayListIteratorImpl(const ArrayListImpl* const arrayList) :
    arrayList(arrayList), indexer(arrayList->elements), isFirst(true), end(arrayList->elements + arrayList->getLength0()) {}

ArrayListImpl::ArrayListIteratorImpl::~ArrayListIteratorImpl() noexcept = default;

RetNotIgnored()
bool ArrayListImpl::ArrayListIteratorImpl::hasNext0() const {
    return indexer != end;
}

void ArrayListImpl::ArrayListIteratorImpl::next0() const {
    ++ indexer;
}

RetNotIgnored()
bool ArrayListImpl::ArrayListIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !arrayList->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetNotIgnored()
GenericReference ArrayListImpl::ArrayListIteratorImpl::get0() const {
    return generic_cast(*indexer);
}

void ArrayListImpl::ArrayListIteratorImpl::reset0() const {
    isFirst = true;
    indexer = arrayList->elements;
}

RetNotIgnored()
Size ArrayListImpl::ArrayListIteratorImpl::count0() const {
    return arrayList->getLength0();
}

ArrayListImpl::ArrayListImpl(const Size maxCount, const GenericOperator genericOperator) :
    length(0), elements(new void*[maxCount]), maxCount(maxCount), genericOperator(genericOperator), iterator(null) {}

ArrayListImpl::ArrayListImpl(const ArrayListImpl& other) :
    length(other.length), elements(new void*[other.maxCount]), maxCount(other.maxCount), genericOperator(other.genericOperator), iterator(null) {
    assert(other.maxCount >= other.length);
    for (Size index = 0; index < other.length; ++ index) {
        elements[index] = genericOperator.allocate(generic_cast(other.elements[index]));
    }
}

ArrayListImpl::~ArrayListImpl() noexcept {
    while (length > 0) {
        remove0();
    }
    delete[] elements;
    delete iterator;
}

RetNotIgnored()
Size ArrayListImpl::getLength0() const {
    return length;
}

RetNotIgnored()
bool ArrayListImpl::isEmpty0() const {
    return length == 0;
}

RetNotIgnored()
GenericReference ArrayListImpl::get0(Size index) const {
    return generic_cast(elements[index]);
}

RetNotIgnored()
bool ArrayListImpl::contain0(GenericReference value) const {
    for (Size index = 0; index < length; ++ index) {
        if (genericOperator.equals(generic_cast(elements[index]), value)) {
            return true;
        }
    }

    return false;
}

void ArrayListImpl::add0(GenericReference element) {
    if (length == maxCount) {
        expand0(maxCount);
    }

    elements[length] = genericOperator.allocate(element);
    ++ length;
}

void ArrayListImpl::remove0() {
    genericOperator.destroy(elements[--length]);
}

void ArrayListImpl::expand0(const Size size) {
    Size count = maxCount + size;
    void** array = new void*[count];

    arrayCopy(array, elements, length, sizeof(void*));
    delete[] elements;

    elements = array;
    maxCount = count;
}

void ArrayListImpl::shrink0(const Size size) {
    Size count = maxCount - size;
    assert(count > length);

    void** array = new void*[count];

    arrayCopy(array, elements, count, sizeof(void*));
    delete[] elements;

    elements = array;
    maxCount = count;
}
