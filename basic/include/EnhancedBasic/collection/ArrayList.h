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

#ifndef ENHANCED_BASIC_COLLECTION_ARRAY0LIST_H
#define ENHANCED_BASIC_COLLECTION_ARRAY0LIST_H

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
        class ENHANCED_BASIC_API ArrayList0 {
        private:
            Size maxCount;

            GenericPointer *elements;

            Size length;

        protected:
            struct GenericsOperator {
                GenericPointer (*allocate)(GenericReference);

                void (*destroy)(GenericPointer);

                bool (*equals)(GenericReference, GenericReference);
            };

            class ENHANCED_BASIC_API ArrayListIterator0 {
                friend class ArrayList0;

            private:
                const ArrayList0 *arrayList;

                mutable GenericPointer *indexer;

                mutable bool isFirst;

                const GenericPointer *end;

            protected:
                explicit ArrayListIterator0(const ArrayList0 *arrayList);

                virtual ~ArrayListIterator0() noexcept;

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

            mutable ArrayListIterator0 *iterator;

            ArrayList0(Size length, GenericsOperator genericsOperator);

            ArrayList0(const ArrayList0 &copy);

            virtual ~ArrayList0() noexcept;

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
        class ArrayList final : public List<Type>, public RandomAccess<Type>, private ArrayList0 {
        private:
            class ArrayListIterator : public core::Iterator<Type>, private ArrayList0::ArrayListIterator0 {
                friend struct core::Iterable<Type>;

            public:
                explicit inline ArrayListIterator(const ArrayList<Type> *arrayList);

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
            explicit inline ArrayList();

            explicit inline ArrayList(Size maxCount);

            inline ArrayList(const ArrayList<Type> &copy);

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
            inline ArrayList<Type> *copy() const override;

            inline void add(const Type &element) override;

            inline Type remove() override;
        };
    } // namespace collection
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#include "EnhancedBasic/collection/ArrayList.tcc"

#endif // !ENHANCED_BASIC_COLLECTION_ARRAY0LIST_H
