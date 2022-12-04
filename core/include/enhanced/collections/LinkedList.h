/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>
#include <enhanced/Iterator.h>
#include <enhanced/InitializerList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/collections/List.h>

namespace enhancedInternal::collections {
    class ENHANCED_CORE_API LinkedListImpl {
    protected:
        struct Node {
            void* value;

            Node* prev;

            Node* next;
        };

        Node* first;

        Node* last;

        sizetype size;

        using OpCopy = void* (*)(void*);
        using OpMove = void* (*)(void*);
        using OpDestroy = void (*)(void*);
        using OpEqual = bool (*)(void*, void*);

        class ENHANCED_CORE_API LinkedListIteratorImpl {
        protected:
            const LinkedListImpl* linkedList;

            mutable Node* indexer;

            LinkedListIteratorImpl(const LinkedListImpl* linkedList);

            $NoIgnoreReturn
            bool hasNext0() const;

            void next0() const;

            $NoIgnoreReturn
            void* get0() const;

            void reset0() const;
        };

        static Node*& prevNode(Node*& node);

        static Node*& nextNode(Node*& node);

        LinkedListImpl();

        LinkedListImpl(const LinkedListImpl& other, OpCopy opCopy);

        LinkedListImpl(LinkedListImpl&& other) noexcept;

        $NoIgnoreReturn
        void* getLast0() const;

        $NoIgnoreReturn
        void* getFirst0() const;

        $NoIgnoreReturn
        void* get0(sizetype index) const;

        $NoIgnoreReturn
        sizetype indexOf0(void* value, OpEqual opEqual) const;

        void addFirst0(void* element, OpCopy opCopy);

        void addFirst1(void* element, OpMove opMove);

        void addLast0(void* element, OpCopy opCopy);

        void addLast1(void* element, OpMove opMove);

        void removeFirst0(OpDestroy opDestroy);

        void removeLast0(OpDestroy opDestroy);

        void clear0(OpDestroy opDestroy);
    };
}

namespace enhanced::collections {
    template <typename Type>
    class LinkedList : public List<Type>, private enhancedInternal::collections::LinkedListImpl {
    private:
        using LinkedListImpl = enhancedInternal::collections::LinkedListImpl;

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
        class LinkedListIterator : public Iterator<Type>, private LinkedListImpl::LinkedListIteratorImpl {
        public:
            inline explicit LinkedListIterator(const LinkedList<Type>* linkedList) : LinkedListIteratorImpl(linkedList) {}

            $NoIgnoreReturn
            inline bool hasNext() const override {
                return hasNext0();
            }

            inline const Iterator<Type>* next() const override {
                next0();
                return this;
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
                return static_cast<const LinkedList<Type>*>(linkedList)->size;
            }
        };

        inline LinkedList() : LinkedListImpl() {}

        inline LinkedList(InitializerList<Type> list) : LinkedListImpl() {
            for (auto item : list) {
                addLast(util::move(item));
            }
        }

        inline LinkedList(const LinkedList<Type>& other) : LinkedListImpl(other, copy) {}

        inline LinkedList(LinkedList<Type>&& other) noexcept : LinkedListImpl(other) {}

        inline ~LinkedList() noexcept {
            clear();
        }

        $NoIgnoreReturn
        inline sizetype getSize() const override {
            return size;
        }

        $NoIgnoreReturn
        inline bool isEmpty() const override {
            return size == 0;
        }

        $NoIgnoreReturn
        inline bool contain(const Type& value) const override {
            return indexOf(value) != INVALID_SIZE;
        }

        $NoIgnoreReturn
        inline LinkedListIterator begin() const {
            return iterator();
        }

        $NoIgnoreReturn
        inline constexpr byte end() const {
            return 0;
        }

        $NoIgnoreReturn
        inline LinkedListIterator iterator() const {
            return LinkedListIterator {this};
        }

        $NoIgnoreReturn
        inline sizetype indexOf(const Type& value) const override {
            return indexOf0(util::removePtrConst(&value), equal);
        }

        $NoIgnoreReturn
        inline Type& getLast() const override {
            return *reinterpret_cast<Type*>(getLast0());
        }

        $NoIgnoreReturn
        inline Type& getFirst() const override {
            return *reinterpret_cast<Type*>(getFirst0());
        }

        $NoIgnoreReturn
        inline Type& get(sizetype index) const override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        $NoIgnoreReturn
        inline Type& operator[](sizetype index) const override {
            return *reinterpret_cast<Type*>(get0(index));
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
    };
}
