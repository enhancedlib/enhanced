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

#ifndef ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_H
#define ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/export.h"

#include "EnhancedBasic/core/Iterable.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#include "EnhancedBasic/collection/mixed/MixedList.h"
#include "EnhancedBasic/collection/mixed/MixedDeque.h"

#ifdef CXX_LANGUAGE // C++ language

namespace BasicGenericImpl {
    namespace collection {
        namespace mixed {
            class ENHANCED_BASIC_API MixedLinkedListImpl {
            private:
                struct Node {
                    void *value;

                    bool dynamic;

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

                class ENHANCED_BASIC_API MixedLinkedListIteratorImpl {
                    friend class MixedLinkedListImpl;

                private:
                    const MixedLinkedListImpl *mixedLinkedList;

                    mutable bool isFirst;

                protected:
                    explicit MixedLinkedListIteratorImpl(const MixedLinkedListImpl *mixedLinkedList);

                    virtual ~MixedLinkedListIteratorImpl() noexcept;

                    $RetNotIgnored()
                    bool hasNext0() const;

                    void next0() const;

                    $RetNotIgnored()
                    bool each0() const;

                    $RetNotIgnored()
                    GenericReference get0() const;

                    void reset0() const;

                    Size count0() const;
                };

                GenericOperator genericOperator;

                mutable MixedLinkedListIteratorImpl *iterator;

                explicit MixedLinkedListImpl(GenericOperator genericOperator);

                virtual ~MixedLinkedListImpl() noexcept;

                MixedLinkedListImpl(const MixedLinkedListImpl &other);

                Size getLength0() const;

                $RetNotIgnored()
                bool isEmpty0() const;

                GenericReference getLast0() const;

                GenericReference getFirst0() const;

                GenericReference get0(Size index) const;

                $RetNotIgnored()
                bool contain0(GenericReference value) const;

                void addLast0(GenericReference element);

                void addLastReferenced0(GenericReference element);

                void removeLast0();

                void addFirst0(GenericReference element);

                void addFirstReferenced0(GenericReference element);

                void removeFirst0();
            };
        }
    }
}

namespace EnhancedBasic {
    namespace collection {
        namespace mixed {
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
                                          public BasicGenericImpl::collection::mixed::MixedLinkedListImpl {
        #pragma warning(pop)
        #else // Non Microsoft Visual C++ Compiler
            template <typename Type>
            class MixedLinkedList final : public MixedList<Type>, public MixedDeque<Type>,
                                          private BasicGenericImpl::collection::mixed::MixedLinkedListImpl {
        #endif // COMPILER_MSVC
            private:
                using MixedLinkedListImpl = BasicGenericImpl::collection::mixed::MixedLinkedListImpl;

                class MixedLinkedListIterator : public core::Iterator<Type>, private MixedLinkedListIteratorImpl {
                    friend struct core::Iterable<Type>;

                public:
                    explicit inline MixedLinkedListIterator(const MixedLinkedList<Type> *mixedLinkedList);

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
                inline MixedLinkedList();

                inline MixedLinkedList(const MixedLinkedList<Type> &other);

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

                inline core::Iterator<Type> *iterator() const override;

                $RetNotIgnored()
                inline bool contain(const Type &value) const override;

                $RetRequiresRelease()
                inline MixedLinkedList<Type> *copy() const override;

                $RetNotIgnored()
                inline typename core::Iterable<Type>::ForeachIterator begin() const override;

                $RetNotIgnored()
                inline constexpr UnusedType end() const override;

                inline void addLast(const Type &element) override;

                inline void addLastReferenced(const Type &element) override;

                inline Type removeLast() override;

                inline void addFirst(const Type &element) override;

                inline void addFirstReferenced(const Type &element) override;

                inline Type removeFirst() override;

                inline void add(const Type &element) override;

                inline void addReferenced(const Type &element) override;

                inline Type remove() override;

                inline void push(const Type &element) override;

                inline void pushReferenced(const Type &element) override;

                inline Type popup() override;
            };
        } // namespace mixed
    } // namespace collection
} // namespace EnhancedBasic

#include "EnhancedBasic/collection/mixed/MixedLinkedList.hpp"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_MIXED_MIXED0LINKED0LIST_H
