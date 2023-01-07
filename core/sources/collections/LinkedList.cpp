/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#include <enhanced/collections/LinkedList.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>
#include <enhanced/Assert.h>
#include <enhanced/exceptions/IndexOutOfBoundsException.h>
#include <enhanced/exceptions/InvalidStateException.h>

using enhanced::exceptions::IndexOutOfBoundsException;
using enhanced::exceptions::InvalidStateException;

namespace enhancedInternal::collections {
    LinkedListImpl::Node*& LinkedListImpl::prevNode(Node*& node) {
        return node = node->prev;
    }

    LinkedListImpl::Node*& LinkedListImpl::nextNode(Node*& node) {
        return node = node->next;
    }

    LinkedListImpl::LinkedListImpl() : first(nullptr), last(nullptr), size(0) {}

    LinkedListImpl::LinkedListImpl(const LinkedListImpl& other, OpCopy opCopy) : first(nullptr), last(nullptr), size(0) {
        Node* indexer = other.first;
        for (sizetype _ = 0; _ < other.size; ++_) {
            addLast0(indexer->value, opCopy);
            nextNode(indexer);
        }
    }

    LinkedListImpl::LinkedListImpl(LinkedListImpl&& other) noexcept : first(other.first), last(other.last), size(other.size) {
        other.first = nullptr;
        other.last = nullptr;
        other.size = INVALID_SIZE;
    }

    $NoIgnoreReturn
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

    $NoIgnoreReturn
    void* LinkedListImpl::getFirst0() const {
        if (size == 0) throw InvalidStateException("The list is empty");

        return first->value;
    }

    $NoIgnoreReturn
    void* LinkedListImpl::getLast0() const {
        if (size == 0) throw InvalidStateException("The list is empty");

        return last->value;
    }

    $NoIgnoreReturn
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
        E_ASSERT(size > 0);

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
        E_ASSERT(size > 0);

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

    LinkedListImpl::LinkedListIteratorImpl::LinkedListIteratorImpl(const LinkedListImpl* linkedList) :
        linkedList(linkedList), indexer((Node*) INVALID_SIZE) {}

    $NoIgnoreReturn
    bool LinkedListImpl::LinkedListIteratorImpl::isBegin0() const {
        return indexer == (Node*) INVALID_SIZE;
    }

    $NoIgnoreReturn
    bool LinkedListImpl::LinkedListIteratorImpl::isEnd0() const {
        return indexer == nullptr;
    }

    $NoIgnoreReturn
    bool LinkedListImpl::LinkedListIteratorImpl::hasNext0() const {
        return (isBegin0() && linkedList->size != 0) || (!isEnd0() && indexer->next != nullptr);
    }

    void LinkedListImpl::LinkedListIteratorImpl::next0() const {
        if (isEnd0()) throw InvalidStateException("The iterator is at the end of the list");
        else if (isBegin0()) indexer = linkedList->first;
        else nextNode(indexer);
    }

    void LinkedListImpl::LinkedListIteratorImpl::prev0() const {
        if (isBegin0()) throw InvalidStateException("The iterator is at the begin of the list");
        else if (isEnd0()) indexer = linkedList->last;
        else nextNode(indexer);
    }

    $NoIgnoreReturn
    void* LinkedListImpl::LinkedListIteratorImpl::get0() const {
        if (isBegin0() || isEnd0()) throw InvalidStateException("Current location of the iterator is not valid");

        return indexer->value;
    }

    void LinkedListImpl::LinkedListIteratorImpl::reset0() const {
        indexer = (Node*) INVALID_SIZE;
    }
}
