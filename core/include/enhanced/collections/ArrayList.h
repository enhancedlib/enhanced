/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>
#include <enhanced/Memory.h>
#include <enhanced/Iterator.h>
#include <enhanced/InitializerList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/collections/List.h>

namespace enhancedInternal::collections {
    class ENHANCED_CORE_API ArrayListImpl {
    protected:
        void** elements;

        sizetype size;

        sizetype capacity;

        using OpCopy = void* (*)(void*);
        using OpMove = void* (*)(void*);
        using OpDestroy = void (*)(void*);
        using OpEqual = bool (*)(void*, void*);

        using ExpSizeFallbackFunc = sizetype (*)(sizetype);

        ExpSizeFallbackFunc expSizeFallback;

        class ENHANCED_CORE_API ArrayListIteratorImpl {
        protected:
            const ArrayListImpl* arrayList;

            mutable void** indexer;

            ArrayListIteratorImpl(const ArrayListImpl* arrayList);

            $NoIgnoreReturn
            bool isBegin0() const;

            $NoIgnoreReturn
            bool isEnd0() const;

            $NoIgnoreReturn
            bool hasNext0() const;

            void next0() const;

            void prev0() const;

            $NoIgnoreReturn
            void* get0() const;

            void reset0() const;
        };

        ArrayListImpl(sizetype capacity);

        ArrayListImpl(const ArrayListImpl& other, OpCopy opCopy);

        ArrayListImpl(ArrayListImpl&& other) noexcept;

        $NoIgnoreReturn
        void* getFirst0() const;

        $NoIgnoreReturn
        void* getLast0() const;

        $NoIgnoreReturn
        void* get0(sizetype index) const;

        $NoIgnoreReturn
        sizetype indexOf0(void* value, OpEqual opEqual) const;

        void addLast0(void* element, OpCopy opCopy);

        void addLast1(void* element, OpMove opMove);

        void addFirst0(void* element, OpCopy opCopy);

        void addFirst1(void* element, OpMove opMove);

        void removeFirst0(OpDestroy opDestroy);

        void removeLast0(OpDestroy opDestroy);

        void clear0(OpDestroy opDestroy);

        void setCapacity0(sizetype newCapacity);

        void expand0();

        void expand0(sizetype expSize);

        void shrink0();

        void shrink0(sizetype shrSize, OpDestroy opDestroy);
    };
}

namespace enhanced::collections {
    template <typename Type>
    class ArrayList : public List<Type>, private enhancedInternal::collections::ArrayListImpl {
    private:
        using ArrayListImpl = enhancedInternal::collections::ArrayListImpl;

        $RetRequiresRelease
        static void* copy(void* element) {
            return new Type(*reinterpret_cast<Type*>(element));
        }

        $RetRequiresRelease
        static void* move(void* element) {
            return new Type(util::move(*reinterpret_cast<Type*>(element)));
        }

        static void destroy(void* element) {
            delete reinterpret_cast<Type*>(element);
        }

        $NoIgnoreReturn
        static bool equal(void* element, void* value) {
            return *reinterpret_cast<Type*>(element) == *reinterpret_cast<Type*>(value);
        }

    public:
        class ArrayListIterator : public Iterator<Type>, private ArrayListImpl::ArrayListIteratorImpl {
        public:
            inline explicit ArrayListIterator(const ArrayList<Type>* arrayList) : ArrayListIteratorImpl(arrayList) {}

            $NoIgnoreReturn
            inline bool isBegin() const override {
                return isBegin0();
            }

            $NoIgnoreReturn
            inline bool isEnd() const override {
                return isEnd0();
            }

            $NoIgnoreReturn
            inline bool hasNext() const override {
                return hasNext0();
            }

            $ReturnSelf
            inline const Iterator<Type>& next() const override {
                next0();
                return *this;
            }

            $ReturnSelf
            inline const Iterator<Type>& prev() const override {
                prev0();
                return *this;
            }

            $NoIgnoreReturn
            inline Type& get() const override {
                return *reinterpret_cast<Type*>(get0());
            }

