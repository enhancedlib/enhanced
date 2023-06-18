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

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>
#include <enhanced/Traits.h>
#include <enhanced/Memory.h>
#include <enhanced/Iterator.h>
#include <enhanced/Iterable.h>
#include <enhanced/InitializerList.h>
#include <enhanced/collections/List.h>

namespace enhancedInternal::collections {
    class E_CORE_API ArrayListImpl {
        E_CLASS(ArrayListImpl)

    E_CLASS_BODY
    protected:
        void** elements;

        enhanced::sizetype size;

        enhanced::sizetype capacity;

        using OpCopy = void* (*)(void*);
        using OpMove = void* (*)(void*);
        using OpDestroy = void (*)(void*);
        using OpEqual = bool (*)(void*, void*);

        using ExpansionSizeFunc = enhanced::sizetype (*)(enhanced::sizetype);

        ExpansionSizeFunc expansionSizeFunc;

        class E_CORE_API ArrayListIteratorImpl {
            E_CLASS(ArrayListIteratorImpl)

        E_CLASS_BODY
        protected:
            const ArrayListImpl* arrayList;

            mutable void** indexer;

            ArrayListIteratorImpl(const ArrayListImpl* arrayList, void** init);

            E_RET_NO_DISCARD()
            void* get0() const;

            E_RET_NO_DISCARD()
            bool hasNext0() const;

            E_RET_NO_DISCARD()
            bool hasPrev0() const;

            E_RET_NO_DISCARD()
            bool isBegin0() const;

            E_RET_NO_DISCARD()
            bool isEnd0() const;

            void next0() const;

            void next0(enhanced::sizetype count) const;

            void prev0() const;

            void prev0(enhanced::sizetype count) const;

            void setBegin0() const;

            void setEnd0() const;
        };

        ArrayListImpl(enhanced::sizetype capacity);

        ArrayListImpl(const ArrayListImpl& other, OpCopy opCopy);

        ArrayListImpl(ArrayListImpl&& other) noexcept;

        E_RET_NO_DISCARD()
        void* getFirst0() const;

        E_RET_NO_DISCARD()
        void* getLast0() const;

        E_RET_NO_DISCARD()
        void* get0(enhanced::sizetype index) const;

        E_RET_NO_DISCARD()
        enhanced::sizetype indexOf0(void* value, OpEqual opEqual) const;

        void addLast0(void* element, OpCopy opCopy);

        void addLast1(void* element, OpMove opMove);

        void addFirst0(void* element, OpCopy opCopy);

        void addFirst1(void* element, OpMove opMove);

        void removeFirst0(OpDestroy opDestroy);

        void removeLast0(OpDestroy opDestroy);

        void clear0(OpDestroy opDestroy);

        void setCapacity0(enhanced::sizetype newCapacity, OpDestroy opDestroy);
    };
}

namespace enhanced::collections {
    extern E_CORE_API sizetype ARRAY_LIST_DEFAULT_CAPACITY; // Default value: 16

    template <typename Type>
    class ArrayList : public List<Type>, public Iterable<ArrayList<Type>>, private enhancedInternal::collections::ArrayListImpl {
        E_CLASS(ArrayList)

    E_CLASS_BODY
    private:
        using ArrayListImpl = enhancedInternal::collections::ArrayListImpl;

        E_RET_NEED_RELEASE()
        static void* copy(void* element) {
            return new Type(*reinterpret_cast<Type*>(element));
        }

        E_RET_NEED_RELEASE()
        static void* move(void* element) {
            return new Type(traits::move(*reinterpret_cast<Type*>(element)));
        }

        static void destroy(void* element) {
            delete reinterpret_cast<Type*>(element);
        }

        E_RET_NO_DISCARD()
        static bool equal(void* element, void* value) {
            return *reinterpret_cast<Type*>(element) == *reinterpret_cast<Type*>(value);
        }

    public:
        class ArrayListIterator : public Iterator<Type>, private ArrayListImpl::ArrayListIteratorImpl {
            E_CLASS(ArrayListIterator)

        E_CLASS_BODY
        public:
            inline explicit ArrayListIterator(const ArrayList<Type>* arrayList, void** init) : ArrayListIteratorImpl(arrayList, init) {}

            E_RET_NO_DISCARD()
            inline Type& get() const override {
                return *reinterpret_cast<Type*>(get0());
            }

            E_RET_NO_DISCARD()
            inline sizetype count() const override {
                return static_cast<const ArrayList<Type>*>(arrayList)->size;
            }

            E_RET_NO_DISCARD()
            inline bool isBegin() const override {
                return isBegin0();
            }

            E_RET_NO_DISCARD()
            inline bool isEnd() const override {
                return isEnd0();
            }

            E_RET_NO_DISCARD()
            inline bool hasNext() const override {
                return hasNext0();
            }

            E_RET_NO_DISCARD()
            inline bool hasPrev() const override {
                return hasPrev0();
            }

            E_RETURN_SELF()
            inline const Iterator<Type>& prev() const override {
                prev0();
                return *this;
            }

            E_RETURN_SELF()
            inline const Iterator<Type>& prev(sizetype count) const override {
                prev0(count);
                return *this;
            }

            E_RETURN_SELF()
            inline const Iterator<Type>& next() const override {
                next0();
                return *this;
            }

