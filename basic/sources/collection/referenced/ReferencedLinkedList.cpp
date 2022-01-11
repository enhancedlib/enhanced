/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This product is licensed under Enhanced License.
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

using EnhancedBasic::Collection::Referenced::ReferencedLinkedList0;

ReferencedLinkedList0::ReferencedLinkedListIterator0::
ReferencedLinkedListIterator0(const ReferencedLinkedList0 *referencedLinkedList) :
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
    nextNode(this->referencedLinkedList->indexer);
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
void *ReferencedLinkedList0::ReferencedLinkedListIterator0::get0() const {
    return this->referencedLinkedList->indexer->value;
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

ReferencedLinkedList0::ReferencedLinkedList0(const ReferencedLinkedList0 &originalCopy) :
    first(null), last(null), indexer(null), length(0),
    genericsOperator(originalCopy.genericsOperator), iterator(null) {
    this->indexer = originalCopy.first;
    for (Size count = 0; count < originalCopy.length; ++ count) {
        this->addFirst0((const void *) this->indexer->value);
        nextNode(this->indexer);
    }
}

ReferencedLinkedList0::~ReferencedLinkedList0() noexcept {
    for (Size count = 1; count < this->length; ++ count) {
        backNode(this->last);
        delete this->last->next;
    }
    delete this->last;
    delete this->iterator;
}

$RetNotIgnored()
bool ReferencedLinkedList0::contain0(const void *const value) const {
    this->indexer = this->first;
    for (Size count = 0; count < this->length; ++ count) {
        if (this->genericsOperator.genericsEquals(this->indexer->value, const_cast<void *&>(value))) {
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
void *ReferencedLinkedList0::getFirst0() const {
    return this->first->value;
}

$RetNotIgnored()
void *ReferencedLinkedList0::getLast0() const {
    return this->last->value;
}

$RetNotIgnored()
void *ReferencedLinkedList0::get0(const Size index) const {
    if (index < this->length >> 1) {
        this->indexer = this->first;
        for (Size count = 0; count < index; ++ count) {
            nextNode(this->indexer);
        }
    } else {
        this->indexer = this->last;
        for (Size count = 0; count < this->length - index - 1; ++ count) {
            backNode(this->indexer);
        }
    }
    return this->indexer->value;
}

void ReferencedLinkedList0::addLast0(const void *const element) {
    if (this->isEmpty0()) {
        this->last = new Node();
        this->last->value = const_cast<void *>(element);
        this->first = this->last;
    } else {
        this->last->next = new Node();
        this->last->next->value = const_cast<void *>(element);
        this->last->next->back = this->last;
        nextNode(this->last);
    }
    ++ this->length;
}

void ReferencedLinkedList0::addFirst0(const void *const element) {
    if (this->isEmpty0()) {
        this->first = new Node();
        this->first->value = const_cast<void *>(element);
        this->last = this->first;
    } else {
        this->first->back = new Node();
        this->first->back->value = const_cast<void *>(element);
        this->first->back->next = this->first;
        backNode(this->first);
    }
    ++ this->length;
}

void ReferencedLinkedList0::removeLast0() {
    backNode(this->last);

    delete this->last->next;
    -- this->length;
}

void ReferencedLinkedList0::removeFirst0() {
    nextNode(this->first);

    delete this->first->back;
    -- this->length;
}
