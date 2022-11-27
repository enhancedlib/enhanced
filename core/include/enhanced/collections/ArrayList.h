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

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>
#include <enhanced/Iterable.h>
#include <enhanced/Iterator.h>
#include <enhanced/InitializerList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/collections/List.h>
#include <enhanced/collections/RandomAccess.h>

namespace enhancedInternal::collections {
    class ENHANCED_CORE_API ArrayListImpl {
    protected:
        void** elements;

        sizetype size;

        sizetype capacity;

        using OpCopy = func (*)(void*) -> void*;
        using OpMove = func (*)(void*) -> void*;
        using OpDestroy = func (*)(void*) -> void;
        using OpEqual = func (*)(void*, void*) -> bool;

        class ENHANCED_CORE_API ArrayListIteratorImpl {
        protected:
            const ArrayListImpl* arrayList;

            mutable void** indexer;

            ArrayListIteratorImpl(const ArrayListImpl* arrayList);

            $NoIgnoreReturn
            func hasNext0() const -> bool;

            func next0() const -> void;

            $NoIgnoreReturn
            func get0() const -> void*;

            func reset0() const -> void;
        };

        ArrayListImpl(sizetype capacity);

        ArrayListImpl(const ArrayListImpl& other, OpCopy opCopy);

        ArrayListImpl(ArrayListImpl&& other) noexcept;

        $NoIgnoreReturn
        func getFirst0() const -> void*;

        $NoIgnoreReturn
        func getLast0() const -> void*;

        $NoIgnoreReturn
        func get0(sizetype index) const -> void*;

        $NoIgnoreReturn
        func indexOf0(void* value, OpEqual opEqual) const -> sizetype;

        func addLast0(void* element, OpCopy opCopy) -> void;

        func addLast1(void* element, OpMove opMove) -> void;

        func addFirst0(void* element, OpCopy opCopy) -> void;

        func addFirst1(void* element, OpMove opMove) -> void;

        func removeFirst0(OpDestroy opDestory) -> void;

        func removeLast0(OpDestroy opDestory) -> void;

        func setCapacity0(sizetype newCapacity) -> void;

        func expand0() -> void;

        func expand0(sizetype expSize) -> void;

        func shrink0() -> void;

        func shrink0(sizetype shrSize) -> void;

        func clear0(OpDestroy opDestory) -> void;

    public:
        using ExpSizeFallbackFunc = func (*)(sizetype) -> sizetype;

        ExpSizeFallbackFunc expSizeFallback;
    };
}

namespace enhanced::collections {
    template <typename Type>
    class ArrayList : public List<Type>, public RandomAccess, private enhancedInternal::collections::ArrayListImpl {
    private:
        using ArrayListImpl = enhancedInternal::collections::ArrayListImpl;

    public:
        class ArrayListIterator : public Iterator<Type>, private ArrayListImpl::ArrayListIteratorImpl {
        public:
            inline explicit ArrayListIterator(const ArrayList<Type>* arrayList) : ArrayListIteratorImpl(arrayList) {}

            $NoIgnoreReturn
            inline func hasNext() const -> bool override {
                return hasNext0();
            }

            inline func next() const -> const Iterator<Type>* override {
                next0();
                return this;
            }

            $NoIgnoreReturn
            inline func get() const -> Type& override {
                return *reinterpret_cast<Type*>(get0());
            }

            inline func reset() const -> void override {
                reset0();
            }

            $NoIgnoreReturn
            inline func count() const -> sizetype override {
                return static_cast<const ArrayList<Type>*>(arrayList)->size;
            }
        };

    private:
        $RetRequiresRelease
        static func copy(void* element) -> void* {
            return new Type(*reinterpret_cast<Type*>(element));
        }

        $RetRequiresRelease
        static func move(void* element) -> void* {
            return new Type(util::move(*reinterpret_cast<Type*>(element)));
        }

        static func destroy(void* element) -> void {
            delete reinterpret_cast<Type*>(element);
        }

