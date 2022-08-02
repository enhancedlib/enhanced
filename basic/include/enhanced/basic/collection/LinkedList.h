/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#include "enhanced/basic/export.h"

#include "enhanced/basic/Iterable.h"
#include "enhanced/basic/Iterator.h"

#include "enhanced/basic/util/generic.h"

#include "List.h"
#include "Deque.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::generic_impl::collection {
    class ENHANCED_BASIC_API LinkedListImpl {
    private:
        struct Node {
            void* value;

            Node* next;

            Node* back;
        };

        Node* first;

        Node* last;

        mutable Node* indexer;

        Size length;

        static Node*& nextNode(Node*& node);

        static Node*& backNode(Node*& node);

    protected:
        struct GenericOperator {
            void* (*allocate)(GenericReference);

            void (*destroy)(void*);

            bool (*equals)(GenericReference, GenericReference);
        };

        class ENHANCED_BASIC_API LinkedListIteratorImpl {
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
            GenericReference get0() const;

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
        Size getLength0() const;

        RetCannotIgnored
        bool isEmpty0() const;

        RetCannotIgnored
        GenericReference getLast0() const;

        RetCannotIgnored
        GenericReference getFirst0() const;

        RetCannotIgnored
        GenericReference get0(Size index) const;

        RetCannotIgnored
        bool contain0(GenericReference value) const;

        void addLast0(GenericReference element);

        void removeLast0();

        void addFirst0(GenericReference element);

        void removeFirst0();
    };
}

namespace enhanced::basic::collection {
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
    class LinkedList final : public Collection<Type>, public List<Type>, public Deque<Type>,
                             public enhanced::basic::generic_impl::collection::LinkedListImpl {
#pragma warning(pop)
#else
    template <typename Type>
    class LinkedList : public List<Type>, public Deque<Type>,
                       private enhanced::basic::generic_impl::collection::LinkedListImpl {
#endif // COMPILER_MSVC
    private:
        using LinkedListImpl = enhanced::basic::generic_impl::collection::LinkedListImpl;

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
        static void* allocate(GenericReference element) {
            return new Type((Type&) element);
        }

        static void destroy(void* element) {
            delete (Type*) element;
        }

        RetCannotIgnored
        static bool equals(GenericReference element, GenericReference value) {
            return ((Type&) element) == ((Type&) value);
        }

    public:
        inline LinkedList() : LinkedListImpl({allocate, destroy, equals}) {}

        inline LinkedList(const LinkedList<Type>& other) : LinkedListImpl(other) {}

        RetCannotIgnored
        inline Size getLength() const override {
            return getLength0();
        }

        RetCannotIgnored
        inline bool isEmpty() const override {
            return isEmpty0();
        }

        RetCannotIgnored
        inline bool contain(const Type& value) const override {
            return contain0((GenericReference) value);
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
        inline void* end() const override {
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
            addLast0((GenericReference) element);
        }

        inline Type removeLast() override{
            Type value = getLast();
            removeLast0();
            return value;
        }

        inline void addFirst(const Type& element) override {
            addFirst0((GenericReference) element);
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

#endif // CXX_LANGUAGE
