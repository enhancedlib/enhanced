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
#include <enhanced/core/array.h>
#include <enhanced/core/util/traits.h>
#include <enhanced/core/exceptions/NullPointerException.h>
#include <enhanced/core/exceptions/NotImplementedError.h>

namespace enhancedInternal::core::util {
    class ENHANCED_CORE_API SharedPtrImpl {
    private:
        mutable sizetype* referenceCount;

    public:
        void* pointer;

        void* end;

        using OpDestroy = func (*)(void* ptr, void* end) -> void;

        SharedPtrImpl(void* ptr);

        SharedPtrImpl(void* ptr, void* end);

        SharedPtrImpl(const SharedPtrImpl& other) noexcept;

        SharedPtrImpl(SharedPtrImpl&& other) noexcept;

        func release0(OpDestroy opDestroy) const noexcept -> void;

        func assign0(const SharedPtrImpl& other, OpDestroy opDestroy) noexcept -> void;

        func assign0(SharedPtrImpl&& other, OpDestroy opDestroy) noexcept -> void;
    };
}

namespace enhanced::core::util {
    template <typename Type>
    class SharedPtr final : private enhancedInternal::core::util::SharedPtrImpl {
    private:
        static func destroy(void* ptr, void* end) -> void {
            if (ptr == (static_cast<Type*>(end) + 1)) {
                delete static_cast<Type*>(ptr);
            } else {
                if constexpr (isClass<Type>) {
                    for (Type* item = static_cast<Type*>(ptr); item != static_cast<Type*>(end); ++item) {
                        item->~Type();
                    }
                }

                operator delete(ptr);
            }
        }

        inline func nullPointerCheck() const -> void {
            if (pointer == null) throw exceptions::NullPointerException("The pointer is null");
        }

        SharedPtr(Type* ptr) : SharedPtrImpl(static_cast<void*>(ptr)) {}

        SharedPtr(Type* ptr, Type* end) : SharedPtrImpl(static_cast<void*>(ptr), static_cast<void*>(end)) {}

    public:
        template <typename... Args>
        static func make(Args&&... args) -> SharedPtr {
            return new Type(args...);
        }

        template <sizetype size, typename... Args>
        static func make(Args&&... args) -> SharedPtr {
            let ptr = (Type*) operator new(size * sizeof(Type));
            let end = ptr + size;

            for (Type* item = ptr; item != end; ++item) {
                new (item) Type {args...};
            }

            return {ptr, end};
        }

        inline SharedPtr() : SharedPtrImpl(null) {}

        inline SharedPtr(nulltype ptr) : SharedPtrImpl(static_cast<void*>(ptr)) {}

        inline SharedPtr(const SharedPtr<Type>& other) noexcept : SharedPtrImpl(other) {}

        inline SharedPtr(SharedPtr<Type>&& other) noexcept : SharedPtrImpl(other) {}

        inline ~SharedPtr() noexcept {
            release();
        }

        inline func addressOf() const noexcept -> const SharedPtr* {
            return &static_cast<Type*>(pointer);
        }

        inline func release() const noexcept -> void {
            release0(destroy);
        }

        $(NoIgnoreReturn)
        inline func operator+(sizetype offset) const noexcept -> Type* {
            return static_cast<Type*>(pointer) + offset;
        }

        $(NoIgnoreReturn)
        inline func operator-(sizetype offset) const noexcept -> Type* {
            return static_cast<Type*>(pointer) - offset;
        }

        $(NoIgnoreReturn)
        inline func operator->() const -> Type* {
            nullPointerCheck();
            return static_cast<Type*>(pointer);
        }

        $(NoIgnoreReturn)
        inline func operator*() const -> Type& {
            nullPointerCheck();
            return *static_cast<Type*>(pointer);
        }

        $(NoIgnoreReturn)
        inline func operator[](sizetype offset) const -> Type& {
            nullPointerCheck();
            return static_cast<Type*>(pointer)[offset];
        }

        $(NoIgnoreReturn)
        inline operator Type*() const noexcept {
            return static_cast<Type*>(pointer);
        }

        inline func operator=(const SharedPtr<Type>& other) noexcept -> SharedPtr<Type>& {
            assign0(other, destroy);
            return *this;
        }

        inline func operator=(SharedPtr<Type>&& other) noexcept -> SharedPtr<Type>& {
            assign0(other, destroy);
            return *this;
        }
    };
}
