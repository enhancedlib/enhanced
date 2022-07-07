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

#include "Enhanced/basic/collection/RandomAccess.h"
#include "MixedList.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedGenericImpl::basic::collection::mixed {
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

        mutable MixedArrayListIteratorImpl* iterator;

        MixedArrayListImpl(Size maxCount, GenericOperator genericOperator);

        MixedArrayListImpl(const MixedArrayListImpl& other);

        virtual ~MixedArrayListImpl() noexcept;

        RetNotIgnored()
        Size getLength0() const;

        RetNotIgnored()
        bool isEmpty0() const;

        RetNotIgnored()
        GenericReference get0(Size index) const;

        RetNotIgnored()
        bool contain0(GenericReference value) const;

        void add0(GenericReference element);

        void addReference0(GenericReference element);

        void remove0();

        void expand0(Size size);

        void shrink0(Size size);
    };
}

namespace Enhanced::basic::collection::mixed {
    template <typename Type>
    class MixedArrayList final : public MixedList<Type>, public RandomAccess,
                                 private EnhancedGenericImpl::basic::collection::mixed::MixedArrayListImpl {
    private:
        using MixedArrayListImpl = EnhancedGenericImpl::basic::collection::mixed::MixedArrayListImpl;

        class MixedArrayListIterator : public core::Iterator<Type>,
                                       private MixedArrayListImpl::MixedArrayListIteratorImpl {
            friend struct core::Iterable<Type>;

        public:
            explicit inline MixedArrayListIterator(const MixedArrayList<Type>* arrayList) : MixedArrayListIteratorImpl(arrayList) {}

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
        static void* allocate(GenericReference element) {
            return new Type(reinterpret_cast<Type&>(element));
        }

        static void destroy(void* element) {
            delete (Type*) element;
        }

        RetNotIgnored()
        static bool equals(GenericReference element, GenericReference value) {
            return ((Type&) element) == ((Type&) (value));
        }

    public:
        inline MixedArrayList() : MixedArrayListImpl(DEFAULT_ARRAY_INIT_SIZE, {allocate, destroy, equals}) {}

        explicit inline MixedArrayList(Size maxCount) : MixedArrayListImpl(maxCount, {allocate, destroy, equals}) {}

        inline MixedArrayList(const MixedArrayList<Type>& other) : MixedArrayListImpl(other) {}

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
        inline MixedArrayList<Type>* copy() const override {
            return new MixedArrayList<Type>(*this);
        }

        RetNotIgnored()
        inline Type& get(Size index) const override {
            return (Type&) get0(index);
        }

        RetNotIgnored()
        inline Type& operator[](Size index) const override {
            return (Type&) get0(index);
        }

        inline core::Iterator<Type>* iterator() const override {
            return core::Iterable<Type>::template getIterator<MixedArrayListIterator>(MixedArrayListImpl::iterator,this);
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
