/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#ifndef ENHANCED_BASIC_COLLECTION_LINKED0LIST_H
#define ENHANCED_BASIC_COLLECTION_LINKED0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/export.h"

#include "EnhancedBasic/core/Iterable.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#include "EnhancedBasic/collection/List.h"
#include "EnhancedBasic/collection/Deque.h"

#ifdef CXX_LANGUAGE // C++ language

namespace BasicGenericImpl {
    namespace collection {
        class ENHANCED_BASIC_API LinkedListImpl {
        private:
            struct Node {
                void *value;

                Node *next;

                Node *back;
            };

            Node *first;

            Node *last;

            mutable Node *indexer;

            Size length;

            static Node *&nextNode(Node *&node);

            static Node *&backNode(Node *&node);

        protected:
            struct GenericOperator {
                void *(*allocate)(GenericReference);

                void (*destroy)(void *);

                bool (*equals)(GenericReference, GenericReference);
            };

            class ENHANCED_BASIC_API LinkedListIteratorImpl {
                friend class LinkedListImpl;

            private:
                const LinkedListImpl *linkedList;

                mutable bool isFirst;

            protected:
                explicit LinkedListIteratorImpl(const LinkedListImpl *linkedList);

                virtual ~LinkedListIteratorImpl() noexcept;

                $RetNotIgnored()
                bool hasNext0() const;

                void next0() const;

                $RetNotIgnored()
                bool each0() const;

                $RetNotIgnored()
                GenericReference get0() const;

                void reset0() const;

                $RetNotIgnored()
                Size count0() const;
            };

            GenericOperator genericOperator;

            mutable LinkedListIteratorImpl *iterator;

            explicit LinkedListImpl(GenericOperator genericOperator);

            LinkedListImpl(const LinkedListImpl &other);

            virtual ~LinkedListImpl() noexcept;

            $RetNotIgnored()
            Size getLength0() const;

            $RetNotIgnored()
            bool isEmpty0() const;

            $RetNotIgnored()
            GenericReference getLast0() const;

            $RetNotIgnored()
            GenericReference getFirst0() const;

            $RetNotIgnored()
            GenericReference get0(Size index) const;

            $RetNotIgnored()
            bool contain0(GenericReference value) const;

            void addLast0(GenericReference element);

            void removeLast0();

            void addFirst0(GenericReference element);

            void removeFirst0();
        };
    }
}

namespace EnhancedBasic {
    namespace collection {
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
                                 public BasicGenericImpl::collection::LinkedListImpl {
    #pragma warning(pop)
    #else // Non Microsoft Visual C++ Compiler
        template <typename Type>
        class LinkedList : public List<Type>, public Deque<Type>,
                           private BasicGenericImpl::collection::LinkedListImpl {
    #endif // COMPILER_MSVC
        private:
            using LinkedListImpl = BasicGenericImpl::collection::LinkedListImpl;

            class LinkedListIterator : public core::Iterator<Type>, private LinkedListImpl::LinkedListIteratorImpl {
                friend struct core::Iterable<Type>;

            public:
                explicit inline LinkedListIterator(const LinkedList<Type> *linkedList);

                $RetNotIgnored()
                inline bool hasNext() const override;

                inline const core::Iterator<Type> *next() const override;

                $RetNotIgnored()
                inline bool each() const override;

                $RetNotIgnored()
                inline Type &get() const override;

                inline void reset() const override;

                $RetNotIgnored()
                inline Size count() const override;
            };

            $RetRequiresRelease()
            static void *allocate(GenericReference element);

            static void destroy(void *element);

            $RetNotIgnored()
            static bool equals(GenericReference element, GenericReference value);

        public:
            explicit inline LinkedList();

            inline LinkedList(const LinkedList<Type> &other) : LinkedListImpl(other) {}

            $RetNotIgnored()
            inline Size getLength() const override;

            $RetNotIgnored()
            inline bool isEmpty() const override;

            $RetNotIgnored()
            inline Type &getLast() const override;

            $RetNotIgnored()
            inline Type &getFirst() const override;

            $RetNotIgnored()
            inline Type &get(Size index) const override;

            $RetNotIgnored()
            inline Type &operator[](Size index) const override;

            $RetNotIgnored()
            inline core::Iterator<Type> *iterator() const override;

            $RetNotIgnored()
            inline bool contain(const Type &value) const override;

            $RetRequiresRelease()
            inline LinkedList<Type> *copy() const override;

            $RetNotIgnored()
            inline typename core::Iterable<Type>::ForeachIterator begin() const override;

            $RetNotIgnored()
            inline UnusedType end() const override;

            inline void addLast(const Type &element) override;

            inline Type removeLast() override;

            inline void addFirst(const Type &element) override;

            inline Type removeFirst() override;

            inline void add(const Type &element) override;

            inline Type remove() override;

            inline void push(const Type &element) override;

            inline Type popup() override;
        };
    } // namespace collection
} // namespace EnhancedBasic

#include "EnhancedBasic/collection/LinkedList.hpp"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_LINKED0LIST_H
