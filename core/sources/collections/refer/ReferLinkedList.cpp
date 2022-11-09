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
#include <enhanced/core/annotations.h>
#include <enhanced/core/types.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/generic.h>
#include <enhanced/core/exception/IndexOutOfBoundsException.h>
#include <enhanced/core/exception/UnsupportedOperationException.h>

using enhanced_internal::core::collections::refer::ReferLinkedListImpl;
using enhanced::core::exception::IndexOutOfBoundsException;
using enhanced::core::exception::UnsupportedOperationException;

ReferLinkedListImpl::Node*& ReferLinkedListImpl::prevNode(Node*& node) {
    return node = node->prev;
}

ReferLinkedListImpl::Node*& ReferLinkedListImpl::nextNode(Node*& node) {
    return node = node->next;
}

ReferLinkedListImpl::ReferLinkedListImpl(const GenericOperator genericOperator) :
    first(null), last(null), size(0), genericOperator(genericOperator) {}

ReferLinkedListImpl::ReferLinkedListImpl(const ReferLinkedListImpl& other) :
    first(null), last(null), size(0), genericOperator(other.genericOperator) {
    Node* indexer = other.first;
    for (sizetype _ = 0; _ < other.size; ++_) {
        addLast0(GET_GENERIC_VALUE(indexer->value));
        nextNode(indexer);
    }
}

ReferLinkedListImpl::~ReferLinkedListImpl() noexcept {
    for (sizetype _ = 1; _ < size; ++_) {
        prevNode(last);
        delete last->next;
    }

    delete last;
}

NoIgnoreRet
sizetype ReferLinkedListImpl::getSize0() const {
    return size;
}

NoIgnoreRet
bool ReferLinkedListImpl::isEmpty0() const {
    return size == 0;
}

NoIgnoreRet
Generic& ReferLinkedListImpl::getLast0() const {
    return GET_GENERIC_VALUE(last->value);
}

NoIgnoreRet
Generic& ReferLinkedListImpl::getFirst0() const {
    return GET_GENERIC_VALUE(first->value);
}

NoIgnoreRet
Generic& ReferLinkedListImpl::get0(const sizetype index) const {
    if (index >= size) throw IndexOutOfBoundsException("Index out of bounds"); // TODO

    Node* indexer;
    if (index < (size >> 1)) {
        indexer = first;
        for (sizetype _ = 0; _ < index; ++_) {
            nextNode(indexer);
        }
    } else {
        indexer = last;
        for (sizetype _ = size - 1; _ > index; --_) {
            prevNode(indexer);
        }
    }

    return GET_GENERIC_VALUE(indexer->value);
}

NoIgnoreRet
bool ReferLinkedListImpl::contain0(Generic& value) const {
    Node* indexer = first;
    for (sizetype _ = 0; _ < size; ++_) {
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

ReferLinkedListImpl::ReferLinkedListIteratorImpl::ReferLinkedListIteratorImpl(const ReferLinkedListImpl* referLinkedList) :
    referLinkedList(referLinkedList), indexer(referLinkedList->first) {}

ReferLinkedListImpl::ReferLinkedListIteratorImpl::~ReferLinkedListIteratorImpl() noexcept = default;

NoIgnoreRet
bool ReferLinkedListImpl::ReferLinkedListIteratorImpl::hasNext0() const {
    return indexer != null;
}

void ReferLinkedListImpl::ReferLinkedListIteratorImpl::next0() const {
    nextNode(indexer);
}

NoIgnoreRet
Generic& ReferLinkedListImpl::ReferLinkedListIteratorImpl::get0() const {
    return GET_GENERIC_VALUE(indexer->value);
}

void ReferLinkedListImpl::ReferLinkedListIteratorImpl::reset0() const {
    indexer = referLinkedList->first;
}

NoIgnoreRet
sizetype ReferLinkedListImpl::ReferLinkedListIteratorImpl::count0() const {
    return referLinkedList->getSize0();
}
