/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#include "Enhanced/basic/collection/refer/ReferLinkedList.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"
#include "Enhanced/core/assert.h"

#include "Enhanced/basic/util/Generic.h"

using EnhancedGenericImpl::basic::collection::refer::ReferLinkedListImpl;

ReferLinkedListImpl::ReferLinkedListIteratorImpl::
ReferLinkedListIteratorImpl(const ReferLinkedListImpl* const referLinkedList) :
    referLinkedList(referLinkedList), isFirst(true) {
    referLinkedList->indexer = referLinkedList->first;
}

ReferLinkedListImpl::ReferLinkedListIteratorImpl::~ReferLinkedListIteratorImpl() noexcept = default;

RetNotIgnored()
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

RetNotIgnored()
bool ReferLinkedListImpl::ReferLinkedListIteratorImpl::each0() const {
    if (isFirst) {
        isFirst = false;
        return !referLinkedList->isEmpty0();
    }

    next0();
    return hasNext0();
}

RetNotIgnored()
GenericReference ReferLinkedListImpl::ReferLinkedListIteratorImpl::get0() const {
    return generic_cast(referLinkedList->indexer->value);
}

void ReferLinkedListImpl::ReferLinkedListIteratorImpl::reset0() const {
    isFirst = true;
    referLinkedList->indexer = referLinkedList->first;
}

RetNotIgnored()
Size ReferLinkedListImpl::ReferLinkedListIteratorImpl::count0() const {
    return referLinkedList->getLength0();
}

ReferLinkedListImpl::Node*& ReferLinkedListImpl::nextNode(Node*& node) {
    return node = node->next;
}

ReferLinkedListImpl::Node*& ReferLinkedListImpl::backNode(Node*& node) {
    return node = node->back;
}

ReferLinkedListImpl::ReferLinkedListImpl(const GenericOperator genericOperator) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(genericOperator), iterator(null) {}

ReferLinkedListImpl::ReferLinkedListImpl(const ReferLinkedListImpl& other) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(other.genericOperator), iterator(null) {
    indexer = other.first;
    for (Size count = 0; count < other.length; ++ count) {
        addLast0(generic_cast(indexer->value));
        nextNode(indexer);
    }
}

ReferLinkedListImpl::~ReferLinkedListImpl() noexcept {
    for (Size count = 1; count < length; ++ count) {
        backNode(last);
        delete last->next;
    }

    delete last;
    delete iterator;
}

RetNotIgnored()
Size ReferLinkedListImpl::getLength0() const {
    return length;
}

RetNotIgnored()
bool ReferLinkedListImpl::isEmpty0() const {
    return length == 0;
}

RetNotIgnored()
GenericReference ReferLinkedListImpl::getLast0() const {
    return generic_cast(last->value);
}

RetNotIgnored()
GenericReference ReferLinkedListImpl::getFirst0() const {
    return generic_cast(first->value);
}

RetNotIgnored()
GenericReference ReferLinkedListImpl::get0(const Size index) const {
    if (index < length >> 1) {
        indexer = first;
        for (Size count = 0; count < index; ++ count) {
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

RetNotIgnored()
bool ReferLinkedListImpl::contain0(GenericReference value) const {
    indexer = first;
    for (Size count = 0; count < length; ++ count) {
        if (genericOperator.equals(generic_cast(indexer->value), value)) {
            return true;
        }
        indexer = indexer->next;
    }

    return false;
}

void ReferLinkedListImpl::addLast0(GenericReference element) {
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

    ++ length;
}

void ReferLinkedListImpl::removeLast0() {
    assert(!isEmpty0());

    if (length > 1) {
        backNode(last);
        delete last->next;
    } else {
        delete last;
        last = first = null;
    }

    --length;
}

void ReferLinkedListImpl::addFirst0(GenericReference element) {
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

    ++ length;
}

void ReferLinkedListImpl::removeFirst0() {
    assert(!isEmpty0());

    if (length > 1) {
        nextNode(first);
        delete first->back;
    } else {
        delete first;
        first = last = null;
    }

    --length;
}
