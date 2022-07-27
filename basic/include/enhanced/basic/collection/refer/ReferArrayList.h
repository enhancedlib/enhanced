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

#include "enhanced/basic/collection/RandomAccess.h"
#include "ReferList.h"

#ifdef CXX_LANGUAGE // C++ language

namespace enhanced::basic::generic_impl::collection::refer {
    class ENHANCED_BASIC_API ReferArrayListImpl {
    private:
        void** elements;

        Size length;

        Size maxCount;

    protected:
        struct GenericOperator {
            bool (*equals)(GenericReference, GenericReference);
        };

        class ENHANCED_BASIC_API ReferArrayListIteratorImpl {
            friend class ReferArrayListImpl;

        private:
            const ReferArrayListImpl* referenceArrayList;

            mutable void** indexer;

            mutable bool isFirst;

            void** end;

        protected:
            explicit ReferArrayListIteratorImpl(const ReferArrayListImpl* referenceArrayList);

            virtual ~ReferArrayListIteratorImpl() noexcept;

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

        mutable ReferArrayListIteratorImpl* iterator;

        ReferArrayListImpl(Size maxCount, GenericOperator genericOperator);

        ReferArrayListImpl(const ReferArrayListImpl& other);

        virtual ~ReferArrayListImpl() noexcept;

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

namespace enhanced::basic::collection::refer {
    template <typename Type>
    class ReferArrayList final : public ReferList<Type>, public RandomAccess,
                                 private enhanced::basic::generic_impl::collection::refer::ReferArrayListImpl {
    private:
        using ReferArrayListImpl = enhanced::basic::generic_impl::collection::refer::ReferArrayListImpl;

        class ReferArrayListIterator : public Iterator<Type>, private ReferArrayListImpl::ReferArrayListIteratorImpl {
            friend struct Iterable<Type>;

        public:
            explicit inline ReferArrayListIterator(const ReferArrayList<Type>* referArrayList) : ReferArrayListIteratorImpl(referArrayList) {}

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

        RetCannotIgnored()
        static bool equals(GenericReference element, GenericReference value) {
            return ((Type&) element) == ((Type&) (value));
        }

    public:
        inline ReferArrayList() : ReferArrayListImpl(DEFAULT_ARRAY_INIT_SIZE, {equals}) {};

        explicit inline ReferArrayList(Size maxCount) : ReferArrayListImpl(maxCount, {equals}) {}

        inline ReferArrayList(const ReferArrayList<Type>& other) : ReferArrayListImpl(other) {}

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
        inline ReferArrayList<Type>* copy() const override {
            return new ReferArrayList<Type>(*this);
        }

        inline Iterator<Type>* iterator() const override {
            return Iterable<Type>::template getIterator<ReferArrayListIterator>(ReferArrayListImpl::iterator,this);
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
