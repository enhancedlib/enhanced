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

#include "enhanced/basic/collection/CollectionDefaultConfig.h"
#include "enhanced/basic/collection/RandomAccess.h"
#include "MixedList.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::generic_impl::collection::mixed {
    class ENHANCED_BASIC_API MixedArrayListImpl {
    private:
        struct Node {
            void* value;

            bool dynamic;
        };

        Node* elements;

        Size length;

        Size maxCount;

    protected:
        struct GenericOperator {
            void* (*allocate)(GenericReference);

            void (*destroy)(void*);

            bool (*equals)(GenericReference, GenericReference);
        };

        class ENHANCED_BASIC_API MixedArrayListIteratorImpl {
            friend class MixedArrayListImpl;

        private:
            const MixedArrayListImpl* mixedArrayList;

            mutable MixedArrayListImpl::Node* indexer;

            mutable bool isFirst;

            const MixedArrayListImpl::Node* end;

        protected:
            explicit MixedArrayListIteratorImpl(const MixedArrayListImpl* mixedArrayList);

            virtual ~MixedArrayListIteratorImpl() noexcept;

            RetCannotIgnored
            bool hasNext0() const;

            void next0() const;

            RetCannotIgnored
            bool each0() const;

            RetCannotIgnored
            GenericReference get0() const;

            void reset0() const;

            RetCannotIgnored
            Size count0() const;
        };

        GenericOperator genericOperator;

        mutable MixedArrayListIteratorImpl* iterator;

        MixedArrayListImpl(Size maxCount, GenericOperator genericOperator);

        MixedArrayListImpl(const MixedArrayListImpl& other);

        virtual ~MixedArrayListImpl() noexcept;

        RetCannotIgnored
        Size getLength0() const;

        RetCannotIgnored
        bool isEmpty0() const;

        RetCannotIgnored
        GenericReference get0(Size index) const;

        RetCannotIgnored
        bool contain0(GenericReference value) const;

        void add0(GenericReference element);

        void addReference0(GenericReference element);

        void remove0();

        void expand0(Size size);

        void shrink0(Size size);
    };
}

namespace enhanced::basic::collection::mixed {
    template <typename Type>
    class MixedArrayList final : public MixedList<Type>, public RandomAccess,
                                 private enhanced::basic::generic_impl::collection::mixed::MixedArrayListImpl {
    private:
        using MixedArrayListImpl = enhanced::basic::generic_impl::collection::mixed::MixedArrayListImpl;

        class MixedArrayListIterator : public Iterator<Type>,
                                       private MixedArrayListImpl::MixedArrayListIteratorImpl {
            friend struct Iterable<Type>;

        public:
            explicit inline MixedArrayListIterator(const MixedArrayList<Type>* arrayList) : MixedArrayListIteratorImpl(arrayList) {}

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
        static void* allocate(GenericReference element) {
            return new Type(reinterpret_cast<Type&>(element));
        }

        static void destroy(void* element) {
            delete (Type*) element;
        }

        RetCannotIgnored
        static bool equals(GenericReference element, GenericReference value) {
            return ((Type&) element) == ((Type&) (value));
        }

    public:
        inline MixedArrayList() : MixedArrayListImpl(CollectionDefaultConfig::ARRAY_INIT_SIZE, {allocate, destroy, equals}) {}

        explicit inline MixedArrayList(Size maxCount) : MixedArrayListImpl(maxCount, {allocate, destroy, equals}) {}

        inline MixedArrayList(const MixedArrayList<Type>& other) : MixedArrayListImpl(other) {}

        RetCannotIgnored
        inline Size getLength() const override {
            return getLength0();
        }

        RetCannotIgnored
        inline bool isEmpty() const override {
            return isEmpty0();
        }

        RetCannotIgnored
        inline bool contain(const Type& value) const override {
            return contain0((GenericReference) value);
        }

        RetRequiresRelease
        inline MixedArrayList<Type>* copy() const override {
            return new MixedArrayList<Type>(*this);
        }

        RetCannotIgnored
        inline Type& get(Size index) const override {
            return (Type&) get0(index);
        }

        RetCannotIgnored
        inline Type& operator[](Size index) const override {
            return (Type&) get0(index);
        }

        inline Iterator<Type>* iterator() const override {
            return Iterable<Type>::template getIterator<MixedArrayListIterator>(MixedArrayListImpl::iterator,this);
        }

        inline void add(const Type& element) override {
            add0((GenericReference) element);
        }

        inline void addReference(const Type& element) override {
            addReference0((GenericReference) element);
        }

        inline Type remove() override {
            Type value = get(getLength() - 1);
            remove0();
            return value;
        }
    };
}

#endif // CXX_LANGUAGE
