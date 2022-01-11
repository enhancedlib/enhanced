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

#include "EnhancedBasic/collection/mixed/MixedLinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

using EnhancedBasic::Collection::Mixed::MixedLinkedList0;

MixedLinkedList0::MixedLinkedListIterator0::
MixedLinkedListIterator0(const MixedLinkedList0 *mixedLinkedList) :
    mixedLinkedList(mixedLinkedList), isFirst(true) {
    this->mixedLinkedList->indexer = this->mixedLinkedList->first;
}

MixedLinkedList0::MixedLinkedListIterator0::~MixedLinkedListIterator0() noexcept = default;

$RetNotIgnored()
bool MixedLinkedList0::MixedLinkedListIterator0::hasNext0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return true;
    } else {
        return this->mixedLinkedList->indexer != null;
    }
}

void MixedLinkedList0::MixedLinkedListIterator0::next0() const {
    nextNode(this->mixedLinkedList->indexer);
}

$RetNotIgnored()
bool MixedLinkedList0::MixedLinkedListIterator0::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->mixedLinkedList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
void *MixedLinkedList0::MixedLinkedListIterator0::get0() const {
    return this->mixedLinkedList->indexer->value;
}

void MixedLinkedList0::MixedLinkedListIterator0::reset0() const {
    this->isFirst = true;
    this->mixedLinkedList->indexer = this->mixedLinkedList->first;
}

$RetNotIgnored()
Size MixedLinkedList0::MixedLinkedListIterator0::count0() const {
    return this->mixedLinkedList->getLength0();
}

MixedLinkedList0::Node *&MixedLinkedList0::nextNode(Node *&node) {
    return node = node->next;
}

MixedLinkedList0::Node *&MixedLinkedList0::backNode(Node *&node) {
    return node = node->back;
}

MixedLinkedList0::MixedLinkedList0(const GenericsOperator genericsOperator) :
    first(null), last(null), indexer(null), length(0),
    genericsOperator(genericsOperator), iterator(null) {}

MixedLinkedList0::MixedLinkedList0(const MixedLinkedList0 &originalCopy) :
    first(null), last(null), indexer(null), length(0),
    genericsOperator(originalCopy.genericsOperator), iterator(null) {
    this->indexer = originalCopy.first;
    for (Size count = 0; count < originalCopy.length; ++ count) {
        this->addFirst0((const void *) this->indexer->value);
        nextNode(this->indexer);
    }
}

MixedLinkedList0::~MixedLinkedList0() noexcept {
    for (Size count = 1; count < this->length; ++ count) {
        backNode(this->last);

        if (this->last->next->requiresRelease) {
            this->genericsOperator.genericsDelete(this->last->next->value);
        }
        delete this->last->next;
    }

    if (this->last->requiresRelease) {
        this->genericsOperator.genericsDelete(this->last->value);
    }
    delete this->last;
    delete this->iterator;
}

$RetNotIgnored()
bool MixedLinkedList0::contain0(const void *const value) const {
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
Size MixedLinkedList0::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool MixedLinkedList0::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
void *MixedLinkedList0::getFirst0() const {
    return this->first->value;
}

$RetNotIgnored()
void *MixedLinkedList0::getLast0() const {
    return this->last->value;
}

$RetNotIgnored()
void *MixedLinkedList0::get0(const Size index) const {
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

void MixedLinkedList0::addLast0(const void *const element) {
    if (this->isEmpty0()) {
        this->last = new MixedLinkedList0::Node();
        this->last->requiresRelease = true;
        this->last->value = this->genericsOperator.genericsNew(const_cast<void *&>(element));
        this->first = this->last;
    } else {
        this->last->next = new MixedLinkedList0::Node();
        this->last->next->requiresRelease = true;
        this->last->next->value = this->genericsOperator.genericsNew(const_cast<void *&>(element));
        this->last->next->back = this->last;
        nextNode(this->last);
    }
    ++ this->length;
}

void MixedLinkedList0::addLastReferenced0(const void *const element) {
    if (this->isEmpty0()) {
        this->last = new MixedLinkedList0::Node();
        this->last->value = const_cast<void *>(element);
        this->first = this->last;
    } else {
        this->last->next = new MixedLinkedList0::Node();
        this->last->next->value = const_cast<void *>(element);
        this->last->next->back = this->last;
        nextNode(this->last);
    }
    ++ this->length;
}

void MixedLinkedList0::addFirst0(const void *const element) {
    if (this->isEmpty0()) {
        this->first = new MixedLinkedList0::Node();
        this->first->requiresRelease = true;
        this->first->value = this->genericsOperator.genericsNew(const_cast<void *&>(element));
        this->last = this->first;
    } else {
        this->first->back = new MixedLinkedList0::Node();
        this->first->back->requiresRelease = true;
        this->first->back->value = this->genericsOperator.genericsNew(const_cast<void *&>(element));
        this->first->back->next = this->first;
        backNode(this->first);
    }
    ++ this->length;
}

void MixedLinkedList0::addFirstReferenced0(const void *const element) {
    if (this->isEmpty0()) {
        this->first = new MixedLinkedList0::Node();
        this->first->value = const_cast<void *>(element);
        this->last = this->first;
    } else {
        this->first->back = new MixedLinkedList0::Node();
        this->first->back->value = const_cast<void *>(element);
        this->first->back->next = this->first;
        backNode(this->first);
    }
    ++ this->length;
}

void MixedLinkedList0::removeLast0() {
    backNode(this->last);

    if (this->last->next->requiresRelease) {
        this->genericsOperator.genericsDelete(this->last->next->value);
    }

    delete this->last->next;
    -- this->length;
}

void MixedLinkedList0::removeFirst0() {
    nextNode(this->first);

    if (this->first->back->requiresRelease) {
        this->genericsOperator.genericsDelete(this->first->back->value);
    }

    delete this->first->back;
    -- this->length;
}
