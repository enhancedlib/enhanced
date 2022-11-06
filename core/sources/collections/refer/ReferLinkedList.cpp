/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <enhanced/core/collections/refer/ReferLinkedList.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/generic.h>
#include <enhanced/core/exception/UnsupportedOperationException.h>

using enhanced_internal::core::collections::refer::ReferLinkedListImpl;
using enhanced::core::exception::UnsupportedOperationException;

ReferLinkedListImpl::Node*& ReferLinkedListImpl::prevNode(Node*& node) {
    return node = node->prev;
}

ReferLinkedListImpl::Node*& ReferLinkedListImpl::nextNode(Node*& node) {
    return node = node->next;
}

ReferLinkedListImpl::ReferLinkedListImpl(const GenericOperator genericOperator) :
    first(null), last(null), indexer(null), size(0), genericOperator(genericOperator), iterator(null) {}

ReferLinkedListImpl::ReferLinkedListImpl(const ReferLinkedListImpl& other) :
    first(null), last(null), indexer(null), size(0), genericOperator(other.genericOperator), iterator(null) {
    indexer = other.first;
    for (Size count = 0; count < other.size; ++count) {
        addLast0(GET_GENERIC_VALUE(indexer->value));
        nextNode(indexer);
    }
}

ReferLinkedListImpl::~ReferLinkedListImpl() noexcept {
    for (Size count = 1; count < size; ++count) {
        prevNode(last);
        delete last->next;
    }

    delete last;
    delete iterator;
}

RetCannotIgnored
Size ReferLinkedListImpl::getSize0() const {
    return size;
}

RetCannotIgnored
bool ReferLinkedListImpl::isEmpty0() const {
    return size == 0;
}

RetCannotIgnored
Generic& ReferLinkedListImpl::getLast0() const {
    return GET_GENERIC_VALUE(last->value);
}

RetCannotIgnored
Generic& ReferLinkedListImpl::getFirst0() const {
    return GET_GENERIC_VALUE(first->value);
}

RetCannotIgnored
Generic& ReferLinkedListImpl::get0(const Size index) const {
    if (index < (size >> 1)) {
        indexer = first;
        for (Size count = 0; count < index; ++count) {
            nextNode(indexer);
        }
    } else {
        indexer = last;
        for (Size count = size - 1; count > index; --count) {
            prevNode(indexer);
        }
    }

    return GET_GENERIC_VALUE(indexer->value);
}

RetCannotIgnored
bool ReferLinkedListImpl::contain0(Generic& value) const {
    indexer = first;
    for (Size count = 0; count < size; ++count) {
        if (genericOperator.equals(GET_GENERIC_VALUE(indexer->value), value)) {
            return true;
        }
        indexer = indexer->next;
    }

    return false;
}

void ReferLinkedListImpl::addLast0(Generic& element) {
    if (isEmpty0()) {
        last = new Node();
        last->value = &element;
        first = last;
    } else {
        last->next = new Node();
        last->next->value = &element;
        last->next->prev = last;
        nextNode(last);
    }

    ++size;
}

void ReferLinkedListImpl::removeLast0() {
    if (isEmpty0()) throw UnsupportedOperationException("The list is empty");

    if (size > 1) {
        prevNode(last);
        delete last->next;
    } else {
        delete last;
        last = first = null;
    }

    --size;
}

void ReferLinkedListImpl::addFirst0(Generic& element) {
    if (isEmpty0()) {
        first = new Node();
        first->value = &element;
        last = first;
    } else {
        first->prev = new Node();
        first->prev->value = &element;
        first->prev->next = first;
        prevNode(first);
    }

    ++size;
}

void ReferLinkedListImpl::removeFirst0() {
    if (isEmpty0()) throw UnsupportedOperationException("The list is empty");

    if (size > 1) {
        nextNode(first);
        delete first->prev;
    } else {
        delete first;
        first = last = null;
    }

    --size;
}

ReferLinkedListImpl::ReferLinkedListIteratorImpl::
ReferLinkedListIteratorImpl(const ReferLinkedListImpl* referLinkedList) :
    referLinkedList(referLinkedList), isFirst(true) {
    referLinkedList->indexer = referLinkedList->first;
}

ReferLinkedListImpl::ReferLinkedListIteratorImpl::~ReferLinkedListIteratorImpl() noexcept = default;

RetCannotIgnored
bool ReferLinkedListImpl::ReferLinkedListIteratorImpl::hasNext0() const {
    if (isFirst) {
        isFirst = false;
        return true;
    } else {
        return referLinkedList->indexer != null;
    }
}

void ReferLinkedListImpl::ReferLinkedListIteratorImpl::next0() const {
    nextNode(referLinkedList->indexer);
}

RetCannotIgnored
bool ReferLinkedListImpl::ReferLinkedListIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !referLinkedList->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetCannotIgnored
Generic& ReferLinkedListImpl::ReferLinkedListIteratorImpl::get0() const {
    return GET_GENERIC_VALUE(referLinkedList->indexer->value);
}

void ReferLinkedListImpl::ReferLinkedListIteratorImpl::reset0() const {
    isFirst = true;
    referLinkedList->indexer = referLinkedList->first;
}

RetCannotIgnored
Size ReferLinkedListImpl::ReferLinkedListIteratorImpl::count0() const {
    return referLinkedList->getSize0();
}
