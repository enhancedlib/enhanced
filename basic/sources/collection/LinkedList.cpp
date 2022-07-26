/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/basic/collection/LinkedList.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"
#include "enhanced/core/assert.h"

#include "enhanced/basic/util/generic.h"

using enhanced::basic::generic_impl::collection::LinkedListImpl;

LinkedListImpl::LinkedListIteratorImpl::LinkedListIteratorImpl(const LinkedListImpl* linkedList) :
    linkedList(linkedList), isFirst(true) {
    linkedList->indexer = linkedList->first;
}

LinkedListImpl::LinkedListIteratorImpl::~LinkedListIteratorImpl() noexcept = default;

RetCannotIgnored()
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

RetCannotIgnored()
bool LinkedListImpl::LinkedListIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !linkedList->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetCannotIgnored()
GenericReference LinkedListImpl::LinkedListIteratorImpl::get0() const {
    return generic_cast(linkedList->indexer->value);
}

void LinkedListImpl::LinkedListIteratorImpl::reset0() const {
    isFirst = true;
    linkedList->indexer = linkedList->first;
}

RetCannotIgnored()
Size LinkedListImpl::LinkedListIteratorImpl::count0() const {
    return linkedList->getLength0();
}

LinkedListImpl::Node*& LinkedListImpl::nextNode(Node*& node) {
    return node = node->next;
}

LinkedListImpl::Node*& LinkedListImpl::backNode(Node*& node) {
    return node = node->back;
}

LinkedListImpl::LinkedListImpl(const GenericOperator genericOperator) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(genericOperator), iterator(null) {}

LinkedListImpl::LinkedListImpl(const LinkedListImpl& other) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(other.genericOperator), iterator(null) {
    indexer = other.first;
    for (Size count = 0; count < other.length; ++count) {
        addLast0(generic_cast(indexer->value));
        nextNode(indexer);
    }
}

LinkedListImpl::~LinkedListImpl() noexcept {
    for (Size count = 1; count < length; ++count) {
        backNode(last);

        genericOperator.destroy(last->next->value);
        delete last->next;
    }

    if (!isEmpty0()) {
        genericOperator.destroy(last->value);
    }

    delete last;
    delete iterator;
}

RetCannotIgnored()
Size LinkedListImpl::getLength0() const {
    return length;
}

RetCannotIgnored()
bool LinkedListImpl::isEmpty0() const {
    return length == 0;
}

RetCannotIgnored()
GenericReference LinkedListImpl::getFirst0() const {
    return generic_cast(first->value);
}

RetCannotIgnored()
GenericReference LinkedListImpl::getLast0() const {
    return generic_cast(last->value);
}

RetCannotIgnored()
GenericReference LinkedListImpl::get0(const Size index) const {
    if (index < length >> 1) {
        indexer = first;
        for (Size count = 0; count < index; ++count) {
            nextNode(indexer);
        }
    } else {
        indexer = last;
        for (Size count = length - 1; count > index; --count) {
            backNode(indexer);
        }
    }

    return generic_cast(indexer->value);
}

RetCannotIgnored()
bool LinkedListImpl::contain0(GenericReference value) const {
    indexer = first;
    for (Size count = 0; count < length; ++count) {
        if (genericOperator.equals(indexer->value, const_cast<void*&>(value))) {
            return true;
        }
        nextNode(indexer);
    }

    return false;
}

void LinkedListImpl::addLast0(GenericReference element) {
    if (isEmpty0()) {
        last = new Node();
        last->value = genericOperator.allocate(element);
        first = last;
    } else {
        last->next = new Node();
        last->next->value = genericOperator.allocate(element);
        last->next->back = last;
        nextNode(last);
    }

    ++length;
}

void LinkedListImpl::removeLast0() {
    assert(!isEmpty0());

    if (length > 1) {
        backNode(last);
        genericOperator.destroy(last->next->value);
        delete last->next;
    } else {
        genericOperator.destroy(last->value);
        delete last;
        last = first = null;
    }

    --length;
}

void LinkedListImpl::addFirst0(GenericReference element) {
    if (isEmpty0()) {
        first = new Node();
        first->value = genericOperator.allocate(element);
        last = first;
    } else {
        first->back = new Node();
        first->back->value = genericOperator.allocate(element);
        first->back->next = first;
        backNode(first);
    }

    ++length;
}

void LinkedListImpl::removeFirst0() {
    assert(!isEmpty0());

    if (length > 1) {
        nextNode(first);
        genericOperator.destroy(first->back->value);
        delete first->back;
    } else {
        genericOperator.destroy(first->value);
        delete first;
        first = last = null;
    }

    --length;
}
