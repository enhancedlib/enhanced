/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <enhanced/collections/LinkedList.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>
#include <enhanced/Assert.h>
#include <enhanced/exceptions/IndexOutOfBoundsException.h>
#include <enhanced/exceptions/OperationException.h>

using enhanced::sizetype;
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
        other.size = E_SIZE_TYPE_MAX;
    }

    E_ANNOTATE(RetNotIgnored)
    sizetype LinkedListImpl::indexOf0(void* value, OpEqual opEqual) const {
        Node* indexer = first;
        for (sizetype index = 0; index < size; ++index) {
            if (opEqual(indexer->value, value)) {
                return index;
            }
            nextNode(indexer);
        }

        return E_SIZE_TYPE_MAX;
    }

    E_ANNOTATE(RetNotIgnored)
    void* LinkedListImpl::getFirst0() const {
        if (size == 0) throw OperationException("The list is empty");

        return first->value;
    }

    E_ANNOTATE(RetNotIgnored)
    void* LinkedListImpl::getLast0() const {
        if (size == 0) throw OperationException("The list is empty");

        return last->value;
    }

    E_ANNOTATE(RetNotIgnored)
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
        if (size == E_SIZE_TYPE_MAX) return;

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

    E_ANNOTATE(RetNotIgnored)
    void* LinkedListImpl::LinkedListIteratorImpl::get0() const {
        if (isBegin0() || isEnd0()) {
            throw OperationException("The iterator has not element at the current location (begin or end)");
        }
        return indexer->value;
    }

    E_ANNOTATE(RetNotIgnored)
    bool LinkedListImpl::LinkedListIteratorImpl::isBegin0() const {
        return indexer == (Node*) E_SIZE_TYPE_MAX;
    }

    E_ANNOTATE(RetNotIgnored)
    bool LinkedListImpl::LinkedListIteratorImpl::isEnd0() const {
        return indexer == nullptr;
    }

    E_ANNOTATE(RetNotIgnored)
    bool LinkedListImpl::LinkedListIteratorImpl::hasNext0() const {
        return (isBegin0() && linkedList->size != 0) || (!isEnd0() && indexer->next != nullptr);
    }

    E_ANNOTATE(RetNotIgnored)
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
        indexer = (Node*) E_SIZE_TYPE_MAX;
    }

    void LinkedListImpl::LinkedListIteratorImpl::setEnd0() const {
        indexer = nullptr;
    }
}
