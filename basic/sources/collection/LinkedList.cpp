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

#include "EnhancedBasic/collection/LinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/assert.h"

#include "EnhancedBasic/generic/Generic.h"

using BasicGenericImpl::collection::LinkedListImpl;

LinkedListImpl::LinkedListIteratorImpl::LinkedListIteratorImpl(const LinkedListImpl *linkedList) :
    linkedList(linkedList), isFirst(true) {
    this->linkedList->indexer = this->linkedList->first;
}

LinkedListImpl::LinkedListIteratorImpl::~LinkedListIteratorImpl() noexcept = default;

$RetNotIgnored()
bool LinkedListImpl::LinkedListIteratorImpl::hasNext0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return true;
    } else {
        return this->linkedList->indexer != null;
    }
}

void LinkedListImpl::LinkedListIteratorImpl::next0() const {
    LinkedListImpl::nextNode(this->linkedList->indexer);
}

$RetNotIgnored()
bool LinkedListImpl::LinkedListIteratorImpl::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->linkedList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference LinkedListImpl::LinkedListIteratorImpl::get0() const {
    return generic_cast(this->linkedList->indexer->value);
}

void LinkedListImpl::LinkedListIteratorImpl::reset0() const {
    this->isFirst = true;
    this->linkedList->indexer = this->linkedList->first;
}

$RetNotIgnored()
Size LinkedListImpl::LinkedListIteratorImpl::count0() const {
    return this->linkedList->getLength0();
}

LinkedListImpl::Node *&LinkedListImpl::nextNode(Node *&node) {
    return node = node->next;
}

LinkedListImpl::Node *&LinkedListImpl::backNode(Node *&node) {
    return node = node->back;
}

LinkedListImpl::LinkedListImpl(const GenericOperator genericOperator) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(genericOperator), iterator(null) {}

LinkedListImpl::LinkedListImpl(const LinkedListImpl &other) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(other.genericOperator), iterator(null) {
    this->indexer = other.first;
    for (Size count = 0; count < other.length; ++ count) {
        this->addLast0(generic_cast(this->indexer->value));
        LinkedListImpl::nextNode(this->indexer);
    }
}

LinkedListImpl::~LinkedListImpl() noexcept {
    for (Size count = 1; count < this->length; ++ count) {
        LinkedListImpl::backNode(this->last);

        this->genericOperator.destroy(this->last->next->value);
        delete this->last->next;
    }

    if (!this->isEmpty0()) {
        this->genericOperator.destroy(this->last->value);
    }

    delete this->last;
    delete this->iterator;
}

$RetNotIgnored()
Size LinkedListImpl::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool LinkedListImpl::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference LinkedListImpl::getFirst0() const {
    return generic_cast(this->first->value);
}

$RetNotIgnored()
GenericReference LinkedListImpl::getLast0() const {
    return generic_cast(this->last->value);
}

$RetNotIgnored()
GenericReference LinkedListImpl::get0(const Size index) const {
    if (index < this->length >> 1) {
        this->indexer = this->first;
        for (Size count = 0; count < index; ++ count) {
            LinkedListImpl::nextNode(this->indexer);
        }
    } else {
        this->indexer = this->last;
        for (Size count = this->length - 1; count > index; -- count) {
            LinkedListImpl::backNode(this->indexer);
        }
    }

    return generic_cast(this->indexer->value);
}

$RetNotIgnored()
bool LinkedListImpl::contain0(GenericReference value) const {
    this->indexer = this->first;
    for (Size count = 0; count < this->length; ++ count) {
        if (this->genericOperator.equals(this->indexer->value, const_cast<void *&>(value))) {
            return true;
        }
        LinkedListImpl::nextNode(this->indexer);
    }

    return false;
}

void LinkedListImpl::addLast0(GenericReference element) {
    if (this->isEmpty0()) {
        this->last = new Node();
        this->last->value = this->genericOperator.allocate(element);
        this->first = this->last;
    } else {
        this->last->next = new Node();
        this->last->next->value = this->genericOperator.allocate(element);
        this->last->next->back = this->last;
        LinkedListImpl::nextNode(this->last);
    }

    ++ this->length;
}

void LinkedListImpl::removeLast0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        LinkedListImpl::backNode(this->last);
        this->genericOperator.destroy(this->last->next->value);
        delete this->last->next;
    } else {
        this->genericOperator.destroy(this->last->value);
        delete this->last;
        this->last = this->first = null;
    }

    -- this->length;
}

void LinkedListImpl::addFirst0(GenericReference element) {
    if (this->isEmpty0()) {
        this->first = new Node();
        this->first->value = this->genericOperator.allocate(element);
        this->last = this->first;
    } else {
        this->first->back = new Node();
        this->first->back->value = this->genericOperator.allocate(element);
        this->first->back->next = this->first;
        LinkedListImpl::backNode(this->first);
    }

    ++ this->length;
}

void LinkedListImpl::removeFirst0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        LinkedListImpl::nextNode(this->first);
        this->genericOperator.destroy(this->first->back->value);
        delete this->first->back;
    } else {
        this->genericOperator.destroy(this->first->value);
        delete this->first;
        this->first = this->last = null;
    }

    -- this->length;
}
