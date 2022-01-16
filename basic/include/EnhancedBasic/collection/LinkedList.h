/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
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

namespace EnhancedBasic {
    namespace collection {
        class ENHANCED_BASIC_API LinkedList0 {
        private:
            struct Node {
                GenericPointer value;

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
            struct GenericsOperator {
                GenericPointer (*allocate)(GenericReference);

                void (*destroy)(GenericPointer);

                bool (*equals)(GenericReference, GenericReference);
            };

            class ENHANCED_BASIC_API LinkedListIterator0 {
                friend class LinkedList0;

            private:
                const LinkedList0 *linkedList;

                mutable bool isFirst;

            protected:
                explicit LinkedListIterator0(const LinkedList0 *linkedList);

                virtual ~LinkedListIterator0() noexcept;

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

            GenericsOperator genericsOperator;

            mutable LinkedListIterator0 *iterator;

            explicit LinkedList0(GenericsOperator genericsOperator);

            LinkedList0(const LinkedList0 &copy);

            virtual ~LinkedList0() noexcept;

            $RetNotIgnored()
            Size getLength0() const;

            $RetNotIgnored()
            bool isEmpty0() const;

            $RetNotIgnored()
            bool contain0(GenericReference value) const;

            $RetNotIgnored()
            GenericReference getLast0() const;

            $RetNotIgnored()
            GenericReference getFirst0() const;

            $RetNotIgnored()
            GenericReference get0(Size index) const;

            void addLast0(GenericReference element);

            void removeLast0();

            void addFirst0(GenericReference element);

            void removeFirst0();
        };

    /*
     * When you build project with Microsoft Visual C++ compiler,
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
        class LinkedList final : public Collection<Type>, public List<Type>, public Deque<Type>, public LinkedList0 {
    #pragma warning(pop)
    #else // Non Microsoft Visual C++ compiler
        template <typename Type>
        class LinkedList : public List<Type>, public Deque<Type>, private LinkedList0 {
    #endif // COMPILER_MSVC
        private:
            class LinkedListIterator : public core::Iterator<Type>, private LinkedListIterator0 {
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

            static GenericPointer allocate(GenericReference element);

            static void destroy(GenericPointer element);

            static bool equals(GenericReference element, GenericReference value);

        public:
            explicit inline LinkedList();

            inline LinkedList(const LinkedList<Type> &copy) : LinkedList0(copy) {}

            $RetNotIgnored()
            inline Size getLength() const override;

            $RetNotIgnored()
            inline bool isEmpty() const override;

            $RetNotIgnored()
            inline bool contain(const Type &value) const override;

            $RetRequiresRelease()
            inline LinkedList<Type> *copy() const override;

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
            inline typename core::Iterable<Type>::ForeachIterator begin() const override;

            $RetNotIgnored()
            inline constexpr InvalidType end() const override;

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

#endif // CXX_LANGUAGE

#include "EnhancedBasic/collection/LinkedList.tcc"

#endif // !ENHANCED_BASIC_COLLECTION_LINKED0LIST_H
