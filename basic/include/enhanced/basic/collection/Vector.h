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

#include "List.h"
#include "RandomAccess.h"

#ifdef CXX_LANGUAGE // C++ language

namespace enhanced::basic::generic_impl::collection {
    class ENHANCED_BASIC_API VectorImpl {
    private:
        Size maxCount;

        void* elements;

        Size length;

    protected:
        struct GenericOperator {
            void* (*allocateArray)(const Size size);

            void (*copyArray)(void* destination, void* source, const Size size);

            void (*moveArray)(void* destination, void* source, const Size size);

            void* (*index)(void* elements, const Size index);

            GenericReference (*getElement)(void* elements, const Size index);

            void (*setElement)(void* elements, const Size index, GenericReference value);

            bool (*equals)(GenericReference element, GenericReference value);
        };

        class ENHANCED_BASIC_API VectorIteratorImpl {
            friend class VectorImpl;

        private:
            const VectorImpl* vector;

            mutable void* indexer;

            mutable bool isFirst;

            void* end;

        protected:
            explicit VectorIteratorImpl(const VectorImpl* vector);

            virtual ~VectorIteratorImpl() noexcept;

            RetCannotIgnored()
            bool hasNext0() const;

            void next0() const;

            RetCannotIgnored()
            bool each0() const;

            RetCannotIgnored()
            GenericReference get0() const;

            void reset0() const;

            RetCannotIgnored()
            Size count0() const;
        };

        GenericOperator genericOperator;

        mutable VectorIteratorImpl* iterator;

        VectorImpl(Size maxCount, GenericOperator genericOperator);

        VectorImpl(const VectorImpl& other);

        virtual ~VectorImpl() noexcept;

        RetCannotIgnored()
        Size getLength0() const;

        RetCannotIgnored()
        bool isEmpty0() const;

        RetCannotIgnored()
        GenericReference get0(Size index) const;

        RetCannotIgnored()
        bool contain0(GenericReference value) const;

        void add0(GenericReference element);

        void remove0();

        void expand0(Size size);

        void shrink0(Size size);
    };
}


namespace enhanced::basic::collection {
    template <typename Type>
    class Vector final : public List<Type>, public RandomAccess, private enhanced::basic::generic_impl::collection::VectorImpl {
    private:
        using VectorImpl = enhanced::basic::generic_impl::collection::VectorImpl;

        class VectorIterator : public Iterator<Type>, private VectorImpl::VectorIteratorImpl {
            friend struct Iterable<Type>;

        public:
            explicit inline VectorIterator(const Vector<Type>* vector) : VectorIteratorImpl(vector) {}

            RetCannotIgnored()
            inline bool hasNext() const override {
                return hasNext0();
            }

            inline const Iterator<Type>* next() const override {
                next0();
                return this;
            }

            RetCannotIgnored()
            inline bool each() const override {
                return each0();
            }

            RetCannotIgnored()
            inline Type& get() const override {
                return (Type&) get0();
            }

            inline void reset() const override {
                reset0();
            }

            RetCannotIgnored()
            inline Size count() const override {
                return count0();
            }
        };

        RetRequiresRelease()
        static void* allocateArray(Size size) {
            return operator new(size * sizeof(Type));
        }

        static void copyArray(void* destination, void* source, const Size size) {
            for (Size index = 0; index < size; ++index) {
                ((Type*) destination)[index] = ((Type*) source)[index];
            }
        }

        static void moveArray(void* destination, void* source, Size size) {
            for (Size index = 0; index < size; ++index) {
                ((Type*) destination)[index] = (Type&&) ((Type*) (source))[index];
            }
        }

        static GenericReference getElement(void* elements, Size index) {
            return (GenericReference) ((Type*) elements)[index];
        }

        static void* index(void* elements, Size index) {
            return (void*) ((Type*) elements + index);
        }

        static void setElement(void* elements, Size index, GenericReference value) {
            ((Type*) elements)[index] = (Type&&) value;
        }

        RetCannotIgnored()
        static bool equals(GenericReference element, GenericReference value) {
            return ((Type&) element) == ((Type&) value);
        }

    public:
        inline Vector() : VectorImpl(DEFAULT_ARRAY_INIT_SIZE, {allocateArray, copyArray, moveArray, index, getElement, setElement, equals}) {}

        explicit inline Vector(Size maxCount) : VectorImpl(maxCount, {allocateArray, copyArray, moveArray, index, getElement, setElement, equals}) {}

        inline Vector(const Vector<Type>& other) : VectorImpl(other) {}

        RetCannotIgnored()
        inline Size getLength() const override {
            return getLength0();
        }

        RetCannotIgnored()
        inline bool isEmpty() const override {
            return isEmpty0();
        }

        RetCannotIgnored()
        inline bool contain(const Type& value) const override {
            return contain0((GenericReference) value);
        }

        RetRequiresRelease()
        inline Vector<Type>* copy() const override {
            return new Vector<Type>(*this);
        }

        RetCannotIgnored()
        inline Iterator<Type>* iterator() const override {
            return Iterable<Type>::template getIterator<VectorIterator>(VectorImpl::iterator, this);
        }

        RetCannotIgnored()
        inline Type& get(Size index) const override {
            return (Type&) get0(index);
        }

        RetCannotIgnored()
        inline Type& operator[](Size index) const override {
            return (Type&) get0(index);
        }

        inline void add(const Type& element) override {
            add0((GenericReference) element);
        }

        inline Type remove() override {
            Type value = get(getLength() - 1);
            remove0();
            return value;
        }
    };
}

#endif // CXX_LANGUAGE
