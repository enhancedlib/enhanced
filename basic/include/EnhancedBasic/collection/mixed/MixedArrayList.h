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
 * The authors or copyright holders be not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by This software,
 * the authors or copyright holders may provide possible solutions,
 * but it does not mean that the authors or copyright holders
 * will definitely solve the problem.
 * In no event shall the author or copyright
 * owner be liable for any claims, damages or other liabilities.
 *
 * You should see the Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#ifndef ENHANCED_BASIC_COLLECTION_MIXED_MIXED0ARRAY0LIST_H
#define ENHANCED_BASIC_COLLECTION_MIXED_MIXED0ARRAY0LIST_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/export.h"

#include "EnhancedBasic/core/Iterable.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#include "EnhancedBasic/collection/RandomAccess.h"
#include "EnhancedBasic/collection/mixed/MixedList.h"

#ifdef CXX_LANGUAGE // C++ language

namespace BasicGenericImpl {
    namespace collection {
        namespace mixed {
            class ENHANCED_BASIC_API MixedArrayListImpl {
            private:
                struct Node {
                    void *value;

                    bool dynamic;
                };

                Node *elements;

                Size length;

                Size maxCount;

            protected:
                struct GenericOperator {
                    void *(*allocate)(GenericReference);

                    void (*destroy)(void *);

                    bool (*equals)(GenericReference, GenericReference);
                };

                class ENHANCED_BASIC_API MixedArrayListIteratorImpl {
                    friend class MixedArrayListImpl;

                private:
                    const MixedArrayListImpl *mixedArrayList;

                    mutable MixedArrayListImpl::Node *indexer;

                    mutable bool isFirst;

                    const MixedArrayListImpl::Node *end;

                protected:
                    explicit MixedArrayListIteratorImpl(const MixedArrayListImpl *mixedArrayList);

                    virtual ~MixedArrayListIteratorImpl() noexcept;

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

                mutable MixedArrayListIteratorImpl *iterator;

                MixedArrayListImpl(Size maxCount, GenericOperator genericOperator);

                MixedArrayListImpl(const MixedArrayListImpl &other);

                virtual ~MixedArrayListImpl() noexcept;

                $RetNotIgnored()
                Size getLength0() const;

                $RetNotIgnored()
                bool isEmpty0() const;

                $RetNotIgnored()
                GenericReference get0(Size index) const;

                $RetNotIgnored()
                bool contain0(GenericReference value) const;

                void add0(GenericReference element);

                void addReferenced0(GenericReference element);

                void remove0();

                void expand0(Size size);

                void shrink0(Size size);
            };
        }
    }
}

namespace EnhancedBasic {
    namespace collection {
        namespace mixed {
            template <typename Type>
            class MixedArrayList final : public MixedList<Type>, public RandomAccess<Type>,
                                         private BasicGenericImpl::collection::mixed::MixedArrayListImpl {
            private:
                using MixedArrayListImpl = BasicGenericImpl::collection::mixed::MixedArrayListImpl;

                class MixedArrayListIterator : public core::Iterator<Type>,
                                               private MixedArrayListImpl::MixedArrayListIteratorImpl {
                    friend struct core::Iterable<Type>;

                public:
                    explicit inline MixedArrayListIterator(const MixedArrayList<Type> *arrayList);

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
                explicit inline MixedArrayList();

                explicit inline MixedArrayList(Size maxCount);

                inline MixedArrayList(const MixedArrayList<Type> &other);

                $RetNotIgnored()
                inline Size getLength() const override;

                $RetNotIgnored()
                inline bool isEmpty() const override;

                $RetNotIgnored()
                inline Type &get(Size index) const override;

                $RetNotIgnored()
                inline Type &operator[](Size index) const override;

                inline core::Iterator<Type> *iterator() const override;

                $RetNotIgnored()
                inline bool contain(const Type &value) const override;

                $RetRequiresRelease()
                inline MixedArrayList<Type> *copy() const override;

                inline void add(const Type &element) override;

                inline void addReferenced(const Type &element) override;

                inline Type remove() override;
            };
        } // namespace Reference
    } // namespace collection
} // namespace EnhancedBasic

#include "EnhancedBasic/collection/mixed/MixedArrayList.hpp"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_MIXED_MIXED0ARRAY0LIST_H
