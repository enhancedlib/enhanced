/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <enhanced/collections/LinkedList.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>
#include <enhanced/Assert.h>
#include <enhanced/exceptions/IndexOutOfBoundsException.h>
#include <enhanced/exceptions/OperationException.h>

using enhanced::exceptions::IndexOutOfBoundsException;
using enhanced::exceptions::OperationException;

namespace enhancedInternal::collections {
    LinkedListImpl::LinkedListImpl() : first(nullptr), last(nullptr), size(0) {}

    LinkedListImpl::LinkedListImpl(const LinkedListImpl& other, OpCopy opCopy) :
        first(nullptr), last(nullptr), size(0) {
        Node* indexer = other.first;
        for (sizetype _ = 0; _ < other.size; ++_) {
            addLast0(indexer->value, opCopy);
            nextNode(indexer);
        }
    }

    LinkedListImpl::LinkedListImpl(LinkedListImpl&& other) noexcept :
        first(other.first), last(other.last), size(other.size) {
        other.first = nullptr;
        other.last = nullptr;
        other.size = INVALID_SIZE;
    }

    [[RetNotIgnored]]
    sizetype LinkedListImpl::indexOf0(void* value, OpEqual opEqual) const {
        Node* indexer = first;
        for (sizetype index = 0; index < size; ++index) {
            if (opEqual(indexer->value, value)) {
                return index;
            }
            nextNode(indexer);
        }

        return INVALID_SIZE;
    }

    [[RetNotIgnored]]
    void* LinkedListImpl::getFirst0() const {
        if (size == 0) throw OperationException("The list is empty");

        return first->value;
    }

    [[RetNotIgnored]]
    void* LinkedListImpl::getLast0() const {
        if (size == 0) throw OperationException("The list is empty");

        return last->value;
    }

    [[RetNotIgnored]]
    void* LinkedListImpl::get0(sizetype index) const {
        if (index >= size) throw IndexOutOfBoundsException(index, size);

        Node* indexer;
        if (index < (size >> 1)) {
            indexer = first;
            while (index-- > 0) {
                nextNode(indexer);
            }
        } else {
            indexer = last;
            while (++index < size) {
                prevNode(indexer);
            }
        }

        return indexer->value;
    }

    void LinkedListImpl::addFirst0(void* element, OpCopy opCopy) {
        if (size == 0) {
            first = new Node();
            first->value = opCopy(element);
            last = first;
        } else {
            first->prev = new Node();
            first->prev->value = opCopy(element);
            first->prev->next = first;
            prevNode(first);
        }

        ++size;
    }

    void LinkedListImpl::addFirst1(void* element, OpMove opMove) {
        if (size == 0) {
            first = new Node();
            first->value = opMove(element);
            last = first;
        } else {
            first->prev = new Node();
            first->prev->value = opMove(element);
            first->prev->next = first;
            prevNode(first);
        }

        ++size;
    }

    void LinkedListImpl::addLast0(void* element, OpCopy opCopy) {
        if (size == 0) {
            last = new Node();
            last->value = opCopy(element);
            first = last;
        } else {
            last->next = new Node();
            last->next->value = opCopy(element);
            last->next->prev = last;
            nextNode(last);
        }

        ++size;
    }

    void LinkedListImpl::addLast1(void* element, OpMove opMove) {
        if (size == 0) {
            last = new Node();
            last->value = opMove(element);
            first = last;
        } else {
            last->next = new Node();
            last->next->value = opMove(element);
            last->next->prev = last;
            nextNode(last);
        }

        ++size;
    }

    void LinkedListImpl::removeFirst0(OpDestroy opDestroy) {
        if (size == 0) throw OperationException("The list is empty");

        if (size > 1) {
            nextNode(first);
            opDestroy(first->prev->value);
            delete first->prev;
        } else {
            opDestroy(first->value);
            delete first;
            first = last = nullptr;
        }

        --size;
    }

    void LinkedListImpl::removeLast0(OpDestroy opDestroy) {
        if (size == 0) throw OperationException("The list is empty");

        if (size > 1) {
            prevNode(last);
            opDestroy(last->next->value);
            delete last->next;
        } else {
            opDestroy(last->value);
            delete last;
            last = first = nullptr;
        }

        --size;
    }

    void LinkedListImpl::clear0(OpDestroy opDestroy) {
        if (size == INVALID_SIZE) return;

        while (size-- > 1) {
            prevNode(last);
            opDestroy(last->next->value);
            delete last->next;
        }

        if (last != nullptr) {
            opDestroy(last->value);
            delete last;
            last = first = nullptr;
        }
    }

    LinkedListImpl::LinkedListIteratorImpl::LinkedListIteratorImpl(const LinkedListImpl* linkedList, Node* init) :
        linkedList(linkedList), indexer(init) {}

    [[RetNotIgnored]]
    void* LinkedListImpl::LinkedListIteratorImpl::get0() const {
        if (isBegin0() || isEnd0()) {
            throw OperationException("The iterator has not element at the current location (begin or end)");
        }
        return indexer->value;
    }

    [[RetNotIgnored]]
    bool LinkedListImpl::LinkedListIteratorImpl::isBegin0() const {
        return indexer == (Node*) INVALID_SIZE;
    }

    [[RetNotIgnored]]
    bool LinkedListImpl::LinkedListIteratorImpl::isEnd0() const {
        return indexer == nullptr;
    }

    [[RetNotIgnored]]
    bool LinkedListImpl::LinkedListIteratorImpl::hasNext0() const {
        return (isBegin0() && linkedList->size != 0) || (!isEnd0() && indexer->next != nullptr);
    }

    [[RetNotIgnored]]
    bool LinkedListImpl::LinkedListIteratorImpl::hasPrev0() const {
        return (isEnd0() && linkedList->size != 0) || (!isBegin0() && indexer->prev != nullptr);
    }

    void LinkedListImpl::LinkedListIteratorImpl::next0() const {
        if (isEnd0()) throw OperationException("The iterator is at the end of the list");
        else if (isBegin0()) indexer = linkedList->first;
        else nextNode(indexer);
    }

    void LinkedListImpl::LinkedListIteratorImpl::next0(sizetype count) const {
        for (sizetype step = 0; step < count; ++step) {
            if (isEnd0()) throw OperationException("Out of the list");
            else if (isBegin0()) indexer = linkedList->first;
            else nextNode(indexer);
        }
    }

    void LinkedListImpl::LinkedListIteratorImpl::prev0() const {
        if (isBegin0()) throw OperationException("The iterator is at the begin of the list");
        else if (isEnd0()) indexer = linkedList->last;
        else prevNode(indexer);
    }

    void LinkedListImpl::LinkedListIteratorImpl::prev0(sizetype count) const {
        for (sizetype step = 0; step < count; ++step) {
            if (isEnd0()) throw OperationException("Out of the list");
            else if (isEnd0()) indexer = linkedList->last;
            else prevNode(indexer);
        }
    }

    void LinkedListImpl::LinkedListIteratorImpl::setBegin0() const {
        indexer = (Node*) INVALID_SIZE;
    }

    void LinkedListImpl::LinkedListIteratorImpl::setEnd0() const {
        indexer = nullptr;
    }
}