            E_RETURN_SELF()
            inline const Iterator<Type>& next(sizetype count) const override {
                next0(count);
                return *this;
            }

            E_RETURN_SELF()
            inline const Iterator<Type>& setBegin() const override {
                setBegin0();
                return *this;
            }

            E_RETURN_SELF()
            inline const Iterator<Type>& setEnd() const override {
                setEnd0();
                return *this;
            }
        };

        using ExpansionSizeFunc = ArrayListImpl::ExpansionSizeFunc;

        inline ArrayList() : ArrayListImpl(ARRAY_LIST_DEFAULT_CAPACITY) {}

        E_INIT_LIST_CONSTRUCTOR(ArrayList, Type)
        inline ArrayList(InitializerList<Type> list) : ArrayListImpl(list.getSize() + 1) {
            for (auto item : list) {
                addLast(traits::move(item));
            }
        }

        inline explicit ArrayList(sizetype capacity) : ArrayListImpl(capacity) {}

        inline ArrayList(const ArrayList<Type>& other) : ArrayListImpl(other, copy) {}

        inline ArrayList(ArrayList<Type>&& other) noexcept : ArrayListImpl(traits::move(other)) {}

        inline ~ArrayList() noexcept {
            clear();
            delete[] elements;
        }

        E_RET_NO_DISCARD()
        inline sizetype getSize() const noexcept override {
            return size;
        }

        E_RET_NO_DISCARD()
        inline bool isEmpty() const noexcept override {
            return size == 0;
        }

        E_RET_NO_DISCARD()
        inline bool contain(const Type& value) const override {
            return indexOf(value) != E_SIZE_TYPE_MAX;
        }

        E_RET_NO_DISCARD()
        inline ArrayListIterator iterator() const noexcept {
            return ArrayListIterator {this, elements - 1};
        }

        E_RET_NO_DISCARD()
        inline ForwardIterator<ArrayListIterator> forwardIterator() const noexcept {
            return ArrayListIterator {this, elements - 1};
        }

        E_RET_NO_DISCARD()
        inline ReverseIterator<ArrayListIterator> reverseIterator() const noexcept {
            return ArrayListIterator {this, elements + size};
        }

        E_RET_NO_DISCARD()
        inline ReversedIterable<ArrayList<Type>> reversed() const noexcept {
            return ReversedIterable<ArrayList<Type>>(*this);
        }

        E_RET_NO_DISCARD()
        inline sizetype indexOf(const Type& value) const override {
            return indexOf0(removePtrConst(&value), equal);
        }

        E_RET_NO_DISCARD()
        inline Type& getFirst() const override {
            return *reinterpret_cast<Type*>(getFirst0());
        }

        E_RET_NO_DISCARD()
        inline Type& getLast() const override {
            return *reinterpret_cast<Type*>(getLast0());
        }

        E_RET_NO_DISCARD()
        inline Type& get(sizetype index) const override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        E_RET_NO_DISCARD()
        inline sizetype getCapacity() const noexcept {
            return capacity;
        }

        E_RET_NO_DISCARD()
        inline Type& operator[](sizetype index) const override {
            return get(index);
        }

        inline void addFirst(const Type& element) override {
            addFirst0(removePtrConst(&element), copy);
        }

        inline void addFirst(Type&& element) override {
            addFirst1(removePtrConst(&element), move);
        }

        inline void addLast(const Type& element) override {
            addLast0(removePtrConst(&element), copy);
        }

        inline void addLast(Type&& element) override {
            addLast1(removePtrConst(&element), move);
        }

        inline void push(const Type& element) override {
            return addFirst(element);
        }

        inline void push(Type&& element) override {
            return addFirst(traits::move(element));
        }

        inline void add(const Type& element) override {
            addLast(element);
        }

        inline void add(Type&& element) override {
            addLast(traits::move(element));
        }

        inline Type removeFirst() override {
            Type value = getFirst();
            removeFirst0(destroy);
            return value;
        }

        inline Type removeLast() override {
            Type value = getLast();
            removeLast0(destroy);
            return value;
        }

        inline Type popup() override {
            return removeFirst();
        }

        inline Type remove() override {
            return removeLast();
        }

        inline bool removeFirstIf() override {
            if (size == 0) return false;
            removeFirst0(destroy);
            return true;
        }

        inline bool removeLastIf() override {
            if (size == 0) return false;
            removeLast0(destroy);
            return true;
        }

        inline bool popupIf() override {
            return removeFirstIf();
        }

        inline bool removeIf() override {
            return removeLastIf();
        }

        inline void clear() override {
            clear0(destroy);
        }

        inline void setExpansionSize(ExpansionSizeFunc expansionSizeFunc) noexcept {
            this->expansionSizeFunc = expansionSizeFunc;
        }

        inline void setCapacity(sizetype newCapacity) {
            setCapacity0(newCapacity, destroy);
        }

        inline void reserve(sizetype newCapacity) {
            if (newCapacity < capacity) return;
            setCapacity(newCapacity);
        }

        inline void expand() {
            setCapacity(expansionSizeFunc(capacity));
        }

        inline void expand(sizetype size) {
            setCapacity(capacity + size);
        }

        inline void shrink() {
            setCapacity(size);
        }

        inline void shrink(sizetype size) {
            setCapacity(capacity - size);
        }
    };
}
