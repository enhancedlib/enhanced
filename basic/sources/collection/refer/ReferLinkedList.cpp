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

#include "EnhancedBasic/collection/refer/ReferLinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/assert.h"

#include "EnhancedBasic/generic/Generic.h"

using BasicGenericImpl::collection::refer::ReferLinkedListImpl;

ReferLinkedListImpl::ReferLinkedListIteratorImpl::
ReferLinkedListIteratorImpl(const ReferLinkedListImpl* const referLinkedList) :
    referLinkedList(referLinkedList), isFirst(true) {
    this->referLinkedList->indexer = this->referLinkedList->first;
}

ReferLinkedListImpl::ReferLinkedListIteratorImpl::~ReferLinkedListIteratorImpl() noexcept = default;

$RetNotIgnored()
bool ReferLinkedListImpl::ReferLinkedListIteratorImpl::hasNext0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return true;
    } else {
        return this->referLinkedList->indexer != null;
    }
}

void ReferLinkedListImpl::ReferLinkedListIteratorImpl::next0() const {
    ReferLinkedListImpl::nextNode(this->referLinkedList->indexer);
}

$RetNotIgnored()
bool ReferLinkedListImpl::ReferLinkedListIteratorImpl::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->referLinkedList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference ReferLinkedListImpl::ReferLinkedListIteratorImpl::get0() const {
    return generic_cast(this->referLinkedList->indexer->value);
}

void ReferLinkedListImpl::ReferLinkedListIteratorImpl::reset0() const {
    this->isFirst = true;
    this->referLinkedList->indexer = this->referLinkedList->first;
}

$RetNotIgnored()
Size ReferLinkedListImpl::ReferLinkedListIteratorImpl::count0() const {
    return this->referLinkedList->getLength0();
}

ReferLinkedListImpl::Node*& ReferLinkedListImpl::nextNode(Node * &node) {
    return node = node->next;
}

ReferLinkedListImpl::Node*& ReferLinkedListImpl::backNode(Node * &node) {
    return node = node->back;
}

ReferLinkedListImpl::ReferLinkedListImpl(const GenericOperator genericOperator) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(genericOperator), iterator(null) {}

ReferLinkedListImpl::ReferLinkedListImpl(const ReferLinkedListImpl & other) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(other.genericOperator), iterator(null) {
    this->indexer = other.first;
    for (Size count = 0; count < other.length; ++ count) {
        this->addLast0(generic_cast(this->indexer->value));
        ReferLinkedListImpl::nextNode(this->indexer);
    }
}

ReferLinkedListImpl::~ReferLinkedListImpl() noexcept {
    for (Size count = 1; count < this->length; ++ count) {
        ReferLinkedListImpl::backNode(this->last);
        delete this->last->next;
    }

    delete this->last;
    delete this->iterator;
}

$RetNotIgnored()
Size ReferLinkedListImpl::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool ReferLinkedListImpl::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference ReferLinkedListImpl::getLast0() const {
    return generic_cast(this->last->value);
}

$RetNotIgnored()
GenericReference ReferLinkedListImpl::getFirst0() const {
    return generic_cast(this->first->value);
}

$RetNotIgnored()
GenericReference ReferLinkedListImpl::get0(const Size index) const {
    if (index < this->length >> 1) {
        this->indexer = this->first;
        for (Size count = 0; count < index; ++ count) {
            ReferLinkedListImpl::nextNode(this->indexer);
        }
    } else {
        this->indexer = this->last;
        for (Size count = this->length - 1; count > index; -- count) {
            ReferLinkedListImpl::backNode(this->indexer);
        }
    }

    return generic_cast(this->indexer->value);
}

$RetNotIgnored()
bool ReferLinkedListImpl::contain0(GenericReference value) const {
    this->indexer = this->first;
    for (Size count = 0; count < this->length; ++ count) {
        if (this->genericOperator.equals(generic_cast(this->indexer->value), value)) {
            return true;
        }
        this->indexer = this->indexer->next;
    }

    return false;
}

void ReferLinkedListImpl::addLast0(GenericReference element) {
    if (this->isEmpty0()) {
        this->last = new Node();
        this->last->value = &element;
        this->first = this->last;
    } else {
        this->last->next = new Node();
        this->last->next->value = &element;
        this->last->next->back = this->last;
        ReferLinkedListImpl::nextNode(this->last);
    }

    ++ this->length;
}

void ReferLinkedListImpl::removeLast0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        ReferLinkedListImpl::backNode(this->last);
        delete this->last->next;
    } else {
        delete this->last;
        this->last = this->first = null;
    }

    -- this->length;
}

void ReferLinkedListImpl::addFirst0(GenericReference element) {
    if (this->isEmpty0()) {
        this->first = new Node();
        this->first->value = &element;
        this->last = this->first;
    } else {
        this->first->back = new Node();
        this->first->back->value = &element;
        this->first->back->next = this->first;
        ReferLinkedListImpl::backNode(this->first);
    }

    ++ this->length;
}

void ReferLinkedListImpl::removeFirst0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        ReferLinkedListImpl::nextNode(this->first);
        delete this->first->back;
    } else {
        delete this->first;
        this->first = this->last = null;
    }

    -- this->length;
}