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

#include "EnhancedBasic/collection/mixed/MixedLinkedList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/assert.h"

#include "EnhancedBasic/generic/Generic.h"

using BasicGenericImpl::collection::mixed::MixedLinkedListImpl;

MixedLinkedListImpl::MixedLinkedListIteratorImpl::
MixedLinkedListIteratorImpl(const MixedLinkedListImpl *mixedLinkedList) :
    mixedLinkedList(mixedLinkedList), isFirst(true) {
    this->mixedLinkedList->indexer = this->mixedLinkedList->first;
}

MixedLinkedListImpl::MixedLinkedListIteratorImpl::~MixedLinkedListIteratorImpl() noexcept = default;

$RetNotIgnored()
bool MixedLinkedListImpl::MixedLinkedListIteratorImpl::hasNext0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return true;
    } else {
        return this->mixedLinkedList->indexer != null;
    }
}

void MixedLinkedListImpl::MixedLinkedListIteratorImpl::next0() const {
    MixedLinkedListImpl::nextNode(this->mixedLinkedList->indexer);
}

$RetNotIgnored()
bool MixedLinkedListImpl::MixedLinkedListIteratorImpl::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->mixedLinkedList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
GenericReference MixedLinkedListImpl::MixedLinkedListIteratorImpl::get0() const {
    return generic_cast(this->mixedLinkedList->indexer->value);
}

void MixedLinkedListImpl::MixedLinkedListIteratorImpl::reset0() const {
    this->isFirst = true;
    this->mixedLinkedList->indexer = this->mixedLinkedList->first;
}

$RetNotIgnored()
Size MixedLinkedListImpl::MixedLinkedListIteratorImpl::count0() const {
    return this->mixedLinkedList->getLength0();
}

MixedLinkedListImpl::Node *&MixedLinkedListImpl::nextNode(Node *&node) {
    return node = node->next;
}

MixedLinkedListImpl::Node *&MixedLinkedListImpl::backNode(Node *&node) {
    return node = node->back;
}

MixedLinkedListImpl::MixedLinkedListImpl(const GenericOperator genericOperator) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(genericOperator), iterator(null) {}

MixedLinkedListImpl::MixedLinkedListImpl(const MixedLinkedListImpl &other) :
    first(null), last(null), indexer(null), length(0),
    genericOperator(other.genericOperator), iterator(null) {
    this->indexer = other.first;
    for (Size count = 0; count < other.length; ++ count) {
        if (this->indexer->dynamic) {
            this->addLast0(generic_cast(this->indexer->value));
        } else {
            this->addLastReferenced0(generic_cast(this->indexer->value));
        }
        MixedLinkedListImpl::nextNode(this->indexer);
    }
}

MixedLinkedListImpl::~MixedLinkedListImpl() noexcept {
    for (Size count = 1; count < this->length; ++ count) {
        MixedLinkedListImpl::backNode(this->last);

        if (this->last->next->dynamic) {
            this->genericOperator.destroy(this->last->next->value);
        }
        delete this->last->next;
    }

    if (!this->isEmpty0() && this->last->dynamic) {
        this->genericOperator.destroy(this->last->value);
    }

    delete this->last;
    delete this->iterator;
}

$RetNotIgnored()
Size MixedLinkedListImpl::getLength0() const {
    return this->length;
}

$RetNotIgnored()
bool MixedLinkedListImpl::isEmpty0() const {
    return this->length == 0;
}

$RetNotIgnored()
GenericReference MixedLinkedListImpl::getFirst0() const {
    return generic_cast(this->first->value);
}

$RetNotIgnored()
GenericReference MixedLinkedListImpl::getLast0() const {
    return generic_cast(this->last->value);
}

$RetNotIgnored()
GenericReference MixedLinkedListImpl::get0(const Size index) const {
    if (index < this->length >> 1) {
        this->indexer = this->first;
        for (Size count = 0; count < index; ++ count) {
            MixedLinkedListImpl::nextNode(this->indexer);
        }
    } else {
        this->indexer = this->last;
        for (Size count = this->length - 1; count > index; -- count) {
            MixedLinkedListImpl::backNode(this->indexer);
        }
    }

    return generic_cast(this->indexer->value);
}

$RetNotIgnored()
bool MixedLinkedListImpl::contain0(GenericReference value) const {
    this->indexer = this->first;
    for (Size count = 0; count < this->length; ++ count) {
        if (this->genericOperator.equals(generic_cast(this->indexer->value), value)) {
            return true;
        }
        this->indexer = this->indexer->next;
    }

    return false;
}

void MixedLinkedListImpl::addLast0(GenericReference element) {
    if (this->isEmpty0()) {
        this->last = new MixedLinkedListImpl::Node();
        this->last->dynamic = true;
        this->last->value = this->genericOperator.allocate(element);
        this->first = this->last;
    } else {
        this->last->next = new MixedLinkedListImpl::Node();
        this->last->next->dynamic = true;
        this->last->next->value = this->genericOperator.allocate(element);
        this->last->next->back = this->last;
        MixedLinkedListImpl::nextNode(this->last);
    }

    ++ this->length;
}

void MixedLinkedListImpl::addLastReferenced0(GenericReference element) {
    if (this->isEmpty0()) {
        this->last = new MixedLinkedListImpl::Node();
        this->last->value = &element;
        this->first = this->last;
    } else {
        this->last->next = new MixedLinkedListImpl::Node();
        this->last->next->value = &element;
        this->last->next->back = this->last;
        MixedLinkedListImpl::nextNode(this->last);
    }

    ++ this->length;
}

void MixedLinkedListImpl::removeLast0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        MixedLinkedListImpl::backNode(this->last);
        if (this->last->next->dynamic) {
            this->genericOperator.destroy(this->last->next->value);
        }
        delete this->last->next;
    } else {
        if (this->last->dynamic) {
            this->genericOperator.destroy(this->last->value);
        }
        delete this->last;
        this->last = this->first = null;
    }

    -- this->length;
}

void MixedLinkedListImpl::addFirst0(GenericReference element) {
    if (this->isEmpty0()) {
        this->first = new MixedLinkedListImpl::Node();
        this->first->dynamic = true;
        this->first->value = this->genericOperator.allocate(element);
        this->last = this->first;
    } else {
        this->first->back = new MixedLinkedListImpl::Node();
        this->first->back->dynamic = true;
        this->first->back->value = this->genericOperator.allocate(element);
        this->first->back->next = this->first;
        MixedLinkedListImpl::backNode(this->first);
    }

    ++ this->length;
}

void MixedLinkedListImpl::addFirstReferenced0(GenericReference element) {
    if (this->isEmpty0()) {
        this->first = new MixedLinkedListImpl::Node();
        this->first->value = &element;
        this->last = this->first;
    } else {
        this->first->back = new MixedLinkedListImpl::Node();
        this->first->back->value = &element;
        this->first->back->next = this->first;
        MixedLinkedListImpl::backNode(this->first);
    }

    ++ this->length;
}

void MixedLinkedListImpl::removeFirst0() {
    assert(!this->isEmpty0());

    if (this->length > 1) {
        MixedLinkedListImpl::nextNode(this->first);
        if (this->first->back->dynamic) {
            this->genericOperator.destroy(this->first->back->value);
        }
        delete this->first->back;
    } else {
        if (this->first->dynamic) {
            this->genericOperator.destroy(this->first->value);
        }
        delete this->first;
        this->first = this->last = null;
    }

    -- this->length;
}
