/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#include "EnhancedBasic/collection/referenced/ReferencedLinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/assert.h"

#include "EnhancedBasic/generic/Generic.h"

using BasicGenericImpl::collection::referenced::ReferencedLinkedListImpl;

ReferencedLinkedListImpl::ReferencedLinkedListIteratorImpl::
ReferencedLinkedListIteratorImpl(const ReferencedLinkedListImpl *const referencedLinkedList) :
    referencedLinkedList(referencedLinkedList), isFirst(true) {
    this->referencedLinkedList->indexer = this->referencedLinkedList->first;
}

ReferencedLinkedListImpl::ReferencedLinkedListIteratorImpl::~ReferencedLinkedListIteratorImpl() noexcept = default;

$RetNotIgnored()
bool ReferencedLinkedListImpl::ReferencedLinkedListIteratorImpl::hasNext0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return true;
    } else {
        return this->referencedLinkedList->indexer != null;
    }
}

void ReferencedLinkedListImpl::ReferencedLinkedListIteratorImpl::next0() const {
    ReferencedLinkedListImpl::nextNode(this->referencedLinkedList->indexer);
}

$RetNotIgnored()
bool ReferencedLinkedListImpl::ReferencedLinkedListIteratorImpl::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->referencedLinkedList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference ReferencedLinkedListImpl::ReferencedLinkedListIteratorImpl::get0() const {
    return generic_cast(this->referencedLinkedList->indexer->value);
}

void ReferencedLinkedListImpl::ReferencedLinkedListIteratorImpl::reset0() const {
    this->isFirst = true;
    this->referencedLinkedList->indexer = this->referencedLinkedList->first;
}

$RetNotIgnored()
Size ReferencedLinkedListImpl::ReferencedLinkedListIteratorImpl::count0() const {
    return this->referencedLinkedList->getLength0();
}

ReferencedLinkedListImpl::Node *&ReferencedLinkedListImpl::nextNode(Node *&node) {
    return node = node->next;
}

ReferencedLinkedListImpl::Node *&ReferencedLinkedListImpl::backNode(Node *&node) {
    return node = node->back;
}

ReferencedLinkedListImpl::ReferencedLinkedListImpl(const GenericOperator genericOperator) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(genericOperator), iterator(null) {}

ReferencedLinkedListImpl::ReferencedLinkedListImpl(const ReferencedLinkedListImpl &other) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(other.genericOperator), iterator(null) {
    this->indexer = other.first;
    for (Size count = 0; count < other.length; ++ count) {
        this->addLast0(generic_cast(this->indexer->value));
        ReferencedLinkedListImpl::nextNode(this->indexer);
    }
}

ReferencedLinkedListImpl::~ReferencedLinkedListImpl() noexcept {
    for (Size count = 1; count < this->length; ++ count) {
        ReferencedLinkedListImpl::backNode(this->last);
        delete this->last->next;
    }

    delete this->last;
    delete this->iterator;
}

$RetNotIgnored()
Size ReferencedLinkedListImpl::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool ReferencedLinkedListImpl::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference ReferencedLinkedListImpl::getLast0() const {
    return generic_cast(this->last->value);
}

$RetNotIgnored()
GenericReference ReferencedLinkedListImpl::getFirst0() const {
    return generic_cast(this->first->value);
}

$RetNotIgnored()
GenericReference ReferencedLinkedListImpl::get0(const Size index) const {
    if (index < this->length >> 1) {
        this->indexer = this->first;
        for (Size count = 0; count < index; ++ count) {
            ReferencedLinkedListImpl::nextNode(this->indexer);
        }
    } else {
        this->indexer = this->last;
        for (Size count = this->length - 1; count > index; -- count) {
            ReferencedLinkedListImpl::backNode(this->indexer);
        }
    }

    return generic_cast(this->indexer->value);
}

$RetNotIgnored()
bool ReferencedLinkedListImpl::contain0(GenericReference value) const {
    this->indexer = this->first;
    for (Size count = 0; count < this->length; ++ count) {
        if (this->genericOperator.equals(generic_cast(this->indexer->value), value)) {
            return true;
        }
        this->indexer = this->indexer->next;
    }

    return false;
}

void ReferencedLinkedListImpl::addLast0(GenericReference element) {
    if (this->isEmpty0()) {
        this->last = new Node();
        this->last->value = &element;
        this->first = this->last;
    } else {
        this->last->next = new Node();
        this->last->next->value = &element;
        this->last->next->back = this->last;
        ReferencedLinkedListImpl::nextNode(this->last);
    }

    ++ this->length;
}

void ReferencedLinkedListImpl::removeLast0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        ReferencedLinkedListImpl::backNode(this->last);
        delete this->last->next;
    } else {
        delete this->last;
        this->last = this->first = null;
    }

    -- this->length;
}

void ReferencedLinkedListImpl::addFirst0(GenericReference element) {
    if (this->isEmpty0()) {
        this->first = new Node();
        this->first->value = &element;
        this->last = this->first;
    } else {
        this->first->back = new Node();
        this->first->back->value = &element;
        this->first->back->next = this->first;
        ReferencedLinkedListImpl::backNode(this->first);
    }

    ++ this->length;
}

void ReferencedLinkedListImpl::removeFirst0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        ReferencedLinkedListImpl::nextNode(this->first);
        delete this->first->back;
    } else {
        delete this->first;
        this->first = this->last = null;
    }

    -- this->length;
}
