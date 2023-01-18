/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>
#include <enhanced/Array.h>
#include <enhanced/util/Traits.h>
#include <enhanced/exceptions/NullPointerException.h>
#include <enhanced/exceptions/NotImplementedError.h>

namespace enhancedInternal::util {
    class ENHANCED_CORE_API SharedPtrImpl {
    protected:
        mutable sizetype* referenceCount;

        void* pointer;

        void* end;

        using OpDestroy = void (*)(void* ptr, void* end);

        SharedPtrImpl(void* ptr);

        SharedPtrImpl(void* ptr, void* end);

        SharedPtrImpl(const SharedPtrImpl& other) noexcept;

        SharedPtrImpl(SharedPtrImpl&& other) noexcept;

        void release0(OpDestroy opDestroy) const noexcept;

        void assign0(const SharedPtrImpl& other, OpDestroy opDestroy) noexcept;

        void assign0(SharedPtrImpl&& other, OpDestroy opDestroy) noexcept;
    };
}

namespace enhanced::util {
    template <typename Type>
    class SharedPtr final : private enhancedInternal::util::SharedPtrImpl {
    private:
        static void destroy(void* ptr, void* end) {
            if (ptr == (static_cast<Type*>(end) - 1)) {
                delete static_cast<Type*>(ptr);
            } else {
                if constexpr (isClass<Type> && isDestructible<Type>) {
                    for (Type* item = static_cast<Type*>(ptr); item != static_cast<Type*>(end); ++item) {
                        item->~Type();
                    }
                }

                operator delete(ptr);
            }
        }

        inline void nullPointerCheck() const {
            if (pointer == nullptr) throw exceptions::NullPointerException("The pointer is nullptr");
        }

        inline SharedPtr(Type* ptr) : SharedPtrImpl(static_cast<void*>(ptr)) {}

        inline SharedPtr(Type* ptr, Type* end) : SharedPtrImpl(static_cast<void*>(ptr), static_cast<void*>(end)) {}

      public:
        template <typename... Args>
        static inline SharedPtr make(Args&&... args) {
            return new Type {args...};
        }

        template <typename... Args>
        static SharedPtr makeMulti(sizetype size, Args&&... args) {
            auto ptr = (Type*) operator new(size * sizeof(Type));
            auto end = ptr + size;

            for (Type* item = ptr; item != end; ++item) {
                new (item) Type {args...};
            }

            return {ptr, end};
        }

        template <sizetype size, typename... Args>
        static inline SharedPtr make(Args&&... args) {
            return makeMulti(size, args...);
        }

        inline SharedPtr() noexcept : SharedPtrImpl(nullptr) {}

        inline SharedPtr(nulltype ptr) : SharedPtrImpl(static_cast<void*>(ptr)) {}

        inline SharedPtr(const SharedPtr<Type>& other) noexcept : SharedPtrImpl(other) {}

        inline SharedPtr(SharedPtr<Type>&& other) noexcept : SharedPtrImpl(other) {}

        inline ~SharedPtr() noexcept {
            release();
        }

        [[RetNotIgnored, RetNotNull]]
        inline Type* get() const noexcept {
            nullPointerCheck();
            return static_cast<Type*>(pointer);
        }

        [[RetNotIgnored, RetNullable]]
        inline Type* self() const noexcept {
            return static_cast<Type*>(pointer);
        }

        [[RetNotIgnored]]
        inline const SharedPtr* addressOf() const noexcept {
            return &self();
        }

        [[RetNotIgnored]]
        inline Type* endOf() const noexcept {
            return static_cast<Type*>(end);
        }

        inline void release() const noexcept {
            release0(destroy);
        }

        [[RetNotIgnored]]
        inline Type* operator+(sizetype offset) const noexcept {
            return self() + offset;
        }

        [[RetNotIgnored]]
        inline Type* operator-(sizetype offset) const noexcept {
            return self() - offset;
        }

        [[RetNotIgnored]]
        inline Type* operator->() const {
            return get();
        }

        [[RetNotIgnored]]
        inline Type& operator*() const {
            return *get();
        }

        [[RetNotIgnored]]
        inline Type& operator[](sizetype offset) const {
            return get()[offset];
        }

        [[RetNotIgnored, ReturnSelf]]
        inline operator Type*() const noexcept {
            return self();
        }

        [[ReturnSelf]]
        inline SharedPtr<Type>& operator=(const SharedPtr<Type>& other) noexcept {
            assign0(other, destroy);
            return *this;
        }

        [[ReturnSelf]]
        inline SharedPtr<Type>& operator=(SharedPtr<Type>&& other) noexcept {
            assign0(other, destroy);
            return *this;
        }
    };
}
