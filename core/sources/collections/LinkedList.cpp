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
#include <enhanced/core/exceptions/IndexOutOfBoundsException.h>
#include <enhanced/core/exceptions/UnsupportedOperationException.h>

using enhanced::core::exceptions::IndexOutOfBoundsException;
using enhanced::core::exceptions::UnsupportedOperationException;

namespace enhancedInternal::core::collections {
    func LinkedListImpl::prevNode(Node*& node) -> LinkedListImpl::Node*& {
        return node = node->prev;
    }

    func LinkedListImpl::nextNode(Node*& node) -> LinkedListImpl::Node*& {
        return node = node->next;
    }

    LinkedListImpl::LinkedListImpl() : first(null), last(null), size(0) {}

    LinkedListImpl::LinkedListImpl(const LinkedListImpl& other, OpCopy opCopy) : first(null), last(null), size(0) {
        Node* indexer = other.first;
        for (sizetype _ = 0; _ < other.size; ++_) {
            addLast0(indexer->value, opCopy);
            nextNode(indexer);
        }
    }

    LinkedListImpl::LinkedListImpl(LinkedListImpl&& other) noexcept : first(other.first), last(other.last), size(other.size) {
        other.first = null;
        other.last = null;
        other.size = INVALID_SIZE;
    }

    func LinkedListImpl::destruct0(OpDestroy opDestroy) noexcept -> void {
        clear0(opDestroy);
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
    func LinkedListImpl::get0(sizetype index) const -> void* {
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

    $(NoIgnoreReturn)
    func LinkedListImpl::indexOf0(void* value, OpEqual opEqual) const -> sizetype {
        Node* indexer = first;
        for (sizetype index = 0; index < size; ++index) {
            if (opEqual(indexer->value, value)) {
                return index;
            }
            nextNode(indexer);
        }

        return INVALID_SIZE;
    }

    func LinkedListImpl::addLast0(void* element, OpCopy opCopy) -> void {
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

    func LinkedListImpl::addLastMoved0(void* element, OpMove opMove) -> void {
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

    func LinkedListImpl::removeLast0(OpDestroy opDestroy) -> void {
        if (size == 0) throw UnsupportedOperationException("The list is empty");

        if (size > 1) {
            prevNode(last);
            opDestroy(last->next->value);
            delete last->next;
        } else {
            opDestroy(last->value);
            delete last;
            last = first = null;
        }

        --size;
    }

    func LinkedListImpl::addFirst0(void* element, OpCopy opCopy) -> void {
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

    func LinkedListImpl::addFirstMoved0(void* element, OpMove opMove) -> void {
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

    func LinkedListImpl::removeFirst0(OpDestroy opDestroy) -> void {
        if (size == 0) throw UnsupportedOperationException("The list is empty");

        if (size > 1) {
            nextNode(first);
            opDestroy(first->prev->value);
            delete first->prev;
        } else {
            opDestroy(first->value);
            delete first;
            first = last = null;
        }

        --size;
    }

    func LinkedListImpl::clear0(OpDestroy opDestroy) -> void {
        while (size > 1) {
            prevNode(last);
            opDestroy(last->next->value);
            delete last->next;
            --size;
        }

        opDestroy(last->value);
        delete last;
        last = first = null;
    }

    LinkedListImpl::LinkedListIteratorImpl::LinkedListIteratorImpl(const LinkedListImpl* linkedList) :
        linkedList(linkedList), indexer(linkedList->first) {}

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
}
