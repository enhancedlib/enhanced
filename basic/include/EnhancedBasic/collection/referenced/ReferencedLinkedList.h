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

#ifndef ENHANCED_BASIC_COLLECTION_REFERENCE_REFERENCE0LINKED0LIST_H
#define ENHANCED_BASIC_COLLECTION_REFERENCE_REFERENCE0LINKED0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/export.h"

#include "EnhancedBasic/core/Iterable.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#include "EnhancedBasic/collection/referenced/ReferencedList.h"
#include "EnhancedBasic/collection/referenced/ReferencedDeque.h"

#ifdef CXX_LANGUAGE // C++ language

namespace BasicGenericImpl {
    namespace collection {
        namespace referenced {
            class ENHANCED_BASIC_API ReferencedLinkedListImpl {
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
                    bool (*equals)(GenericReference, GenericReference);
                };

                class ENHANCED_BASIC_API ReferencedLinkedListIteratorImpl {
                    friend class ReferencedLinkedListImpl;

                private:
                    const ReferencedLinkedListImpl *referencedLinkedList;

                    mutable bool isFirst;

                protected:
                    explicit ReferencedLinkedListIteratorImpl(const ReferencedLinkedListImpl *referencedLinkedList);

                    virtual ~ReferencedLinkedListIteratorImpl() noexcept;

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

                mutable ReferencedLinkedListIteratorImpl *iterator;

                explicit ReferencedLinkedListImpl(GenericOperator genericOperator);

                ReferencedLinkedListImpl(const ReferencedLinkedListImpl &other);

                virtual ~ReferencedLinkedListImpl() noexcept;

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
}

namespace EnhancedBasic {
    namespace collection {
        namespace referenced {
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
            class ReferencedLinkedList final : public Collection<Type>, public ReferencedList<Type>, public ReferencedDeque<Type>,
                                               private BasicGenericImpl::collection::referenced::ReferencedLinkedListImpl {
        #pragma warning(pop)
        #else // Non Microsoft Visual C++ Compiler
            template <typename Type>
            class ReferencedLinkedList final : public ReferencedList<Type>, public ReferencedDeque<Type>,
                                               private BasicGenericImpl::collection::referenced::ReferencedLinkedListImpl {
        #endif // COMPILER_MSVC
            private:
                using ReferencedLinkedListImpl = BasicGenericImpl::collection::referenced::ReferencedLinkedListImpl;

                class ReferencedLinkedListIterator : public core::Iterator<Type>,
                                                     private ReferencedLinkedListIteratorImpl {
                    friend struct core::Iterable<Type>;

                public:
                    explicit inline
                    ReferencedLinkedListIterator(const ReferencedLinkedList<Type> *referenceLinkedList);

                    inline bool hasNext() const override;

                    inline const core::Iterator<Type> *next() const override;

                    inline bool each() const override;

                    inline Type &get() const override;

                    inline void reset() const override;

                    inline Size count() const override;
                };

                $RetNotIgnored()
                static bool equals(GenericReference element, GenericReference value);

            public:
                inline ReferencedLinkedList();

                ReferencedLinkedList(const ReferencedLinkedList<Type> &other);

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
                inline ReferencedLinkedList<Type> *copy() const override;

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
        } // namespace referenced
    } // namespace collection
} // namespace EnhancedBasic

#include "EnhancedBasic/collection/referenced/ReferencedLinkedList.hpp"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_REFERENCE_REFERENCE0LINKED0LIST_H
