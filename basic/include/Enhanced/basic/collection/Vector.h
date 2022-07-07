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

#pragma once

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"

#include "Enhanced/basic/export.h"

#include "Enhanced/basic/core/Iterable.h"
#include "Enhanced/basic/core/Iterator.h"

#include "Enhanced/basic/util/Generic.h"

#include "List.h"
#include "RandomAccess.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedGenericImpl::basic::collection {
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

            RetNotIgnored()
            bool hasNext0() const;

            void next0() const;

            RetNotIgnored()
            bool each0() const;

            RetNotIgnored()
            GenericReference get0() const;

            void reset0() const;

            RetNotIgnored()
            Size count0() const;
        };

        GenericOperator genericOperator;

        mutable VectorIteratorImpl* iterator;

        VectorImpl(Size maxCount, GenericOperator genericOperator);

        VectorImpl(const VectorImpl& other);

        virtual ~VectorImpl() noexcept;

        RetNotIgnored()
        Size getLength0() const;

        RetNotIgnored()
        bool isEmpty0() const;

        RetNotIgnored()
        GenericReference get0(Size index) const;

        RetNotIgnored()
        bool contain0(GenericReference value) const;

        void add0(GenericReference element);

        void remove0();

        void expand0(Size size);

        void shrink0(Size size);
    };
}


namespace Enhanced::basic::collection {
    template <typename Type>
    class Vector final : public List<Type>, public RandomAccess, private EnhancedGenericImpl::basic::collection::VectorImpl {
    private:
        using VectorImpl = EnhancedGenericImpl::basic::collection::VectorImpl;

        class VectorIterator : public core::Iterator<Type>, private VectorImpl::VectorIteratorImpl {
            friend struct core::Iterable<Type>;

        public:
            explicit inline VectorIterator(const Vector<Type>* vector) : VectorIteratorImpl(vector) {}

            RetNotIgnored()
            inline bool hasNext() const override {
                return hasNext0();
            }

            inline const core::Iterator<Type>* next() const override {
                next0();
                return this;
            }

            RetNotIgnored()
            inline bool each() const override {
                return each0();
            }

            RetNotIgnored()
            inline Type& get() const override {
                return (Type&) get0();
            }

            inline void reset() const override {
                reset0();
            }

            RetNotIgnored()
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

        RetNotIgnored()
        static bool equals(GenericReference element, GenericReference value) {
            return ((Type&) element) == ((Type&) value);
        }

    public:
        inline Vector() : VectorImpl(DEFAULT_ARRAY_INIT_SIZE, {allocateArray, copyArray, moveArray, index, getElement, setElement, equals}) {}

        explicit inline Vector(Size maxCount) : VectorImpl(maxCount, {allocateArray, copyArray, moveArray, index, getElement, setElement, equals}) {}

        inline Vector(const Vector<Type>& other) : VectorImpl(other) {}

        RetNotIgnored()
        inline Size getLength() const override {
            return getLength0();
        }

        RetNotIgnored()
        inline bool isEmpty() const override {
            return isEmpty0();
        }

        RetNotIgnored()
        inline bool contain(const Type& value) const override {
            return contain0((GenericReference) value);
        }

        RetRequiresRelease()
        inline Vector<Type>* copy() const override {
            return new Vector<Type>(*this);
        }

        RetNotIgnored()
        inline core::Iterator<Type>* iterator() const override {
            return core::Iterable<Type>::template getIterator<VectorIterator>(VectorImpl::iterator, this);
        }

        RetNotIgnored()
        inline Type& get(Size index) const override {
            return (Type&) get0(index);
        }

        RetNotIgnored()
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
