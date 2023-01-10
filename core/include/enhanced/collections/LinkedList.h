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

            [[RetNotIgnored]]
            bool isBegin0() const;

            [[RetNotIgnored]]
            bool isEnd0() const;

            [[RetNotIgnored]]
            bool hasNext0() const;

            void next0() const;

            void prev0() const;

            [[RetNotIgnored]]
            void* get0() const;

            void reset0() const;
        };

        static Node*& prevNode(Node*& node);

        static Node*& nextNode(Node*& node);

        LinkedListImpl();

        LinkedListImpl(const LinkedListImpl& other, OpCopy opCopy);

        LinkedListImpl(LinkedListImpl&& other) noexcept;

        [[RetNotIgnored]]
        void* getLast0() const;

        [[RetNotIgnored]]
        void* getFirst0() const;

        [[RetNotIgnored]]
        void* get0(sizetype index) const;

        [[RetNotIgnored]]
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

        [[RetRequiresRelease]]
        static void* copy(void* element) {
            return new Type(*reinterpret_cast<Type*>(element));
        }

        [[RetRequiresRelease]]
        static void* move(void* element) {
            return new Type(util::move(*reinterpret_cast<Type*>(element)));
        }

        static void destroy(void* element) {
            delete reinterpret_cast<Type*>(element);
        }

        [[RetNotIgnored]]
        static bool equal(void* element, void* value) {
            return *reinterpret_cast<Type*>(element) == *reinterpret_cast<Type*>(value);
        }

    public:
        class LinkedListIterator : public Iterator<Type>, private LinkedListImpl::LinkedListIteratorImpl {
        public:
            inline explicit LinkedListIterator(const LinkedList<Type>* linkedList) : LinkedListIteratorImpl(linkedList) {}

            [[RetNotIgnored]]
            inline bool isBegin() const override {
                return isBegin0();
            }

            [[RetNotIgnored]]
            inline bool isEnd() const override {
                return isEnd0();
            }

            [[RetNotIgnored]]
            inline bool hasNext() const override {
                return hasNext0();
            }

            [[ReturnSelf]]
            inline const Iterator<Type>& next() const override {
                next0();
                return *this;
            }

            [[ReturnSelf]]
            inline const Iterator<Type>& prev() const override {
                prev0();
                return *this;
            }

            [[RetNotIgnored]]
            inline Type& get() const override {
                return *reinterpret_cast<Type*>(get0());
            }

            inline void reset() const override {
                reset0();
            }

            [[RetNotIgnored]]
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

        inline E_INIT_LIST_CONSTRUCTOR(LinkedList)

        inline LinkedList(const LinkedList<Type>& other) : LinkedListImpl(other, copy) {}

        inline LinkedList(LinkedList<Type>&& other) noexcept : LinkedListImpl(other) {}

        inline ~LinkedList() noexcept {
            clear();
        }

        [[RetNotIgnored]]
        inline sizetype getSize() const override {
            return size;
        }

        [[RetNotIgnored]]
        inline bool isEmpty() const override {
            return size == 0;
        }

        [[RetNotIgnored]]
        inline bool contain(const Type& value) const override {
            return indexOf(value) != INVALID_SIZE;
        }

        [[RetNotIgnored]]
        inline LinkedListIterator begin() const {
            auto it = iterator();
            it.next();
            return it;
        }

        [[RetNotIgnored]]
        inline constexpr byte end() const {
            return 0;
        }

        [[RetNotIgnored]]
        inline LinkedListIterator iterator() const {
            return LinkedListIterator {this};
        }

        [[RetNotIgnored]]
        inline sizetype indexOf(const Type& value) const override {
            return indexOf0(util::removePtrConst(&value), equal);
        }

        [[RetNotIgnored]]
        inline Type& getLast() const override {
            return *reinterpret_cast<Type*>(getLast0());
        }

        [[RetNotIgnored]]
        inline Type& getFirst() const override {
            return *reinterpret_cast<Type*>(getFirst0());
        }

        [[RetNotIgnored]]
        inline Type& get(sizetype index) const override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        [[RetNotIgnored]]
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
