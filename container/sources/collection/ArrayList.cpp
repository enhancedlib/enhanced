/*
 * Copyright (C) 2021 Liu Baihao. All rights reserved.
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

#include "EnhancedContainer/collection/ArrayList.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/array.h"

using EnhancedContainer::Collection::ArrayList0;

ArrayList0::ArrayListIterator0::ArrayListIterator0(const ArrayList0 *const arrayList) :
    arrayList(arrayList), indexer(arrayList->elements), isFirst(true),
    end((const void **) arrayList->elements + arrayList->getLength0()) {}

#ifdef CXX_11_OR_MORE

ArrayList0::ArrayListIterator0::~ArrayListIterator0() noexcept = default;

#else

ArrayList0::ArrayListIterator0::~ArrayListIterator0() noexcept {}

#endif // CXX_11_OR_MORE

$RetNotIgnored()
bool ArrayList0::ArrayListIterator0::hasNext0() const {
    return this->indexer != this->end;
}

void ArrayList0::ArrayListIterator0::next0() const {
    ++ this->indexer;
}

$RetNotIgnored()
bool ArrayList0::ArrayListIterator0::each0() const {
    if (this->isFirst) {
        this->isFirst = false;
        return !this->arrayList->isEmpty0();
    }

    this->next0();
    return this->hasNext0();
}

$RetNotIgnored()
void *ArrayList0::ArrayListIterator0::get0() const {
    return *this->indexer;
}

void ArrayList0::ArrayListIterator0::reset0() const {
    this->isFirst = true;
    this->indexer = this->arrayList->elements;
}

$RetNotIgnored()
Size ArrayList0::ArrayListIterator0::count0() const {
    return this->arrayList->getLength0();
}

ArrayList0::ArrayList0(const Size maxCount, const ElementOperator elementOperator) :
    maxCount(maxCount), length(0), elements(new void *[maxCount]),
    elementOperator(elementOperator), iterator(null) {}

ArrayList0::~ArrayList0() noexcept {
    while (this->length > 0) {
        this->remove0();
    }
    delete[] this->elements;
    delete this->iterator;
}

Size ArrayList0::getLength0() const {
    return this->length;
}

bool ArrayList0::isEmpty0() const {
    return this->length == 0;
}

void *&ArrayList0::get0(const Size index) const {
    return this->elements[index];
}

bool ArrayList0::contain0(const void *const element) const {
    for (Size index = 0; index < this->length; ++ index) {
        if (this->elementOperator.elementEqual(this->elements[index], const_cast<void *&>(element))) {
            return true;
        }
    }

    return false;
}

void ArrayList0::add0(const void *const element) {
    if (this->length == this->maxCount) {
        this->expand0(this->maxCount >> 1);
    }

    this->elements[this->length] = this->elementOperator.elementNew(const_cast<void *&>(element));
    ++ this->length;
}

void ArrayList0::remove0() {
    this->elementOperator.elementDelete(this->elements[-- this->length]);
}

void ArrayList0::expand0(const Size size) {
    Size count = this->maxCount + size;
    void **array = new void *[count];

    arrayCopy(array, this->elements, count, sizeof(void *));
    delete[] this->elements;

    this->elements = array;
}

void ArrayList0::shrink0(const Size size) {
    Size count = this->maxCount - size;
    if (count < this->length) {
        return;
    }

    void **array = new void *[count];

    arrayCopy(array, this->elements, count, sizeof(void *));
    delete[] this->elements;

    this->elements = array;
}
