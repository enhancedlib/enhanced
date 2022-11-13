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
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/Iterable.h>
#include <enhanced/core/Iterator.h>
#include <enhanced/core/collections/List.h>
#include <enhanced/core/collections/RandomAccess.h>
#include <enhanced/core/util/traits.h>

namespace enhanced_internal::core::collections {
    class ENHANCED_CORE_API ArrayListImpl {
    protected:
        void** elements;

        sizetype size;

        sizetype capacity;

        struct GenericOperator {
            void* (*allocate)(void*);

            void (*destroy)(void*);

            bool (*equals)(void*, void*);
        };

        class ENHANCED_CORE_API ArrayListIteratorImpl {
            friend class ArrayListImpl;

        protected:
            const ArrayListImpl* arrayList;

            mutable void** indexer;

            explicit ArrayListIteratorImpl(const ArrayListImpl* arrayList);

            virtual ~ArrayListIteratorImpl() noexcept;

            $(NoIgnoreReturn)
            func hasNext0() const -> bool;

            func next0() const -> void;

            $(NoIgnoreReturn)
            func get0() const -> void*;

            func reset0() const -> void;
        };

        GenericOperator genericOperator;

        ArrayListImpl(sizetype capacity, GenericOperator genericOperator);

        ArrayListImpl(const ArrayListImpl& other);

        virtual ~ArrayListImpl() noexcept;

        $(NoIgnoreReturn)
        func get0(sizetype index) const -> void*;

        $(NoIgnoreReturn)
        func contain0(void* value) const -> bool;

        func add0(void* element) -> void;

        func remove0() -> void;

        func expand0(sizetype size) -> void;

        func shrink0(sizetype size) -> void;
    };
}

namespace enhanced::core::collections {
    template <typename Type>
    class ENHANCED_CORE_API ArrayList final : public List<Type>, public RandomAccess, private enhanced_internal::core::collections::ArrayListImpl {
    private:
        using ArrayListImpl = enhanced_internal::core::collections::ArrayListImpl;

        class ENHANCED_CORE_API ArrayListIterator : public Iterator<Type>, private ArrayListImpl::ArrayListIteratorImpl {
            friend class ArrayList<Type>;

        public:
            inline explicit ArrayListIterator(const ArrayList<Type>* arrayList) : ArrayListIteratorImpl(arrayList) {}

            $(NoIgnoreReturn)
            inline func hasNext() const -> bool override {
                return hasNext0();
            }

            inline func next() const -> const Iterator<Type>* override {
                next0();
                return this;
            }

            $(NoIgnoreReturn)
            inline func get() const -> Type& override {
                return *reinterpret_cast<Type*>(get0());
            }

            inline func reset() const -> void override {
                reset0();
            }

            $(NoIgnoreReturn)
            inline func count() const -> sizetype override {
                return static_cast<const ArrayList<Type>*>(arrayList)->size;
            }
        };

        $(RetRequiresRelease)
        static func allocate(void* element) -> void* {
            return new Type(*reinterpret_cast<Type*>(element));
        }

        static func destroy(void* element) -> void {
            delete reinterpret_cast<Type*>(element);
        }

        $(NoIgnoreReturn)
        static func equals(void* element, void* value) -> bool {
            return *reinterpret_cast<Type*>(element) == *reinterpret_cast<Type*>(value);
        }

        ArrayListIterator iter = ArrayListIterator(this);

    public:
        inline ArrayList() : ArrayListImpl(ARRAY_INIT_SIZE, {allocate, destroy, equals}) {}

        inline explicit ArrayList(sizetype capacity) : ArrayListImpl(capacity, {allocate, destroy, equals}) {}

        inline ArrayList(const ArrayList<Type>& other) : ArrayListImpl(other) {}

        $(NoIgnoreReturn)
        inline func getSize() const -> sizetype override {
            return this->size;
        }

        $(NoIgnoreReturn)
        inline func isEmpty() const -> bool override {
            return this->size != 0;
        }

        $(NoIgnoreReturn)
        inline func contain(const Type& value) const -> bool override {
            return contain0(util::traits::removePtrConst(&value));
        }

        $(NoIgnoreReturn)
        inline func iterator() const -> const Iterator<Type>& override {
            iter.reset();
            return iter;
        }

        $(NoIgnoreReturn)
        inline func get(sizetype index) const -> Type& override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        $(NoIgnoreReturn)
        inline func operator[](sizetype index) const -> Type& override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        inline func add(const Type& element) -> void override {
            add0(util::traits::removePtrConst(&element));
        }

        inline func remove() -> Type override {
            Type value = get(getSize() - 1);
            remove0();
            return value;
        }

        $(NoIgnoreReturn)
        inline func getCapacity() const -> sizetype {
            return this->capacity;
        }

        inline func expand(sizetype size) -> void {
            expand0(size);
        }

        inline func shrink(sizetype size) -> void {
            shrink0(size);
        }
    };
}
