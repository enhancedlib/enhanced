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
    class ENHANCED_BASIC_API ArrayListImpl {
    private:
        void** elements;

        Size length;

        Size maxCount;

    protected:
        struct GenericOperator {
            void* (*allocate)(GenericReference);

            void (*destroy)(void*);

            bool (*equals)(GenericReference, GenericReference);
        };

        class ENHANCED_BASIC_API ArrayListIteratorImpl {
            friend class ArrayListImpl;

        private:
            const ArrayListImpl* arrayList;

            mutable void** indexer;

            mutable bool isFirst;

            void** end;

        protected:
            explicit ArrayListIteratorImpl(const ArrayListImpl* arrayList);

            virtual ~ArrayListIteratorImpl() noexcept;

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

        mutable ArrayListIteratorImpl* iterator;

        ArrayListImpl(Size maxCount, GenericOperator genericOperator);

        ArrayListImpl(const ArrayListImpl& other);

        virtual ~ArrayListImpl() noexcept;

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
    class ArrayList final : public List<Type>, public RandomAccess, private enhanced::basic::generic_impl::collection::ArrayListImpl {
    private:
        using ArrayListImpl = enhanced::basic::generic_impl::collection::ArrayListImpl;

        class ArrayListIterator : public Iterator<Type>, private ArrayListImpl::ArrayListIteratorImpl {
            friend struct Iterable<Type>;

        public:
            explicit inline ArrayListIterator(const ArrayList<Type>* arrayList) : ArrayListIteratorImpl(arrayList) {}

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
        static void* allocate(GenericReference element) {
            return new Type((Type&) element);
        }

        static void destroy(void* element) {
            delete (Type*) element;
        }

        RetCannotIgnored()
        static bool equals(GenericReference element, GenericReference value) {
            return ((Type&) element) == ((Type&) value);
        }

    public:
        inline ArrayList() : ArrayListImpl(DEFAULT_ARRAY_INIT_SIZE, {allocate, destroy, equals}) {}

        explicit inline ArrayList(Size maxCount) : ArrayListImpl(maxCount, {allocate, destroy, equals}) {}

        inline ArrayList(const ArrayList<Type>& other) : ArrayListImpl(other) {}

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
        inline ArrayList<Type>* copy() const override {
            return new ArrayList<Type>(*this);
        }

        RetCannotIgnored()
        inline Iterator<Type>* iterator() const override {
            return Iterable<Type>::template getIterator<ArrayListIterator>(ArrayListImpl::iterator, this);
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
