/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
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
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
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
#include <enhanced/CoreAPI.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>
#include <enhanced/Memory.h>
#include <enhanced/Array.h>
#include <enhanced/exceptions/NullPointerException.h>
#include <enhanced/exceptions/NotImplementedError.h>

namespace _E_INTERNAL {
    class E_API(core) SharedPtrImpl {
    protected:
        mutable enhanced::sizetype* referenceCount;

        void* pointer;

        void* endAddress;

        using OpDestroy = void (*)(void* pointer, void* endAddress);

        SharedPtrImpl(void* pointer);

        SharedPtrImpl(void* pointer, void* endAddress);

        SharedPtrImpl(const SharedPtrImpl& other) noexcept;

        SharedPtrImpl(SharedPtrImpl&& other) noexcept;

        void release0(OpDestroy opDestroy) const noexcept;

        void assign0(const SharedPtrImpl& other, OpDestroy opDestroy) noexcept;

        void assign0(SharedPtrImpl&& other, OpDestroy opDestroy) noexcept;
    };
}

namespace enhanced {
    template <typename Type>
    class SharedPtr final : private _E_INTERNAL::SharedPtrImpl {
        E_CLASS(SharedPtr)

    E_CLASS_BODY
    private:
        static void destroy(void* pointer, void* endAddress) {
            if (pointer == (static_cast<Type*>(endAddress) - 1)) {
                delete static_cast<Type*>(pointer);
            } else {
                if constexpr (isClass<Type> && isDestructible<Type>) {
                    for (Type* item = static_cast<Type*>(pointer); item != static_cast<Type*>(endAddress); ++item) {
                        item->~Type();
                    }
                }

                operator delete(pointer);
            }
        }

    public:
        static inline SharedPtr make(auto&&... args) {
            return new Type {forward<decltype(args)...>(args)...};
        }

        template <sizetype size>
        static inline SharedPtr make(auto&&... args) {
            auto pointer = (Type*) operator new(size * sizeof(Type));
            auto endAddress = pointer + size;

            for (Type* item = pointer; item != endAddress; ++item) {
                new (item) Type {forward<decltype(args)...>(args)...};
            }

            return {pointer, endAddress};
        }

        inline SharedPtr() noexcept : SharedPtrImpl(nullptr) {}

        inline SharedPtr(nulltype pointer) : SharedPtrImpl(static_cast<void*>(pointer)) {}

        inline SharedPtr(const SharedPtr<Type>& other) noexcept : SharedPtrImpl(other) {}

        inline SharedPtr(SharedPtr<Type>&& other) noexcept : SharedPtrImpl(other) {}

    private:
        inline SharedPtr(Type* pointer) : SharedPtrImpl(static_cast<void*>(pointer)) {}

        inline SharedPtr(Type* pointer, Type* endAddress) : SharedPtrImpl(static_cast<void*>(pointer), static_cast<void*>(endAddress)) {}

    public:
        inline ~SharedPtr() noexcept {
            release();
        }

        E_RET_NO_DISCARD() E_RET_NONNULL()
        inline Type* get() const noexcept {
            nullPointerCheck();
            return static_cast<Type*>(pointer);
        }

        E_RET_NO_DISCARD() E_RET_NULLABLE_IF("pointer == null")
        inline Type* raw() const noexcept {
            return static_cast<Type*>(pointer);
        }

        E_RET_NO_DISCARD()
        inline const SharedPtr* address() const noexcept {
            return this;
        }

        E_RET_NO_DISCARD()
        inline Type* end() const noexcept {
            return static_cast<Type*>(endAddress);
        }

        inline void release() const noexcept {
            release0(destroy);
        }

        E_RET_NO_DISCARD()
        inline Type* operator+(sizetype offset) const noexcept {
            return raw() + offset;
        }

        E_RET_NO_DISCARD()
        inline Type* operator-(sizetype offset) const noexcept {
            return raw() - offset;
        }

        E_RET_NO_DISCARD()
        inline Type* operator->() const {
            return get();
        }

        E_RET_NO_DISCARD()
        inline Type** operator&() const {
            return &raw();
        }

        E_RET_NO_DISCARD()
        inline Type& operator*() const {
            return *get();
        }

        E_RET_NO_DISCARD()
        inline Type& operator[](sizetype offset) const {
            return get()[offset];
        }

        E_RET_NO_DISCARD()
        inline operator Type*() const noexcept {
            return raw();
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

    private:
        inline void nullPointerCheck() const {
            if (pointer == nullptr) throw exceptions::NullPointerException("The pointer is nullptr");
        }
    };
}
