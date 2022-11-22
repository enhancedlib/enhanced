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

        static func prevNode(Node*& node) -> Node*&;

        static func nextNode(Node*& node) -> Node*&;

        struct GenericOperator {
            func (*copy)(void*) -> void*;

            func (*move)(void*) -> void*;

            func (*destroy)(void*) -> void;

            func (*equals)(void*, void*) -> bool;
        };

        class ENHANCED_CORE_API LinkedListIteratorImpl {
            friend class LinkedListImpl;

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

        GenericOperator genericOperator;

        explicit LinkedListImpl(GenericOperator genericOperator);

        LinkedListImpl(const LinkedListImpl& other);

        virtual ~LinkedListImpl() noexcept;

        $(NoIgnoreReturn)
        func getLast0() const -> void*;

        $(NoIgnoreReturn)
        func getFirst0() const -> void*;

        $(NoIgnoreReturn)
        func get0(sizetype index) const -> void*;

        $(NoIgnoreReturn)
        func contain0(void* value) const -> bool;

        func addLast0(void* element) -> void;

        func addLastMoved0(void* element) -> void;

        func removeLast0() -> void;

        func addFirst0(void* element) -> void;

        func addFirstMoved0(void* element) -> void;

        func removeFirst0() -> void;

        func clear0() -> void;
    };
}

namespace enhanced::core::collections {
    template <typename Type>
    class ENHANCED_CORE_API LinkedList : public List<Type>, public Deque<Type>, private enhancedInternal::core::collections::LinkedListImpl {
    private:
        using LinkedListImpl = enhancedInternal::core::collections::LinkedListImpl;

    public:
        class ENHANCED_CORE_API LinkedListIterator : public Iterator<Type>, private LinkedListImpl::LinkedListIteratorImpl {
            friend class LinkedList<Type>;

        public:
            inline LinkedListIterator(const LinkedList<Type>* linkedList) : LinkedListIteratorImpl(linkedList) {}

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
        static func equals(void* element, void* value) -> bool {
            return *reinterpret_cast<Type*>(element) == *reinterpret_cast<Type*>(value);
        }

        LinkedListIterator iter = {this};

    public:
        inline LinkedList() : LinkedListImpl({copy, move, destroy, equals}) {}

        inline LinkedList(InitializerList<Type> list) : LinkedListImpl({copy, move, destroy, equals}) {
            for (let item : list) {
                add(item);
            }
        }

        inline LinkedList(const LinkedList<Type>& other) : LinkedListImpl(other) {}

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
            return contain0(util::removePtrConst(&value));
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
        inline func operator[](sizetype index) const -> Type& override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        inline func addLast(const Type& element) -> void override {
            addLast0(util::removePtrConst(&element));
        }

        inline func addLast(Type&& element) -> void override {
            addLastMoved0(util::removePtrConst(&element));
        }

        inline func removeLast() -> Type override {
            Type value = getLast();
            removeLast0();
            return value;
        }

        inline func addFirst(const Type& element) -> void override {
            addFirst0(util::removePtrConst(&element));
        }

        inline func addFirst(Type&& element) -> void override {
            addFirstMoved0(util::removePtrConst(&element));
        }

        inline func removeFirst() -> Type override {
            Type value = getFirst();
            removeFirst0();
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
            clear0();
        }
    };
}
