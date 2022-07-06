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
#include "ReferList.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedGenericImpl::basic::collection::refer {
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

        mutable ReferArrayListIteratorImpl* iterator;

        ReferArrayListImpl(Size maxCount, GenericOperator genericOperator);

        ReferArrayListImpl(const ReferArrayListImpl& other);

        virtual ~ReferArrayListImpl() noexcept;

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

namespace Enhanced::basic::collection::refer {
    template <typename Type>
    class ReferArrayList final : public ReferList<Type>, public RandomAccess<Type>,
                                 private EnhancedGenericImpl::basic::collection::refer::ReferArrayListImpl {
    private:
        using ReferArrayListImpl = EnhancedGenericImpl::basic::collection::refer::ReferArrayListImpl;

        class ReferArrayListIterator : public core::Iterator<Type>,
                                       private ReferArrayListImpl::ReferArrayListIteratorImpl {
            friend struct core::Iterable<Type>;

        public:
            explicit inline ReferArrayListIterator(const ReferArrayList<Type>* referArrayList) : ReferArrayListIteratorImpl(referArrayList) {}

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

        RetNotIgnored()
        static bool equals(GenericReference element, GenericReference value) {
            return ((Type&) element) == ((Type&) (value));
        }

    public:
        inline ReferArrayList() : ReferArrayListImpl(UINT8_MAX, {equals}) {};

        explicit inline ReferArrayList(Size maxCount) : ReferArrayListImpl(maxCount, {equals}) {}

        inline ReferArrayList(const ReferArrayList<Type>& other) : ReferArrayListImpl(other) {}

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
        inline ReferArrayList<Type>* copy() const override {
            return new ReferArrayList<Type>(*this);
        }

        inline core::Iterator<Type>* iterator() const override {
            return core::Iterable<Type>::template getIterator<ReferArrayListIterator>(ReferArrayListImpl::iterator,this);
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
