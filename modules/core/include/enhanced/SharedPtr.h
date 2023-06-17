/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>
#include <enhanced/Memory.h>
#include <enhanced/Array.h>
#include <enhanced/exceptions/NullPointerException.h>
#include <enhanced/exceptions/NotImplementedError.h>

namespace enhancedInternal {
    class E_CORE_API SharedPtrImpl {
    protected:
        mutable enhanced::sizetype* referenceCount;

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

namespace enhanced {
    template <typename Type>
    class SharedPtr final : private enhancedInternal::SharedPtrImpl {
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

        E_RET_NO_DISCARD() E_RET_NOT_NULL()
        inline Type* get() const noexcept {
            nullPointerCheck();
            return static_cast<Type*>(pointer);
        }

        E_RET_NO_DISCARD() E_RET_NULLABLE_IF(pointer == null)
        inline Type* self() const noexcept {
            return static_cast<Type*>(pointer);
        }

        E_RET_NO_DISCARD()
        inline const SharedPtr* addressOf() const noexcept {
            return &self();
        }

        E_RET_NO_DISCARD()
        inline Type* endOf() const noexcept {
            return static_cast<Type*>(end);
        }

        inline void release() const noexcept {
            release0(destroy);
        }

        E_RET_NO_DISCARD()
        inline Type* operator+(sizetype offset) const noexcept {
            return self() + offset;
        }

        E_RET_NO_DISCARD()
        inline Type* operator-(sizetype offset) const noexcept {
            return self() - offset;
        }

        E_RET_NO_DISCARD()
        inline Type* operator->() const {
            return get();
        }

        E_RET_NO_DISCARD()
        inline Type& operator*() const {
            return *get();
        }

        E_RET_NO_DISCARD()
        inline Type& operator[](sizetype offset) const {
            return get()[offset];
        }

        E_RET_NO_DISCARD() E_RETURN_SELF()
        inline operator Type*() const noexcept {
            return self();
        }

        E_RETURN_SELF()
        inline SharedPtr<Type>& operator=(const SharedPtr<Type>& other) noexcept {
            assign0(other, destroy);
            return *this;
        }

        E_RETURN_SELF()
        inline SharedPtr<Type>& operator=(SharedPtr<Type>&& other) noexcept {
            assign0(other, destroy);
            return *this;
        }
    };
}
