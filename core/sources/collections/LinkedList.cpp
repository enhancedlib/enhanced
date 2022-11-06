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

#include <enhanced/core/collections/LinkedList.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/generic.h>
#include <enhanced/core/exception/UnsupportedOperationException.h>

using enhanced_internal::core::collections::LinkedListImpl;
using enhanced::core::exception::UnsupportedOperationException;

LinkedListImpl::Node*& LinkedListImpl::prevNode(Node*& node) {
    return node = node->prev;
}

LinkedListImpl::Node*& LinkedListImpl::nextNode(Node*& node) {
    return node = node->next;
}

LinkedListImpl::LinkedListImpl(const GenericOperator genericOperator) :
    first(null), last(null), indexer(null), size(0),
    genericOperator(genericOperator), iterator(null) {}

LinkedListImpl::LinkedListImpl(const LinkedListImpl& other) :
    first(null), last(null), indexer(null), size(0),
    genericOperator(other.genericOperator), iterator(null) {
    indexer = other.first;
    for (Size count = 0; count < other.size; ++count) {
        addLast0(GET_GENERIC_VALUE(indexer->value));
        nextNode(indexer);
    }
}

LinkedListImpl::~LinkedListImpl() noexcept {
    for (Size count = 1; count < size; ++count) {
        prevNode(last);

        genericOperator.destroy(last->next->value);
        delete last->next;
    }

    if (!isEmpty0()) genericOperator.destroy(last->value);

    delete last;
    delete iterator;
}

RetCannotIgnored
Size LinkedListImpl::getSize0() const {
    return size;
}

RetCannotIgnored
bool LinkedListImpl::isEmpty0() const {
    return size == 0;
}

RetCannotIgnored
Generic& LinkedListImpl::getFirst0() const {
    return GET_GENERIC_VALUE(first->value);
}

RetCannotIgnored
Generic& LinkedListImpl::getLast0() const {
    return GET_GENERIC_VALUE(last->value);
}

RetCannotIgnored
Generic& LinkedListImpl::get0(const Size index) const {
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
bool LinkedListImpl::contain0(Generic& value) const {
    indexer = first;
    for (Size count = 0; count < size; ++count) {
        if (genericOperator.equals(indexer->value, const_cast<void*&>(value))) {
            return true;
        }
        nextNode(indexer);
    }

    return false;
}

void LinkedListImpl::addLast0(Generic& element) {
    if (isEmpty0()) {
        last = new Node();
        last->value = genericOperator.allocate(element);
        first = last;
    } else {
        last->next = new Node();
        last->next->value = genericOperator.allocate(element);
        last->next->prev = last;
        nextNode(last);
    }

    ++size;
}

void LinkedListImpl::removeLast0() {
    if (isEmpty0()) throw UnsupportedOperationException("The list is empty");

    if (size > 1) {
        prevNode(last);
        genericOperator.destroy(last->next->value);
        delete last->next;
    } else {
        genericOperator.destroy(last->value);
        delete last;
        last = first = null;
    }

    --size;
}

void LinkedListImpl::addFirst0(Generic& element) {
    if (isEmpty0()) {
        first = new Node();
        first->value = genericOperator.allocate(element);
        last = first;
    } else {
        first->prev = new Node();
        first->prev->value = genericOperator.allocate(element);
        first->prev->next = first;
        prevNode(first);
    }

    ++size;
}

void LinkedListImpl::removeFirst0() {
    if (isEmpty0()) throw UnsupportedOperationException("The list is empty");

    if (size > 1) {
        nextNode(first);
        genericOperator.destroy(first->prev->value);
        delete first->prev;
    } else {
        genericOperator.destroy(first->value);
        delete first;
        first = last = null;
    }

    --size;
}

LinkedListImpl::LinkedListIteratorImpl::LinkedListIteratorImpl(const LinkedListImpl* linkedList) :
    linkedList(linkedList), isFirst(true) {
    linkedList->indexer = linkedList->first;
}

LinkedListImpl::LinkedListIteratorImpl::~LinkedListIteratorImpl() noexcept = default;

RetCannotIgnored
bool LinkedListImpl::LinkedListIteratorImpl::hasNext0() const {
    if (isFirst) {
        isFirst = false;
        return true;
    } else {
        return linkedList->indexer != null;
    }
}

void LinkedListImpl::LinkedListIteratorImpl::next0() const {
    nextNode(linkedList->indexer);
}

RetCannotIgnored
bool LinkedListImpl::LinkedListIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !linkedList->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetCannotIgnored
Generic& LinkedListImpl::LinkedListIteratorImpl::get0() const {
    return GET_GENERIC_VALUE(linkedList->indexer->value);
}

void LinkedListImpl::LinkedListIteratorImpl::reset0() const {
    isFirst = true;
    linkedList->indexer = linkedList->first;
}

RetCannotIgnored
Size LinkedListImpl::LinkedListIteratorImpl::count0() const {
    return linkedList->getSize0();
}
