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

#include <enhanced/core/defines.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/Iterable.h>
#include <enhanced/core/Iterator.h>
#include <enhanced/core/InitializerList.h>
#include <enhanced/core/collections/List.h>
#include <enhanced/core/collections/Deque.h>
#include <enhanced/core/util/traits.h>

namespace enhancedInternal::core::collections {
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

        using OpCopy = func (*)(void*) -> void*;
        using OpMove = func (*)(void*) -> void*;
        using OpDestroy = func (*)(void*) -> void;
        using OpEqual = func (*)(void*, void*) -> bool;

        static func prevNode(Node*& node) -> Node*&;

        static func nextNode(Node*& node) -> Node*&;

        class ENHANCED_CORE_API LinkedListIteratorImpl {
        protected:
            const LinkedListImpl* linkedList;

            mutable Node* indexer;

            LinkedListIteratorImpl(const LinkedListImpl* linkedList);

            $(NoIgnoreReturn)
            func hasNext0() const -> bool;

            func next0() const -> void;

            $(NoIgnoreReturn)
            func get0() const -> void*;

            func reset0() const -> void;
        };

        LinkedListImpl();

        LinkedListImpl(const LinkedListImpl& other, OpCopy opCopy);

        LinkedListImpl(LinkedListImpl&& other) noexcept;

        func destruct0(OpDestroy opDestroy) noexcept -> void;

        $(NoIgnoreReturn)
        func getLast0() const -> void*;

        $(NoIgnoreReturn)
        func getFirst0() const -> void*;

        $(NoIgnoreReturn)
        func get0(sizetype index) const -> void*;

        $(NoIgnoreReturn)
        func indexOf0(void* value, OpEqual opEqual) const -> sizetype;

        func addLast0(void* element, OpCopy opCopy) -> void;

        func addLastMoved0(void* element, OpMove opMove) -> void;

        func removeLast0(OpDestroy opDestroy) -> void;

        func addFirst0(void* element, OpCopy opCopy) -> void;

        func addFirstMoved0(void* element, OpMove opMove) -> void;

        func removeFirst0(OpDestroy opDestroy) -> void;

        func clear0(OpDestroy opDestroy) -> void;
    };
}

namespace enhanced::core::collections {
    template <typename Type>
    class LinkedList : public List<Type>, public Deque<Type>, private enhancedInternal::core::collections::LinkedListImpl {
    private:
        using LinkedListImpl = enhancedInternal::core::collections::LinkedListImpl;

    public:
        class LinkedListIterator : public Iterator<Type>, private LinkedListImpl::LinkedListIteratorImpl {
        public:
            inline explicit LinkedListIterator(const LinkedList<Type>* linkedList) : LinkedListIteratorImpl(linkedList) {}

            $(NoIgnoreReturn)
            inline func hasNext() const -> bool override {
                return hasNext0();
            }

            inline func next() const -> const Iterator<Type>* override {
                next0();
                return this;
            }

            $(NoIgnoreReturn)
            inline func get() const -> Type& override {
                return *reinterpret_cast<Type*>(get0());
            }

            inline func reset() const -> void override {
                reset0();
            }

            $(NoIgnoreReturn)
            inline func count() const -> sizetype override {
                return static_cast<const LinkedList<Type>*>(linkedList)->size;
            }
        };

    private:
        $(RetRequiresRelease)
        static func copy(void* element) -> void* {
            return new Type(*reinterpret_cast<Type*>(element));
        }

        $(RetRequiresRelease)
        static func move(void* element) -> void* {
            return new Type(util::move(*reinterpret_cast<Type*>(element)));
        }

        static func destroy(void* element) -> void {
            delete reinterpret_cast<Type*>(element);
        }

        $(NoIgnoreReturn)
        static func equal(void* element, void* value) -> bool {
            return *reinterpret_cast<Type*>(element) == *reinterpret_cast<Type*>(value);
        }

        LinkedListIterator iter {this};

    public:
        inline LinkedList() : LinkedListImpl() {}

        inline LinkedList(InitializerList<Type> list) : LinkedListImpl() {
            for (let item : list) {
                add(item);
            }
        }

        inline LinkedList(const LinkedList<Type>& other) : LinkedListImpl(other, copy) {}

        inline LinkedList(LinkedList<Type>&& other) noexcept : LinkedListImpl(other) {}

        inline ~LinkedList() noexcept {
            destruct0(destroy);
        }

        $(NoIgnoreReturn)
        inline func getSize() const -> sizetype override {
            return this->size;
        }

        $(NoIgnoreReturn)
        inline func isEmpty() const -> bool override {
            return this->size == 0;
        }

        $(NoIgnoreReturn)
        inline func contain(const Type& value) const -> bool override {
            return indexOf(value) != INVALID_SIZE;
        }

        $(NoIgnoreReturn)
        inline func iterator() const -> const Iterator<Type>& override {
            iter.reset();
            return iter;
        }

        $(NoIgnoreReturn)
        inline func begin() const -> typename Iterable<Type>::ForeachIterator override {
            return List<Type>::begin();
        }

        $(NoIgnoreReturn)
        inline constexpr func end() const -> byte override {
            return List<Type>::end();
        }

        $(NoIgnoreReturn)
        inline func getLast() const -> Type& override {
            return *reinterpret_cast<Type*>(getLast0());
        }

        $(NoIgnoreReturn)
        inline func getFirst() const -> Type& override {
            return *reinterpret_cast<Type*>(getFirst0());
        }

        $(NoIgnoreReturn)
        inline func get(sizetype index) const -> Type& override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        $(NoIgnoreReturn)
        inline func indexOf(const Type& value) const -> sizetype override {
            return indexOf0(util::removePtrConst(&value), equal);
        }

        $(NoIgnoreReturn)
        inline func operator[](sizetype index) const -> Type& override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        inline func addLast(const Type& element) -> void override {
            addLast0(util::removePtrConst(&element), copy);
        }

        inline func addLast(Type&& element) -> void override {
            addLastMoved0(util::removePtrConst(&element), move);
        }

        inline func removeLast() -> Type override {
            Type value = getLast();
            removeLast0(destroy);
            return value;
        }

        inline func addFirst(const Type& element) -> void override {
            addFirst0(util::removePtrConst(&element), copy);
        }

        inline func addFirst(Type&& element) -> void override {
            addFirstMoved0(util::removePtrConst(&element), move);
        }

        inline func removeFirst() -> Type override {
            Type value = getFirst();
            removeFirst0(destroy);
            return value;
        }

        inline func add(const Type& element) -> void override {
            addLast(element);
        }

        inline func add(Type&& element) -> void override {
            addLast(element);
        }

        inline func remove() -> Type override {
            return removeLast();
        }

        inline func push(const Type& element) -> void override {
            addFirst(element);
        }

        inline func push(Type&& element) -> void override {
            addFirst(element);
        }

        inline func popup() -> Type override {
            return removeFirst();
        }

        func clear() -> void override {
            clear0(destroy);
        }
    };
}
