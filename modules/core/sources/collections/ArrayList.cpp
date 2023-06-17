/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <enhanced/collections/ArrayList.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Array.h>
#include <enhanced/Assert.h>
#include <enhanced/Memory.h>
#include <enhanced/exceptions/IndexOutOfBoundsException.h>
#include <enhanced/exceptions/OperationException.h>

using enhanced::sizetype;
using enhanced::arrayCopy;
using enhanced::exceptions::IndexOutOfBoundsException;
using enhanced::exceptions::OperationException;

namespace enhancedInternal::collections {
    ArrayListImpl::ArrayListImpl(sizetype capacity) :
        elements(new void*[capacity]), size(0), capacity(capacity),
        expansionSizeFunc([](sizetype capacity) { return capacity == 0 ? capacity : 1; }) {}

    ArrayListImpl::ArrayListImpl(const ArrayListImpl& other, OpCopy opCopy) :
        elements(new void*[other.capacity]), size(other.size),
        capacity(other.capacity), expansionSizeFunc([](sizetype capacity) { return capacity == 0 ? capacity : 1; }) {
        E_ASSERT(other.capacity >= other.size);
        for (sizetype index = 0; index < other.size; ++index) {
            elements[index] = opCopy(other.elements[index]);
        }
    }

    ArrayListImpl::ArrayListImpl(ArrayListImpl&& other) noexcept : elements(other.elements), size(other.size),
        capacity(other.capacity), expansionSizeFunc([](sizetype capacity) { return capacity == 0 ? capacity : 1; }) {
        other.elements = nullptr;
        other.size = E_SIZE_TYPE_MAX;
        other.capacity = E_SIZE_TYPE_MAX;
    }

    E_RET_NO_DISCARD()
    void* ArrayListImpl::getFirst0() const {
        if (size == 0) throw OperationException("The list is empty");

        return elements[0];
    }

    E_RET_NO_DISCARD()
    void* ArrayListImpl::getLast0() const {
        if (size == 0) throw OperationException("The list is empty");

        return elements[size - 1];
    }

    E_RET_NO_DISCARD()
    void* ArrayListImpl::get0(sizetype index) const {
        if (index >= size) throw IndexOutOfBoundsException(index, size);

        return elements[index];
    }

    E_RET_NO_DISCARD()
    sizetype ArrayListImpl::indexOf0(void* value, OpEqual opEqual) const {
        for (sizetype index = 0; index < size; ++index) {
            if (opEqual(elements[index], value)) {
                return index;
            }
        }

        return E_SIZE_TYPE_MAX;
    }

    void ArrayListImpl::addFirst0(void* element, OpCopy opCopy) {
        if (size == capacity) {
            capacity = expansionSizeFunc(capacity);
        }

        void** array = new void*[capacity];
        arrayCopy(array + 1, elements, size);
        elements = array;

        elements[0] = opCopy(element);
        ++size;
    }

    void ArrayListImpl::addFirst1(void* element, OpMove opMove) {
        if (size == capacity) {
            capacity = expansionSizeFunc(capacity);
        }

        void** array = new void*[capacity];
        arrayCopy(array + 1, elements, size);
        elements = array;

        elements[0] = opMove(element);
        ++size;
    }

    void ArrayListImpl::addLast0(void* element, OpCopy opCopy) {
        if (size == capacity) {
            setCapacity0(expansionSizeFunc(capacity), nullptr);
        }

        elements[size] = opCopy(element);
        ++size;
    }

    void ArrayListImpl::addLast1(void* element, OpMove opMove) {
        if (size == capacity) {
            setCapacity0(expansionSizeFunc(capacity), nullptr);
        }

        elements[size] = opMove(element);
        ++size;
    }

    void ArrayListImpl::removeFirst0(OpDestroy opDestroy) {
        if (size == 0) throw OperationException("The list is empty");

        opDestroy(elements[0]);

        void** array = new void*[capacity];
        arrayCopy(array, elements + 1, size - 1);
        delete[] elements;

        elements = array;
        --size;
    }

    void ArrayListImpl::removeLast0(OpDestroy opDestroy) {
        if (size == 0) throw OperationException("The list is empty");

        opDestroy(elements[--size]);
    }

    void ArrayListImpl::clear0(OpDestroy opDestroy) {
        if (elements == nullptr) return;

        while (size > 0) {
            opDestroy(elements[--size]);
        }
    }

    void ArrayListImpl::setCapacity0(sizetype newCapacity, OpDestroy opDestroy) {
        if (newCapacity == capacity) return;
        while (newCapacity < size) {
            removeLast0(opDestroy);
        }

        void** array = new void*[newCapacity];
        arrayCopy(array, elements, size);
        delete[] elements;

        elements = array;
        capacity = newCapacity;
    }

    ArrayListImpl::ArrayListIteratorImpl::ArrayListIteratorImpl(const ArrayListImpl* arrayList, void** init) : arrayList(arrayList), indexer(init) {}

    E_RET_NO_DISCARD()
    void* ArrayListImpl::ArrayListIteratorImpl::get0() const {
        if (isBegin0() || isEnd0()) {
            throw OperationException("The iterator has not element at the current location (begin or end)");
        }
        return *indexer;
    }

    E_RET_NO_DISCARD()
    bool ArrayListImpl::ArrayListIteratorImpl::hasNext0() const {
        return indexer != arrayList->elements + arrayList->size - 1;
    }

    E_RET_NO_DISCARD()
    bool ArrayListImpl::ArrayListIteratorImpl::hasPrev0() const {
        return indexer != arrayList->elements;
    }

    E_RET_NO_DISCARD()
    bool ArrayListImpl::ArrayListIteratorImpl::isBegin0() const {
        return indexer == arrayList->elements - 1;
    }

    E_RET_NO_DISCARD()
    bool ArrayListImpl::ArrayListIteratorImpl::isEnd0() const {
        return indexer == arrayList->elements + arrayList->size;
    }

    void ArrayListImpl::ArrayListIteratorImpl::next0() const {
        if (isEnd0()) throw OperationException("The iterator is at the end of the list");
        ++indexer;
    }

    void ArrayListImpl::ArrayListIteratorImpl::next0(sizetype count) const {
        if (indexer + count > arrayList->elements + arrayList->size) {
            throw OperationException("The iterator is at the end of the list");
        }
        indexer += count;
    }

    void ArrayListImpl::ArrayListIteratorImpl::prev0() const {
        if (isBegin0()) throw OperationException("The iterator is at the begin of the list");
        --indexer;
    }

    void ArrayListImpl::ArrayListIteratorImpl::prev0(sizetype count) const {
        if (indexer < arrayList->elements - 1 + count) {
            throw OperationException("The iterator is at the begin of the list");
        }
        indexer -= count;
    }

    void ArrayListImpl::ArrayListIteratorImpl::setBegin0() const {
        indexer = arrayList->elements - 1;
    }

    void ArrayListImpl::ArrayListIteratorImpl::setEnd0() const {
        indexer = arrayList->elements + arrayList->size;
    }
}

namespace enhanced::collections {
    sizetype ARRAY_LIST_DEFAULT_CAPACITY = 16;
}
