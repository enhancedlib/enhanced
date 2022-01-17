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

namespace EnhancedBasic {
    namespace collection {
        class ENHANCED_BASIC_API Vector0 {
        private:
            Size maxCount;

            GenericPointer elements;

            Size length;

        protected:
            struct GenericsOperator {
                GenericPointer (*allocateArray)(const Size size);

                void (*destroyArray)(GenericPointer elements, Size length);

                void (*copyArray)(GenericPointer destination, GenericPointer source, const Size size);

                GenericPointer (*index)(GenericPointer elements, const Size index);

                GenericReference (*getElement)(GenericPointer elements, const Size index);

                void (*setElement)(GenericPointer elements, const Size index, GenericReference value);

                bool (*equals)(GenericReference element, GenericReference value);
            };

            class ENHANCED_BASIC_API VectorIterator0 {
                friend class Vector0;

            private:
                const Vector0 *vector;

                mutable GenericPointer indexer;

                mutable bool isFirst;

                GenericPointer end;

            protected:
                explicit VectorIterator0(const Vector0 *vector);

                virtual ~VectorIterator0() noexcept;

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

            mutable VectorIterator0 *iterator;

            Vector0(Size length, GenericsOperator genericsOperator);

            Vector0(const Vector0 &copy);

            virtual ~Vector0() noexcept;

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

        template <typename Type>
        class Vector final : public List<Type>, public RandomAccess<Type>, private Vector0 {
        private:
            class VectorIterator : public core::Iterator<Type>, private Vector0::VectorIterator0 {
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
            static GenericPointer allocateArray(Size size);

            static void destroyArray(GenericPointer elements, Size length);

            static void copyArray(GenericPointer destination, GenericPointer source, Size size);

            static GenericReference getElement(GenericPointer elements, Size index);

            static GenericPointer index(GenericPointer elements, Size index);

            static void setElement(GenericPointer elements, Size index, GenericReference value);

            $RetNotIgnored()
            static bool equals(GenericReference element, GenericReference value);

        public:
            explicit inline Vector();

            explicit inline Vector(Size maxCount);

            inline Vector(const Vector<Type> &copy);

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

#include "EnhancedBasic/collection/Vector.tcc"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_COLLECTION_VECTOR_H
