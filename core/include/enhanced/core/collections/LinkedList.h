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
#include <enhanced/core/Iterable.h>
#include <enhanced/core/Iterator.h>
#include <enhanced/core/generic.h>
#include <enhanced/core/collections/List.h>
#include <enhanced/core/collections/Deque.h>

#ifdef CXX_LANGUAGE

namespace enhanced_internal::core::collections {
    class ENHANCED_CORE_API LinkedListImpl {
    private:
        struct Node {
            void* value;

            Node* prev;

            Node* next;
        };

        Node* first;

        Node* last;

        mutable Node* indexer;

        Size size;

        static Node*& prevNode(Node*& node);

        static Node*& nextNode(Node*& node);

    protected:
        struct GenericOperator {
            void* (*allocate)(Generic&);

            void (*destroy)(void*);

            bool (*equals)(Generic&, Generic&);
        };

        class ENHANCED_CORE_API LinkedListIteratorImpl {
            friend class LinkedListImpl;

        private:
            const LinkedListImpl* linkedList;

            mutable bool isFirst;

        protected:
            explicit LinkedListIteratorImpl(const LinkedListImpl* linkedList);

            virtual ~LinkedListIteratorImpl() noexcept;

            RetCannotIgnored
            bool hasNext0() const;

            void next0() const;

            RetCannotIgnored
            bool each0() const;

            RetCannotIgnored
            Generic& get0() const;

            void reset0() const;

            RetCannotIgnored
            Size count0() const;
        };

        GenericOperator genericOperator;

        mutable LinkedListIteratorImpl* iterator;

        explicit LinkedListImpl(GenericOperator genericOperator);

        LinkedListImpl(const LinkedListImpl& other);

        virtual ~LinkedListImpl() noexcept;

        RetCannotIgnored
        Size getSize0() const;

        RetCannotIgnored
        bool isEmpty0() const;

        RetCannotIgnored
        Generic& getLast0() const;

        RetCannotIgnored
        Generic& getFirst0() const;

        RetCannotIgnored
        Generic& get0(Size index) const;

        RetCannotIgnored
        bool contain0(Generic& value) const;

        void addLast0(Generic& element);

        void removeLast0();

        void addFirst0(Generic& element);

        void removeFirst0();
    };
}

namespace enhanced::core::collections {
/*
 * When you build project with Microsoft Visual C++ Compiler,
 * If you don't explicitly extend the "Collection" class, you will see an error in compiling.
 * The compiler thinks the return type of virtual function 'copy' isn't
 * covariant with the return type the super method.
 * So the class must explicitly extend the "Collection" class.
 *
 * But when the class explicitly extend the "Collection" class,
 * The compiler show a warning (C4584), it thinks the class already extended "Collection" class.
 * So I use "#pragma warning(disable: 4584)" to disable the warning.
 */
#ifdef COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable: 4584)
    template <typename Type>
    class ENHANCED_CORE_API LinkedList final : public Collection<Type>, public List<Type>, public Deque<Type>,
                                               public enhanced_internal::core::collections::LinkedListImpl {
#pragma warning(pop)
#else
    template <typename Type>
    class ENHANCED_CORE_API LinkedList : public List<Type>, public Deque<Type>, private enhanced_internal::core::collections::LinkedListImpl {
#endif
    private:
        using LinkedListImpl = enhanced_internal::core::collections::LinkedListImpl;

        class LinkedListIterator : public Iterator<Type>, private LinkedListImpl::LinkedListIteratorImpl {
            friend struct Iterable<Type>;

        public:
            explicit inline LinkedListIterator(const LinkedList<Type>* linkedList) : LinkedListIteratorImpl(linkedList) {}

            RetCannotIgnored
            inline bool hasNext() const override {
                return hasNext0();
            }

            inline const Iterator<Type>* next() const override {
                next0();
                return this;
            }

            RetCannotIgnored
            inline bool each() const override {
                return each0();
            }

            RetCannotIgnored
            inline Type& get() const override {
                return (Type&) get0();
            }

            inline void reset() const override {
                reset0();
            }

            RetCannotIgnored
            inline Size count() const override {
                return count0();
            }
        };

        RetRequiresRelease
        static void* allocate(Generic& element) {
            return new Type((Type&) element);
        }

        static void destroy(void* element) {
            delete (Type*) element;
        }

        RetCannotIgnored
        static bool equals(Generic& element, Generic& value) {
            return ((Type&) element) == ((Type&) value);
        }

    public:
        inline LinkedList() : LinkedListImpl({allocate, destroy, equals}) {}

        inline LinkedList(const LinkedList<Type>& other) : LinkedListImpl(other) {}

        RetCannotIgnored
        inline Size getSize() const override {
            return getSize0();
        }

        RetCannotIgnored
        inline bool isEmpty() const override {
            return isEmpty0();
        }

        RetCannotIgnored
        inline bool contain(const Type& value) const override {
            return contain0((Generic&) value);
        }

        RetRequiresRelease
        inline LinkedList<Type>* copy() const override {
            return new LinkedList<Type>(*this);
        }

        RetCannotIgnored
        inline Iterator<Type>* iterator() const override {
            return List<Type>::template getIterator<LinkedListIterator>(LinkedListImpl::iterator, this);
        }

        RetCannotIgnored
        inline typename Iterable<Type>::ForeachIterator begin() const override {
            return List<Type>::begin();
        }

        RetCannotIgnored
        inline byte end() const override {
            return List<Type>::end();
        }

        RetCannotIgnored
        inline Type& getLast() const override {
            return (Type&) getLast0();
        }

        RetCannotIgnored
        inline Type& getFirst() const override {
            return (Type&) getFirst0();
        }

        RetCannotIgnored
        inline Type& get(Size index) const override {
            return (Type&) get0(index);
        }

        RetCannotIgnored
        inline Type& operator[](Size index) const override {
            return (Type&) get0(index);
        }

        inline void addLast(const Type& element) override {
            addLast0((Generic&) element);
        }

        inline Type removeLast() override{
            Type value = getLast();
            removeLast0();
            return value;
        }

        inline void addFirst(const Type& element) override {
            addFirst0((Generic&) element);
        }

        inline Type removeFirst() override {
            Type value = getFirst();
            removeFirst0();
            return value;
        }

        inline void add(const Type& element) override {
            addLast(element);
        }

        inline Type remove() override {
            return removeLast();
        }

        inline void push(const Type& element) override {
            addFirst(element);
        }

        inline Type popup() override {
            return removeFirst();
        }
    };
}

#endif
