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

using EnhancedBasic::collection::LinkedList0;

LinkedList0::LinkedListIterator0::LinkedListIterator0(const LinkedList0 *linkedList) :
    linkedList(linkedList), isFirst(true) {
    this->linkedList->indexer = this->linkedList->first;
}

LinkedList0::LinkedListIterator0::~LinkedListIterator0() noexcept = default;

$RetNotIgnored()
bool LinkedList0::LinkedListIterator0::hasNext0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return true;
    } else {
        return this->linkedList->indexer != null;
    }
}

void LinkedList0::LinkedListIterator0::next0() const {
    LinkedList0::nextNode(this->linkedList->indexer);
}

$RetNotIgnored()
bool LinkedList0::LinkedListIterator0::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->linkedList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference LinkedList0::LinkedListIterator0::get0() const {
    return generic_cast(this->linkedList->indexer->value);
}

void LinkedList0::LinkedListIterator0::reset0() const {
    this->isFirst = true;
    this->linkedList->indexer = this->linkedList->first;
}

$RetNotIgnored()
Size LinkedList0::LinkedListIterator0::count0() const {
    return this->linkedList->getLength0();
}

LinkedList0::Node *&LinkedList0::nextNode(Node *&node) {
    return node = node->next;
}

LinkedList0::Node *&LinkedList0::backNode(Node *&node) {
    return node = node->back;
}

LinkedList0::LinkedList0(const GenericsOperator genericsOperator) :
    first(null), last(null), indexer(null), length(0),
    genericsOperator(genericsOperator), iterator(null) {}

LinkedList0::LinkedList0(const LinkedList0 &other) :
    first(null), last(null), indexer(null), length(0),
    genericsOperator(other.genericsOperator), iterator(null) {
    this->indexer = other.first;
    for (Size count = 0; count < other.length; ++ count) {
        this->addLast0(generic_cast(this->indexer->value));
        LinkedList0::nextNode(this->indexer);
    }
}

LinkedList0::~LinkedList0() noexcept {
    for (Size count = 1; count < this->length; ++ count) {
        LinkedList0::backNode(this->last);

        this->genericsOperator.destroy(this->last->next->value);
        delete this->last->next;
    }

    if (!this->isEmpty0()) {
        this->genericsOperator.destroy(this->last->value);
    }

    delete this->last;
    delete this->iterator;
}

$RetNotIgnored()
Size LinkedList0::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool LinkedList0::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference LinkedList0::getFirst0() const {
    return generic_cast(this->first->value);
}

$RetNotIgnored()
GenericReference LinkedList0::getLast0() const {
    return generic_cast(this->last->value);
}

$RetNotIgnored()
GenericReference LinkedList0::get0(const Size index) const {
    if (index < this->length >> 1) {
        this->indexer = this->first;
        for (Size count = 0; count < index; ++ count) {
            LinkedList0::nextNode(this->indexer);
        }
    } else {
        this->indexer = this->last;
        for (Size count = this->length - 1; count > index; -- count) {
            LinkedList0::backNode(this->indexer);
        }
    }

    return generic_cast(this->indexer->value);
}

$RetNotIgnored()
bool LinkedList0::contain0(GenericReference value) const {
    this->indexer = this->first;
    for (Size count = 0; count < this->length; ++ count) {
        if (this->genericsOperator.equals(this->indexer->value, const_cast<void *&>(value))) {
            return true;
        }
        LinkedList0::nextNode(this->indexer);
    }

    return false;
}

void LinkedList0::addLast0(GenericReference element) {
    if (this->isEmpty0()) {
        this->last = new Node();
        this->last->value = this->genericsOperator.allocate(element);
        this->first = this->last;
    } else {
        this->last->next = new Node();
        this->last->next->value = this->genericsOperator.allocate(element);
        this->last->next->back = this->last;
        LinkedList0::nextNode(this->last);
    }

    ++ this->length;
}

void LinkedList0::removeLast0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        LinkedList0::backNode(this->last);
        this->genericsOperator.destroy(this->last->next->value);
        delete this->last->next;
    } else {
        this->genericsOperator.destroy(this->last->value);
        delete this->last;
        this->last = this->first = null;
    }

    -- this->length;
}

void LinkedList0::addFirst0(GenericReference element) {
    if (this->isEmpty0()) {
        this->first = new Node();
        this->first->value = this->genericsOperator.allocate(element);
        this->last = this->first;
    } else {
        this->first->back = new Node();
        this->first->back->value = this->genericsOperator.allocate(element);
        this->first->back->next = this->first;
        LinkedList0::backNode(this->first);
    }

    ++ this->length;
}

void LinkedList0::removeFirst0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        LinkedList0::nextNode(this->first);
        this->genericsOperator.destroy(this->first->back->value);
        delete this->first->back;
    } else {
        this->genericsOperator.destroy(this->first->value);
        delete this->first;
        this->first = this->last = null;
    }

    -- this->length;
}
