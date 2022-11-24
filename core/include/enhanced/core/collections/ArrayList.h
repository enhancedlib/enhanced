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
#include <enhanced/core/memory.h>
#include <enhanced/core/Iterable.h>
#include <enhanced/core/Iterator.h>
#include <enhanced/core/InitializerList.h>
#include <enhanced/core/collections/List.h>
#include <enhanced/core/collections/RandomAccess.h>
#include <enhanced/core/util/traits.h>

namespace enhancedInternal::core::collections {
    class ENHANCED_CORE_API ArrayListImpl {
    protected:
        void** elements;

        sizetype size;

        sizetype capacity;

        using FallbackExpSizeFunc = func (*)(sizetype) -> sizetype;

        FallbackExpSizeFunc fallbackExpSize;

        using OpCopy = func (*)(void*) -> void*;
        using OpMove = func (*)(void*) -> void*;
        using OpDestroy = func (*)(void*) -> void;
        using OpEqual = func (*)(void*, void*) -> bool;

        class ENHANCED_CORE_API ArrayListIteratorImpl {
        protected:
            const ArrayListImpl* arrayList;

            mutable void** indexer;

            ArrayListIteratorImpl(const ArrayListImpl* arrayList);

            $(NoIgnoreReturn)
            func hasNext0() const -> bool;

            func next0() const -> void;

            $(NoIgnoreReturn)
            func get0() const -> void*;

            func reset0() const -> void;
        };

        ArrayListImpl(sizetype capacity);

        ArrayListImpl(const ArrayListImpl& other, OpCopy opCopy);

        ArrayListImpl(ArrayListImpl&& other) noexcept;

        func destruct0(OpDestroy opDestroy) noexcept -> void;

        $(NoIgnoreReturn)
        func get0(sizetype index) const -> void*;

        $(NoIgnoreReturn)
        func indexOf0(void* value, OpEqual opEqual) const -> sizetype;

        func add0(void* element, OpCopy opCopy) -> void;

        func addMoved0(void* element, OpMove opMove) -> void;

        func remove0(OpDestroy opDestory) -> void;

        func setCapacity0(sizetype newCapacity) -> void;

        func expand0() -> void;

        func expand0(sizetype expSize) -> void;

        func shrink0() -> void;

        func shrink0(sizetype shrSize) -> void;

        func clear0(OpDestroy opDestory) -> void;
    };
}

namespace enhanced::core::collections {
    template <typename Type>
    class ArrayList final : public List<Type>, public RandomAccess, private enhancedInternal::core::collections::ArrayListImpl {
    private:
        using ArrayListImpl = enhancedInternal::core::collections::ArrayListImpl;

    public:
        class ArrayListIterator : public Iterator<Type>, private ArrayListImpl::ArrayListIteratorImpl {
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

    private:
        $(RetRequiresRelease)
        static func copy(void* element) -> void* {
            return new Type(*reinterpret_cast<Type*>(element));
        }

        $(RetRequiresRelease)
        static func move(void* element) -> void* {
            return new Type(util::move(*reinterpret_cast<Type*>(element)));
        }

        static func destroy(void* element) -> void {
            delete reinterpret_cast<Type*>(element);
        }

        $(NoIgnoreReturn)
        static func equal(void* element, void* value) -> bool {
            return *reinterpret_cast<Type*>(element) == *reinterpret_cast<Type*>(value);
        }

        ArrayListIterator iter {this};

    public:
        inline ArrayList() : ArrayListImpl(ARRAY_INIT_SIZE) {}

        inline ArrayList(InitializerList<Type> list) : ArrayListImpl(initListConut(list) * 2) {
            for (let item : list) {
                add(item);
            }
        }

        inline explicit ArrayList(sizetype capacity) : ArrayListImpl(capacity) {}

        inline ArrayList(const ArrayList<Type>& other) : ArrayListImpl(other, copy) {}

        inline ArrayList(ArrayList<Type>&& other)  noexcept : ArrayListImpl(util::move(other)) {}

        inline ~ArrayList() noexcept {
            destruct0(destroy);
        }

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
            return indexOf(value) != INVALID_SIZE;
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
        inline func indexOf(const Type& value) const -> sizetype override {
            return indexOf0(util::removePtrConst(&value), equal);
        }

        $(NoIgnoreReturn)
        inline func getCapacity() const -> sizetype {
            return this->capacity;
        }

        $(NoIgnoreReturn)
        inline func operator[](sizetype index) const -> Type& override {
            return get(index);
        }

        inline func add(const Type& element) -> void override {
            add0(util::removePtrConst(&element), copy);
        }

        inline func add(Type&& element) -> void override {
            addMoved0(util::removePtrConst(&element), move);
        }

        inline func remove() -> Type override {
            Type value = get(getSize() - 1);
            remove0(destroy);
            return value;
        }

        inline func setCapacity(sizetype newCapacity) -> void {
            setCapacity0(newCapacity);
        }

        inline func expandSizeFallback(FallbackExpSizeFunc fallbackExpSize) -> void {
            this->fallbackExpSize = fallbackExpSize;
        }

        inline func expand() -> void {
            expand0();
        }

        inline func expand(sizetype size) -> void {
            expand0(size);
        }

        inline func shrink() -> void {
            shrink0();
        }

        inline func shrink(sizetype size) -> void {
            shrink0(size);
        }

        inline func clear() -> void override {
            clear0(destroy);
        }
    };
}