            inline void reset() const override {
                reset0();
            }

            $NoIgnoreReturn
            inline sizetype count() const override {
                return static_cast<const ArrayList<Type>*>(arrayList)->size;
            }
        };

        using ExpSizeFallbackFunc = ArrayListImpl::ExpSizeFallbackFunc;

        inline ArrayList() : ArrayListImpl(ARRAY_INIT_SIZE) {}

        inline ArrayList(InitializerList<Type> list) : ArrayListImpl(list.getSize() * 2) {
            for (auto item : list) {
                addLast(util::move(item));
            }
        }

        inline E_INIT_LIST_CONSTRUCTOR(ArrayList) CTIDY_NOLINT(cppcoreguidelines-pro-type-member-init)

        inline explicit ArrayList(sizetype capacity) : ArrayListImpl(capacity) {}

        inline ArrayList(const ArrayList<Type>& other) : ArrayListImpl(other, copy) {}

        inline ArrayList(ArrayList<Type>&& other) noexcept : ArrayListImpl(util::move(other)) {}

        inline ~ArrayList() noexcept {
            clear();
            delete[] elements;
        }

        $NoIgnoreReturn
        inline sizetype getSize() const noexcept override {
            return size;
        }

        $NoIgnoreReturn
        inline bool isEmpty() const noexcept override {
            return size == 0;
        }

        $NoIgnoreReturn
        inline bool contain(const Type& value) const override {
            return indexOf(value) != INVALID_SIZE;
        }

        $NoIgnoreReturn
        inline ArrayListIterator begin() const noexcept {
            auto it = iterator();
            it.next();
            return it;
        }

        $NoIgnoreReturn
        inline constexpr byte end() const noexcept {
            return 0;
        }

        $NoIgnoreReturn
        inline ArrayListIterator iterator() const noexcept {
            return ArrayListIterator {this};
        }

        $NoIgnoreReturn
        inline sizetype indexOf(const Type& value) const override {
            return indexOf0(util::removePtrConst(&value), equal);
        }

        $NoIgnoreReturn
        inline Type& getFirst() const override {
            return *reinterpret_cast<Type*>(getFirst0());
        }

        $NoIgnoreReturn
        inline Type& getLast() const override {
            return *reinterpret_cast<Type*>(getLast0());
        }

        $NoIgnoreReturn
        inline Type& get(sizetype index) const override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        $NoIgnoreReturn
        inline sizetype getCapacity() const noexcept {
            return capacity;
        }

        $NoIgnoreReturn
        inline Type& operator[](sizetype index) const override {
            return get(index);
        }

        inline void addFirst(const Type& element) override {
            addFirst0(util::removePtrConst(&element), copy);
        }

        inline void addFirst(Type&& element) override {
            addFirst1(util::removePtrConst(&element), move);
        }

        inline void addLast(const Type& element) override {
            addLast0(util::removePtrConst(&element), copy);
        }

        inline void addLast(Type&& element) override {
            addLast1(util::removePtrConst(&element), move);
        }

        inline void push(const Type& element) override {
            return addFirst(element);
        }

        inline void push(Type&& element) override {
            return addFirst(util::move(element));
        }

        inline void add(const Type& element) override {
            addLast(element);
        }

        inline void add(Type&& element) override {
            addLast(util::move(element));
        }

        inline Type removeFirst() override {
            Type value = getFirst();
            removeLast0(destroy);
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
            removeLast0(destroy);
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

        inline void setExpSizeFallback(ExpSizeFallbackFunc expSizeFallbackFunc) noexcept {
            this->expSizeFallback = expSizeFallbackFunc;
        }

        inline void setCapacity(sizetype newCapacity) {
            setCapacity0(newCapacity);
        }

        inline void expand() {
            expand0();
        }

        inline void expand(sizetype size) {
            expand0(size);
        }

        inline void shrink() {
            shrink0();
        }

        inline void shrink(sizetype size) {
            shrink0(size, destroy);
        }
    };
}
