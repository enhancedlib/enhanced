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
#include <enhanced/core/exception/IndexOutOfBoundsException.h>
#include <enhanced/core/exception/UnsupportedOperationException.h>

using enhanced_internal::core::collections::LinkedListImpl;
using enhanced::core::exception::IndexOutOfBoundsException;
using enhanced::core::exception::UnsupportedOperationException;

func LinkedListImpl::prevNode(Node*& node) -> LinkedListImpl::Node*& {
    return node = node->prev;
}

func LinkedListImpl::nextNode(Node*& node) -> LinkedListImpl::Node*& {
    return node = node->next;
}

LinkedListImpl::LinkedListImpl(const GenericOperator genericOperator) : first(null), last(null), size(0), genericOperator(genericOperator) {}

LinkedListImpl::LinkedListImpl(const LinkedListImpl& other) : first(null), last(null), size(0), genericOperator(other.genericOperator) {
    Node* indexer = other.first;
    for (sizetype _ = 0; _ < other.size; ++_) {
        addLast0(indexer->value);
        nextNode(indexer);
    }
}

LinkedListImpl::~LinkedListImpl() noexcept {
    for (sizetype _ = 1; _ < size; ++_) {
        prevNode(last);

        genericOperator.destroy(last->next->value);
        delete last->next;
    }

    if (size != 0) genericOperator.destroy(last->value);

    delete last;
}

$(NoIgnoreReturn)
func LinkedListImpl::getFirst0() const -> void* {
    if (size == 0) throw UnsupportedOperationException("The list is empty");

    return first->value;
}

$(NoIgnoreReturn)
func LinkedListImpl::getLast0() const -> void* {
    if (size == 0) throw UnsupportedOperationException("The list is empty");

    return last->value;
}

$(NoIgnoreReturn)
func LinkedListImpl::get0(const sizetype index) const -> void* {
    if (index >= size) throw IndexOutOfBoundsException(index, size);

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

    return indexer->value;
}

$(NoIgnoreReturn)
func LinkedListImpl::contain0(void* value) const -> bool {
    Node* indexer = first;
    for (sizetype _ = 0; _ < size; ++_) {
        if (genericOperator.equals(indexer->value, value)) {
            return true;
        }
        nextNode(indexer);
    }

    return false;
}

func LinkedListImpl::addLast0(void* element) -> void {
    if (size == 0) {
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

func LinkedListImpl::removeLast0() -> void {
    if (size == 0) throw UnsupportedOperationException("The list is empty");

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

func LinkedListImpl::addFirst0(void* element) -> void {
    if (size == 0) {
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

func LinkedListImpl::removeFirst0() -> void {
    if (size == 0) throw UnsupportedOperationException("The list is empty");

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
    linkedList(linkedList), indexer(linkedList->first) {}

LinkedListImpl::LinkedListIteratorImpl::~LinkedListIteratorImpl() noexcept = default;

$(NoIgnoreReturn)
func LinkedListImpl::LinkedListIteratorImpl::hasNext0() const -> bool {
    return indexer != null;
}

func LinkedListImpl::LinkedListIteratorImpl::next0() const -> void {
    nextNode(indexer);
}

$(NoIgnoreReturn)
func LinkedListImpl::LinkedListIteratorImpl::get0() const -> void* {
    return indexer->value;
}

func LinkedListImpl::LinkedListIteratorImpl::reset0() const -> void {
    indexer = linkedList->first;
}
