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

#include "MixedList.h"
#include "MixedDeque.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::generic_impl::collection::mixed {
    class ENHANCED_BASIC_API MixedLinkedListImpl {
    private:
        struct Node {
            void* value;

            bool dynamic;

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

        class ENHANCED_BASIC_API MixedLinkedListIteratorImpl {
            friend class MixedLinkedListImpl;

        private:
            const MixedLinkedListImpl* mixedLinkedList;

            mutable bool isFirst;

        protected:
            explicit MixedLinkedListIteratorImpl(const MixedLinkedListImpl* mixedLinkedList);

            virtual ~MixedLinkedListIteratorImpl() noexcept;

            RetCannotIgnored
            bool hasNext0() const;

            void next0() const;

            RetCannotIgnored
            bool each0() const;

            RetCannotIgnored
            GenericReference get0() const;

            void reset0() const;

            Size count0() const;
        };

        GenericOperator genericOperator;

        mutable MixedLinkedListIteratorImpl* iterator;

        explicit MixedLinkedListImpl(GenericOperator genericOperator);

        virtual ~MixedLinkedListImpl() noexcept;

        MixedLinkedListImpl(const MixedLinkedListImpl& other);

        Size getLength0() const;

        RetCannotIgnored
        bool isEmpty0() const;

        GenericReference getLast0() const;

        GenericReference getFirst0() const;

        GenericReference get0(Size index) const;

        RetCannotIgnored
        bool contain0(GenericReference value) const;

        void addLast0(GenericReference element);

        void addLastReference0(GenericReference element);

        void removeLast0();

        void addFirst0(GenericReference element);

        void addFirstReference0(GenericReference element);

        void removeFirst0();
    };
}

namespace enhanced::basic::collection::mixed {
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
    class MixedLinkedList final : public Collection<Type>, public MixedDeque<Type>, public MixedList<Type>,
                                  private enhanced::basic::generic_impl::collection::mixed::MixedLinkedListImpl {
#pragma warning(pop)
#else
    template <typename Type>
    class MixedLinkedList final : public MixedList<Type>, public MixedDeque<Type>, private enhanced::basic::generic_impl::collection::mixed::MixedLinkedListImpl {
#endif // COMPILER_MSVC
    private:
        using MixedLinkedListImpl = enhanced::basic::generic_impl::collection::mixed::MixedLinkedListImpl;

        class MixedLinkedListIterator : public Iterator<Type>, private MixedLinkedListImpl::MixedLinkedListIteratorImpl {
            friend struct Iterable<Type>;

        public:
            explicit inline MixedLinkedListIterator(const MixedLinkedList<Type>* mixedLinkedList) : MixedLinkedListIteratorImpl(mixedLinkedList) {}

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
            return new Type(reinterpret_cast<Type&>(element));
        }

        static void destroy(void* element) {
            delete (Type&) element;
        }

        RetCannotIgnored
        static bool equals(GenericReference element, GenericReference value) {
            return ((Type&) element) == ((Type&) (value));
        }

    public:
        inline MixedLinkedList() : MixedLinkedListImpl({allocate, destroy, equals}) {}

        inline MixedLinkedList(const MixedLinkedList<Type>& other) : MixedLinkedListImpl(other) {}

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
        inline MixedLinkedList<Type>* copy() const override {
            return new MixedLinkedList<Type>(*this);
        }

        inline Iterator<Type>* iterator() const override {
            return List<Type>::template getIterator<MixedLinkedListIterator>(MixedLinkedListImpl::iterator, this);
        }

        RetCannotIgnored
        inline typename Iterable<Type>::ForeachIterator begin() const override {
            return MixedList<Type>::begin();
        }

        RetCannotIgnored
        inline void* end() const override {
            return MixedList<Type>::end();
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

        inline void addLastReference(const Type& element) override {
            addLastReference0((GenericReference) element);
        }

        inline Type removeLast() override {
            Type value = getLast();
            removeLast0();
            return value;
        }

        inline void addFirst(const Type& element) override {
            addFirst0((GenericReference) element);
        }

        inline void addFirstReference(const Type& element) override {
            addFirstReference0((GenericReference) element);
        }

        inline Type removeFirst() override {
            Type value = getFirst();
            removeFirst0();
            return value;
        }

        inline void add(const Type& element) override {
            addLast(element);
        }

        inline void addReference(const Type& element) override {
            addLastReference(element);
        }

        inline Type remove() override {
            return removeLast();
        }

        inline void push(const Type& element) override {
            addFirst(element);
        }

        inline void pushReference(const Type& element) override {
            addFirstReference(element);
        }

        inline Type popup() override {
            return removeFirst();
        }
    };
}

#endif // CXX_LANGUAGE
