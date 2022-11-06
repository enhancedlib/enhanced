/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/core/defines.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/Iterable.h>
#include <enhanced/core/Iterator.h>
#include <enhanced/core/generic.h>
#include <enhanced/core/collections/List.h>
#include <enhanced/core/collections/RandomAccess.h>

#ifdef CXX_LANGUAGE

namespace enhanced_internal::core::collections {
    class ENHANCED_CORE_API ArrayListImpl {
    private:
        void** elements;

        Size size;

        Size capacity;

    protected:
        struct GenericOperator {
            void* (*allocate)(Generic&);

            void (*destroy)(void*);

            bool (*equals)(Generic&, Generic&);
        };

        class ArrayListIteratorImpl {
            friend class ArrayListImpl;

        private:
            const ArrayListImpl* arrayList;

            mutable void** indexer;

            mutable bool isFirst;

            void** end;

        protected:
            explicit ArrayListIteratorImpl(const ArrayListImpl* arrayList);

            virtual ~ArrayListIteratorImpl() noexcept;

            RetCannotIgnored
            bool hasNext0() const;

            void next0() const;

            RetCannotIgnored
            bool each0() const;

            RetCannotIgnored
            Generic& get0() const;

            void reset0() const;

            RetCannotIgnored
            Size count0() const;
        };

        GenericOperator genericOperator;

        mutable ArrayListIteratorImpl* iterator;

        ArrayListImpl(Size capacity, GenericOperator genericOperator);

        ArrayListImpl(const ArrayListImpl& other);

        virtual ~ArrayListImpl() noexcept;

        RetCannotIgnored
        Size getSize0() const;

        RetCannotIgnored
        bool isEmpty0() const;

        RetCannotIgnored
        Generic& get0(Size index) const;

        RetCannotIgnored
        bool contain0(Generic& value) const;

        void add0(Generic& element);

        void remove0();

        void expand0(Size size);

        void shrink0(Size size);
    };
}

namespace enhanced::core::collections {
    template <typename Type>
    class ENHANCED_CORE_API ArrayList final : public List<Type>, public RandomAccess, private enhanced_internal::core::collections::ArrayListImpl {
    private:
        using ArrayListImpl = enhanced_internal::core::collections::ArrayListImpl;

        class ArrayListIterator : public Iterator<Type>, private ArrayListImpl::ArrayListIteratorImpl {
            friend struct Iterable<Type>;

        public:
            explicit inline ArrayListIterator(const ArrayList<Type>* arrayList) : ArrayListIteratorImpl(arrayList) {}

            RetCannotIgnored
            inline bool hasNext() const override {
                return hasNext0();
            }

            inline const Iterator<Type>* next() const override {
                next0();
                return this;
            }

            RetCannotIgnored
            inline bool each() const override {
                return each0();
            }

            RetCannotIgnored
            inline Type& get() const override {
                return (Type&) get0();
            }

            inline void reset() const override {
                reset0();
            }

            RetCannotIgnored
            inline Size count() const override {
                return count0();
            }
        };

        RetRequiresRelease
        static void* allocate(Generic& element) {
            return new Type((Type&) element);
        }

        static void destroy(void* element) {
            delete (Type*) element;
        }

        RetCannotIgnored
        static bool equals(Generic& element, Generic& value) {
            return ((Type&) element) == ((Type&) value);
        }

    public:
        inline ArrayList() : ArrayListImpl(ARRAY_INIT_SIZE, {allocate, destroy, equals}) {}

        explicit inline ArrayList(Size capacity) : ArrayListImpl(capacity, {allocate, destroy, equals}) {}

        inline ArrayList(const ArrayList<Type>& other) : ArrayListImpl(other) {}

        RetCannotIgnored
        inline Size getSize() const override {
            return getSize0();
        }

        RetCannotIgnored
        inline bool isEmpty() const override {
            return isEmpty0();
        }

        RetCannotIgnored
        inline bool contain(const Type& value) const override {
            return contain0((Generic&) value);
        }

        RetRequiresRelease
        inline ArrayList<Type>* copy() const override {
            return new ArrayList<Type>(*this);
        }

        RetCannotIgnored
        inline Iterator<Type>* iterator() const override {
            return Iterable<Type>::template getIterator<ArrayListIterator>(ArrayListImpl::iterator, this);
        }

        RetCannotIgnored
        inline Type& get(Size index) const override {
            return (Type&) get0(index);
        }

        RetCannotIgnored
        inline Type& operator[](Size index) const override {
            return (Type&) get0(index);
        }

        inline void add(const Type& element) override {
            add0((Generic&) element);
        }

        inline Type remove() override {
            Type value = get(getSize() - 1);
            remove0();
            return value;
        }

        inline void expand(Size size) {
            expand0(size);
        }

        inline void shrink(Size size) {
            shrink0(size);
        }
    };
}

#endif