        $NoIgnoreReturn
        static func equal(void* element, void* value) -> bool {
            return *reinterpret_cast<Type*>(element) == *reinterpret_cast<Type*>(value);
        }

        ArrayListIterator iter {this};

    public:
        inline ArrayList() : ArrayListImpl(ARRAY_INIT_SIZE) {}

        inline ArrayList(InitializerList<Type> list) : ArrayListImpl(initListConut(list) * 2) {
            for (let item : list) {
                addLast(util::move(item));
            }
        }

        inline explicit ArrayList(sizetype capacity) : ArrayListImpl(capacity) {}

        inline ArrayList(const ArrayList<Type>& other) : ArrayListImpl(other, copy) {}

        inline ArrayList(ArrayList<Type>&& other)  noexcept : ArrayListImpl(util::move(other)) {}

        inline ~ArrayList() noexcept {
            clear();
            delete[] elements;
        }

        $NoIgnoreReturn
        inline func getSize() const -> sizetype override {
            return size;
        }

        $NoIgnoreReturn
        inline func isEmpty() const -> bool override {
            return size != 0;
        }

        $NoIgnoreReturn
        inline func contain(const Type& value) const -> bool override {
            return indexOf(value) != INVALID_SIZE;
        }

        $NoIgnoreReturn
        inline func iterator() const -> const Iterator<Type>& override {
            iter.reset();
            return iter;
        }

        $NoIgnoreReturn
        inline func indexOf(const Type& value) const -> sizetype override {
            return indexOf0(util::removePtrConst(&value), equal);
        }

        $NoIgnoreReturn
        inline func getFirst() const -> Type& override {
            return *reinterpret_cast<Type*>(getFirst0());
        }

        $NoIgnoreReturn
        inline func getLast() const -> Type& override {
            return *reinterpret_cast<Type*>(getLast0());
        }

        $NoIgnoreReturn
        inline func get(sizetype index) const -> Type& override {
            return *reinterpret_cast<Type*>(get0(index));
        }

        $NoIgnoreReturn
        inline func getCapacity() const -> sizetype {
            return capacity;
        }

        $NoIgnoreReturn
        inline func operator[](sizetype index) const -> Type& override {
            return get(index);
        }

        inline func addFirst(const Type& element) -> void override {
            addFirst0(util::removePtrConst(&element), copy);
        }

        inline func addFirst(Type&& element) -> void override {
            addFirst1(util::removePtrConst(&element), move);
        }

        inline func addLast(const Type& element) -> void override {
            addLast0(util::removePtrConst(&element), copy);
        }

        inline func addLast(Type&& element) -> void override {
            addLast1(util::removePtrConst(&element), move);
        }

        inline func push(const Type& element) -> void override {
            return addFirst(element);
        }

        inline func push(Type&& element) -> void override {
            return addFirst(util::move(element));
        }

        inline func add(const Type& element) -> void override {
            addLast(element);
        }

        inline func add(Type&& element) -> void override {
            addLast(util::move(element));
        }

        inline func removeFirst() -> Type override {
            Type value = getFirst();
            removeLast0(destroy);
            return value;
        }

        inline func removeLast() -> Type override {
            Type value = getLast();
            removeLast0(destroy);
            return value;
        }

        inline func removeFirstIf() -> bool override {
            if (size == 0) return false;
            removeLast0(destroy);
            return true;
        }

        inline func removeLastIf() -> bool override {
            if (size == 0) return false;
            removeLast0(destroy);
            return true;
        }

        inline func popup() -> Type override {
            return removeFirst();
        }

        inline func popupIf() -> bool override {
            return removeFirstIf();
        }

        inline func remove() -> Type override {
            return removeLast();
        }

        inline func removeIf() -> bool override {
            return removeLastIf();
        }

        inline func setCapacity(sizetype newCapacity) -> void {
            setCapacity0(newCapacity);
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
