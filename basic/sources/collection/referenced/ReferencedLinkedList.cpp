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

using EnhancedBasic::collection::referenced::ReferencedLinkedList0;

ReferencedLinkedList0::ReferencedLinkedListIterator0::
ReferencedLinkedListIterator0(const ReferencedLinkedList0 *const referencedLinkedList) :
    referencedLinkedList(referencedLinkedList), isFirst(true) {
    this->referencedLinkedList->indexer = this->referencedLinkedList->first;
}

ReferencedLinkedList0::ReferencedLinkedListIterator0::~ReferencedLinkedListIterator0() noexcept = default;

$RetNotIgnored()
bool ReferencedLinkedList0::ReferencedLinkedListIterator0::hasNext0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return true;
    } else {
        return this->referencedLinkedList->indexer != null;
    }
}

void ReferencedLinkedList0::ReferencedLinkedListIterator0::next0() const {
    ReferencedLinkedList0::nextNode(this->referencedLinkedList->indexer);
}

$RetNotIgnored()
bool ReferencedLinkedList0::ReferencedLinkedListIterator0::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->referencedLinkedList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference ReferencedLinkedList0::ReferencedLinkedListIterator0::get0() const {
    return generic_cast(this->referencedLinkedList->indexer->value);
}

void ReferencedLinkedList0::ReferencedLinkedListIterator0::reset0() const {
    this->isFirst = true;
    this->referencedLinkedList->indexer = this->referencedLinkedList->first;
}

$RetNotIgnored()
Size ReferencedLinkedList0::ReferencedLinkedListIterator0::count0() const {
    return this->referencedLinkedList->getLength0();
}

ReferencedLinkedList0::Node *&ReferencedLinkedList0::nextNode(Node *&node) {
    return node = node->next;
}

ReferencedLinkedList0::Node *&ReferencedLinkedList0::backNode(Node *&node) {
    return node = node->back;
}

ReferencedLinkedList0::ReferencedLinkedList0(const GenericsOperator genericsOperator) :
    first(null), last(null), indexer(null), length(0),
    genericsOperator(genericsOperator), iterator(null) {}

ReferencedLinkedList0::ReferencedLinkedList0(const ReferencedLinkedList0 &copy) :
    first(null), last(null), indexer(null), length(0),
    genericsOperator(copy.genericsOperator), iterator(null) {
    this->indexer = copy.first;
    for (Size count = 0; count < copy.length; ++ count) {
        this->addFirst0(this->indexer->value);
        ReferencedLinkedList0::nextNode(this->indexer);
    }
}

ReferencedLinkedList0::~ReferencedLinkedList0() noexcept {
    for (Size count = 1; count < this->length; ++ count) {
        ReferencedLinkedList0::backNode(this->last);
        delete this->last->next;
    }

    delete this->last;
    delete this->iterator;
}

$RetNotIgnored()
bool ReferencedLinkedList0::contain0(GenericReference value) const {
    this->indexer = this->first;
    for (Size count = 0; count < this->length; ++ count) {
        if (this->genericsOperator.equals(generic_cast(this->indexer->value), value)) {
            return true;
        }
        this->indexer = this->indexer->next;
    }

    return false;
}

$RetNotIgnored()
Size ReferencedLinkedList0::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool ReferencedLinkedList0::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference ReferencedLinkedList0::getLast0() const {
    return generic_cast(this->last->value);
}

$RetNotIgnored()
GenericReference ReferencedLinkedList0::getFirst0() const {
    return generic_cast(this->first->value);
}

$RetNotIgnored()
GenericReference ReferencedLinkedList0::get0(const Size index) const {
    if (index < this->length >> 1) {
        this->indexer = this->first;
        for (Size count = 0; count < index; ++ count) {
            ReferencedLinkedList0::nextNode(this->indexer);
        }
    } else {
        this->indexer = this->last;
        for (Size count = this->length - 1; count > index; -- count) {
            ReferencedLinkedList0::backNode(this->indexer);
        }
    }

    return generic_cast(this->indexer->value);
}

void ReferencedLinkedList0::addLast0(GenericReference element) {
    if (this->isEmpty0()) {
        this->last = new Node();
        this->last->value = &element;
        this->first = this->last;
    } else {
        this->last->next = new Node();
        this->last->next->value = &element;
        this->last->next->back = this->last;
        ReferencedLinkedList0::nextNode(this->last);
    }

    ++ this->length;
}

void ReferencedLinkedList0::removeLast0() {
    assert(!this->isEmpty0());
    
    if (this->length > 1) {
        ReferencedLinkedList0::backNode(this->last);
        delete this->last->next;
    } else {
        delete this->last;
        this->last = this->first = null;
    }

    -- this->length;
}

void ReferencedLinkedList0::addFirst0(GenericReference element) {
    if (this->isEmpty0()) {
        this->first = new Node();
        this->first->value = &element;
        this->last = this->first;
    } else {
        this->first->back = new Node();
        this->first->back->value = &element;
        this->first->back->next = this->first;
        ReferencedLinkedList0::backNode(this->first);
    }

    ++ this->length;
}

void ReferencedLinkedList0::removeFirst0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        ReferencedLinkedList0::nextNode(this->first);
        delete this->first->back;
    } else {
        delete this->first;
        this->first = this->last = null;
    }

    -- this->length;
}
