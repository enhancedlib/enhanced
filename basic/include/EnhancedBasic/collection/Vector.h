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

#ifndef ENHANCED_BASIC_COLLECTION_VECTOR_H
#define ENHANCED_BASIC_COLLECTION_VECTOR_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/export.h"

#include "EnhancedBasic/core/Iterable.h"
#include "EnhancedBasic/core/Iterator.h"

#include "EnhancedBasic/generic/Generic.h"

#include "EnhancedBasic/collection/List.h"
#include "EnhancedBasic/collection/RandomAccess.h"

#ifdef CXX_LANGUAGE // C++ language

namespace BasicGenericImpl {
    namespace collection {
        class ENHANCED_BASIC_API VectorImpl {
        private:
            Size maxCount;

            void *elements;

            Size length;

        protected:
            struct GenericOperator {
                void *(*allocateArray)(const Size size);

                void (*copyArray)(void *destination, void *source, const Size size);

                void (*moveArray)(void *destination, void *source, const Size size);

                void *(*index)(void *elements, const Size index);

                GenericReference (*getElement)(void *elements, const Size index);

                void (*setElement)(void *elements, const Size index, GenericReference value);

                bool (*equals)(GenericReference element, GenericReference value);
            };

            class ENHANCED_BASIC_API VectorIteratorImpl {
                friend class VectorImpl;

            private:
                const VectorImpl *vector;

                mutable void *indexer;

                mutable bool isFirst;

                void *end;

            protected:
                explicit VectorIteratorImpl(const VectorImpl *vector);

                virtual ~VectorIteratorImpl() noexcept;

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

            mutable VectorIteratorImpl *iterator;

            VectorImpl(Size maxCount, GenericOperator genericOperator);

            VectorImpl(const VectorImpl &other);

            virtual ~VectorImpl() noexcept;

            $RetNotIgnored()
            Size getLength0() const;

            $RetNotIgnored()
            bool isEmpty0() const;

            $RetNotIgnored()
            GenericReference get0(Size index) const;

            $RetNotIgnored()
            bool contain0(GenericReference value) const;

            void add0(GenericReference element);

            void remove0();

            void expand0(Size size);

            void shrink0(Size size);
        };
    }
}

namespace EnhancedBasic {
    namespace collection {
        template <typename Type>
        class Vector final : public List<Type>, public RandomAccess<Type>,
                             private BasicGenericImpl::collection::VectorImpl {
        private:
            using VectorImpl = BasicGenericImpl::collection::VectorImpl;

            class VectorIterator : public core::Iterator<Type>, private VectorImpl::VectorIteratorImpl {
                friend struct core::Iterable<Type>;

            public:
                explicit inline VectorIterator(const Vector<Type> *vector);

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
            static void *allocateArray(Size size);

            static void copyArray(void *destination, void *source, const Size size);

            static void moveArray(void *destination, void *source, Size size);

            static GenericReference getElement(void *elements, Size index);

            static void *index(void *elements, Size index);

            static void setElement(void *elements, Size index, GenericReference value);

            $RetNotIgnored()
            static bool equals(GenericReference element, GenericReference value);

        public:
            explicit inline Vector();

            explicit inline Vector(Size maxCount);

            inline Vector(const Vector<Type> &other);

            $RetNotIgnored()
            inline Size getLength() const override;

            $RetNotIgnored()
            inline bool isEmpty() const override;

            $RetNotIgnored()
            inline Type &get(Size index) const override;

            $RetNotIgnored()
            inline Type &operator[](Size index) const override;

            $RetNotIgnored()
            inline core::Iterator<Type> *iterator() const override;

            $RetNotIgnored()
            inline bool contain(const Type &value) const override;

            $RetRequiresRelease()
            inline Vector<Type> *copy() const override;

            inline void add(const Type &element) override;

            inline Type remove() override;
        };
    } // namespace collection
} // namespace EnhancedBasic

#include "EnhancedBasic/collection/Vector.hpp"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_VECTOR_H
