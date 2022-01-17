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

#include "EnhancedBasic/collection/mixed/MixedLinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/assert.h"

#include "EnhancedBasic/generic/Generic.h"

using EnhancedBasic::collection::mixed::MixedLinkedList0;

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
    MixedLinkedList0::nextNode(this->mixedLinkedList->indexer);
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
GenericReference MixedLinkedList0::MixedLinkedListIterator0::get0() const {
    return generic_cast(this->mixedLinkedList->indexer->value);
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

MixedLinkedList0::MixedLinkedList0(const MixedLinkedList0 &copy) :
    first(null), last(null), indexer(null), length(0),
    genericsOperator(copy.genericsOperator), iterator(null) {
    this->indexer = copy.first;
    for (Size count = 0; count < copy.length; ++ count) {
        if (this->indexer->dynamic) {
            this->addLast0(generic_cast(this->indexer->value));
        } else {
            this->addLastReferenced0(generic_cast(this->indexer->value));
        }
        MixedLinkedList0::nextNode(this->indexer);
    }
}

MixedLinkedList0::~MixedLinkedList0() noexcept {
    for (Size count = 1; count < this->length; ++ count) {
        MixedLinkedList0::backNode(this->last);

        if (this->last->next->dynamic) {
            this->genericsOperator.destroy(this->last->next->value);
        }
        delete this->last->next;
    }

    if (!this->isEmpty0() && this->last->dynamic) {
        this->genericsOperator.destroy(this->last->value);
    }

    delete this->last;
    delete this->iterator;
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
GenericReference MixedLinkedList0::getFirst0() const {
    return generic_cast(this->first->value);
}

$RetNotIgnored()
GenericReference MixedLinkedList0::getLast0() const {
    return generic_cast(this->last->value);
}

$RetNotIgnored()
GenericReference MixedLinkedList0::get0(const Size index) const {
    if (index < this->length >> 1) {
        this->indexer = this->first;
        for (Size count = 0; count < index; ++ count) {
            MixedLinkedList0::nextNode(this->indexer);
        }
    } else {
        this->indexer = this->last;
        for (Size count = this->length - 1; count > index; -- count) {
            MixedLinkedList0::backNode(this->indexer);
        }
    }

    return generic_cast(this->indexer->value);
}

$RetNotIgnored()
bool MixedLinkedList0::contain0(GenericReference value) const {
    this->indexer = this->first;
    for (Size count = 0; count < this->length; ++ count) {
        if (this->genericsOperator.equals(generic_cast(this->indexer->value), value)) {
            return true;
        }
        this->indexer = this->indexer->next;
    }

    return false;
}

void MixedLinkedList0::addLast0(GenericReference element) {
    if (this->isEmpty0()) {
        this->last = new MixedLinkedList0::Node();
        this->last->dynamic = true;
        this->last->value = this->genericsOperator.allocate(element);
        this->first = this->last;
    } else {
        this->last->next = new MixedLinkedList0::Node();
        this->last->next->dynamic = true;
        this->last->next->value = this->genericsOperator.allocate(element);
        this->last->next->back = this->last;
        MixedLinkedList0::nextNode(this->last);
    }

    ++ this->length;
}

void MixedLinkedList0::addLastReferenced0(GenericReference element) {
    if (this->isEmpty0()) {
        this->last = new MixedLinkedList0::Node();
        this->last->value = &element;
        this->first = this->last;
    } else {
        this->last->next = new MixedLinkedList0::Node();
        this->last->next->value = &element;
        this->last->next->back = this->last;
        MixedLinkedList0::nextNode(this->last);
    }

    ++ this->length;
}

void MixedLinkedList0::removeLast0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        MixedLinkedList0::backNode(this->last);
        if (this->last->next->dynamic) {
            this->genericsOperator.destroy(this->last->next->value);
        }
        delete this->last->next;
    } else {
        if (this->last->dynamic) {
            this->genericsOperator.destroy(this->last->value);
        }
        delete this->last;
        this->last = this->first = null;
    }

    -- this->length;
}

void MixedLinkedList0::addFirst0(GenericReference element) {
    if (this->isEmpty0()) {
        this->first = new MixedLinkedList0::Node();
        this->first->dynamic = true;
        this->first->value = this->genericsOperator.allocate(element);
        this->last = this->first;
    } else {
        this->first->back = new MixedLinkedList0::Node();
        this->first->back->dynamic = true;
        this->first->back->value = this->genericsOperator.allocate(element);
        this->first->back->next = this->first;
        MixedLinkedList0::backNode(this->first);
    }

    ++ this->length;
}

void MixedLinkedList0::addFirstReferenced0(GenericReference element) {
    if (this->isEmpty0()) {
        this->first = new MixedLinkedList0::Node();
        this->first->value = &element;
        this->last = this->first;
    } else {
        this->first->back = new MixedLinkedList0::Node();
        this->first->back->value = &element;
        this->first->back->next = this->first;
        MixedLinkedList0::backNode(this->first);
    }

    ++ this->length;
}

void MixedLinkedList0::removeFirst0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        MixedLinkedList0::nextNode(this->first);
        if (this->first->back->dynamic) {
            this->genericsOperator.destroy(this->first->back->value);
        }
        delete this->first->back;
    } else {
        if (this->first->dynamic) {
            this->genericsOperator.destroy(this->first->value);
        }
        delete this->first;
        this->first = this->last = null;
    }

    -- this->length;
}
