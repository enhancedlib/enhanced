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

namespace EnhancedBasic {
    namespace collection {
        namespace mixed {
            class ENHANCED_BASIC_API MixedArrayList0 {
            private:
                struct Node {
                    GenericPointer value;

                    bool dynamic;
                };

                Node *elements;

                Size length;

                Size maxCount;

            protected:
                struct GenericsOperator {
                    GenericPointer (*allocate)(GenericReference);

                    void (*destroy)(GenericPointer);

                    bool (*equals)(GenericReference, GenericReference);
                };

                class ENHANCED_BASIC_API MixedArrayListIterator0 {
                    friend class MixedArrayList0;

                private:
                    const MixedArrayList0 *mixedArrayList;

                    mutable MixedArrayList0::Node *indexer;

                    mutable bool isFirst;

                    const MixedArrayList0::Node *end;

                protected:
                    explicit MixedArrayListIterator0(const MixedArrayList0 *mixedArrayList);

                    virtual ~MixedArrayListIterator0() noexcept;

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

                mutable MixedArrayListIterator0 *iterator;

                MixedArrayList0(Size length, GenericsOperator genericsOperator);
                
                MixedArrayList0(const MixedArrayList0 &copy);

                virtual ~MixedArrayList0() noexcept;

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

            template <typename Type>
            class MixedArrayList final : public MixedList<Type>, public RandomAccess<Type>, private MixedArrayList0 {
            private:
                class MixedArrayListIterator : public MixedArrayListIterator0, public core::Iterator<Type> {
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
                static GenericPointer allocate(GenericReference element);

                static void destroy(GenericPointer element);

                $RetNotIgnored()
                static bool equals(GenericReference element, GenericReference value);

            public:
                explicit inline MixedArrayList();

                explicit inline MixedArrayList(Size maxCount);

                inline MixedArrayList(const MixedArrayList<Type> &copy);

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

#include "EnhancedBasic/collection/mixed/MixedArrayList.tcc"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_MIXED_MIXED0ARRAY0LIST_H
