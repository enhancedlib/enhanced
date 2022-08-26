/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/basic/container/mixed/MixedLinkedList.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"
#include "enhanced/core/assert.h"

#include "enhanced/basic/util/generic.h"

using enhanced::basic::generic_impl::container::mixed::MixedLinkedListImpl;

MixedLinkedListImpl::Node*& MixedLinkedListImpl::nextNode(Node*& node) {
    return node = node->next;
}

MixedLinkedListImpl::Node*& MixedLinkedListImpl::backNode(Node*& node) {
    return node = node->back;
}

MixedLinkedListImpl::MixedLinkedListImpl(const GenericOperator genericOperator) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(genericOperator), iterator(null) {}

MixedLinkedListImpl::MixedLinkedListImpl(const MixedLinkedListImpl& other) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(other.genericOperator), iterator(null) {
    indexer = other.first;
    for (Size count = 0; count < other.length; ++count) {
        if (indexer->dynamic) {
            addLast0(generic_cast(indexer->value));
        } else {
            addLastReference0(generic_cast(indexer->value));
        }
        nextNode(indexer);
    }
}

MixedLinkedListImpl::~MixedLinkedListImpl() noexcept {
    for (Size count = 1; count < length; ++count) {
        backNode(last);

        if (last->next->dynamic) {
            genericOperator.destroy(last->next->value);
        }
        delete last->next;
    }

    if (!isEmpty0() && last->dynamic) {
        genericOperator.destroy(last->value);
    }

    delete last;
    delete iterator;
}

RetCannotIgnored
Size MixedLinkedListImpl::getLength0() const {
    return length;
}

RetCannotIgnored
bool MixedLinkedListImpl::isEmpty0() const {
    return length == 0;
}

RetCannotIgnored
GenericReference MixedLinkedListImpl::getFirst0() const {
    return generic_cast(first->value);
}

RetCannotIgnored
GenericReference MixedLinkedListImpl::getLast0() const {
    return generic_cast(last->value);
}

RetCannotIgnored
GenericReference MixedLinkedListImpl::get0(const Size index) const {
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

RetCannotIgnored
bool MixedLinkedListImpl::contain0(GenericReference value) const {
    indexer = first;
    for (Size count = 0; count < length; ++count) {
        if (genericOperator.equals(generic_cast(indexer->value), value)) {
            return true;
        }
        indexer = indexer->next;
    }

    return false;
}

void MixedLinkedListImpl::addLast0(GenericReference element) {
    if (isEmpty0()) {
        last = new Node();
        last->dynamic = true;
        last->value = genericOperator.allocate(element);
        first = last;
    } else {
        last->next = new Node();
        last->next->dynamic = true;
        last->next->value = genericOperator.allocate(element);
        last->next->back = last;
        nextNode(last);
    }

    ++length;
}

void MixedLinkedListImpl::addLastReference0(GenericReference element) {
    if (isEmpty0()) {
        last = new Node();
        last->value = &element;
        first = last;
    } else {
        last->next = new Node();
        last->next->value = &element;
        last->next->back = last;
        nextNode(last);
    }

    ++length;
}

void MixedLinkedListImpl::removeLast0() {
    assert(!isEmpty0());

    if (length > 1) {
        backNode(last);
        if (last->next->dynamic) {
            genericOperator.destroy(last->next->value);
        }
        delete last->next;
    } else {
        if (last->dynamic) {
            genericOperator.destroy(last->value);
        }
        delete last;
        last = first = null;
    }

    --length;
}

void MixedLinkedListImpl::addFirst0(GenericReference element) {
    if (isEmpty0()) {
        first = new Node();
        first->dynamic = true;
        first->value = genericOperator.allocate(element);
        last = first;
    } else {
        first->back = new Node();
        first->back->dynamic = true;
        first->back->value = genericOperator.allocate(element);
        first->back->next = first;
        backNode(first);
    }

    ++length;
}

void MixedLinkedListImpl::addFirstReference0(GenericReference element) {
    if (isEmpty0()) {
        first = new Node();
        first->value = &element;
        last = first;
    } else {
        first->back = new Node();
        first->back->value = &element;
        first->back->next = first;
        backNode(first);
    }

    ++length;
}

void MixedLinkedListImpl::removeFirst0() {
    assert(!isEmpty0());

    if (length > 1) {
        nextNode(first);
        if (first->back->dynamic) {
            genericOperator.destroy(first->back->value);
        }
        delete first->back;
    } else {
        if (first->dynamic) {
            genericOperator.destroy(first->value);
        }
        delete first;
        first = last = null;
    }

    --length;
}

MixedLinkedListImpl::MixedLinkedListIteratorImpl::
MixedLinkedListIteratorImpl(const MixedLinkedListImpl* mixedLinkedList) :
    mixedLinkedList(mixedLinkedList), isFirst(true) {
    mixedLinkedList->indexer = mixedLinkedList->first;
}

MixedLinkedListImpl::MixedLinkedListIteratorImpl::~MixedLinkedListIteratorImpl() noexcept = default;

RetCannotIgnored
bool MixedLinkedListImpl::MixedLinkedListIteratorImpl::hasNext0() const {
    if (isFirst) {
        isFirst = false;
        return true;
    } else {
        return mixedLinkedList->indexer != null;
    }
}

void MixedLinkedListImpl::MixedLinkedListIteratorImpl::next0() const {
    nextNode(mixedLinkedList->indexer);
}

RetCannotIgnored
bool MixedLinkedListImpl::MixedLinkedListIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !mixedLinkedList->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetCannotIgnored
GenericReference MixedLinkedListImpl::MixedLinkedListIteratorImpl::get0() const {
    return generic_cast(mixedLinkedList->indexer->value);
}

void MixedLinkedListImpl::MixedLinkedListIteratorImpl::reset0() const {
    isFirst = true;
    mixedLinkedList->indexer = mixedLinkedList->first;
}

RetCannotIgnored
Size MixedLinkedListImpl::MixedLinkedListIteratorImpl::count0() const {
    return mixedLinkedList->getLength0();
}
