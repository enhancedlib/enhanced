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
#include <enhanced/core/util/traits.h>
#include <enhanced/core/exception/NullPointerException.h>
#include <enhanced/core/exception/NotImplementedError.h>

namespace enhancedInternal::core::util {
    class ENHANCED_CORE_API SharedPtrImpl {
    private:
        sizetype* referenceCount;

    protected:
        void* pointer;

        struct GenericOperator {
            func (*destroy)(void* ptr) -> void;
        };

        GenericOperator genericOperator;

        SharedPtrImpl(void* ptr, GenericOperator genericOperator);

        SharedPtrImpl(const SharedPtrImpl& other) noexcept;

        SharedPtrImpl(SharedPtrImpl&& other) noexcept;

        virtual ~SharedPtrImpl() noexcept;

        func release0() noexcept -> void;

        func assign0(void* value) noexcept -> void;

        func assign0(const SharedPtrImpl& other) noexcept -> void;

        func assign0(SharedPtrImpl&& other) noexcept -> void;
    };
}

namespace enhanced::core::util {
    template <typename Type>
    class ENHANCED_CORE_API SharedPtr final : private enhancedInternal::core::util::SharedPtrImpl {
    private:
        static func destroy(void* ptr) -> void {
            delete static_cast<Type*>(ptr);
        }

        inline func nullPointerCheck() const -> void {
            if (pointer == null) throw exception::NullPointerException("The pointer is null");
        }

        SharedPtr(Type* ptr) : SharedPtrImpl(static_cast<void*>(ptr), {destroy}) {}

    public:
        template <typename... Args>
        static func make(Args... args) -> SharedPtr {
            return SharedPtr(new Type(args...));
        }

        template <sizetype size, typename... Args>
        static func make(Args... args) -> SharedPtr {
            NOT_IMPLEMENTED();
        }

        SharedPtr() : SharedPtrImpl(null, {destroy}) {}

        SharedPtr(nulltype ptr) : SharedPtrImpl(static_cast<void*>(ptr), {destroy}) {}

        SharedPtr(const SharedPtr<Type>& other) noexcept : SharedPtrImpl(other) {}

        SharedPtr(SharedPtr<Type>&& other) noexcept : SharedPtrImpl(other) {}

        func addressOf() const noexcept -> const SharedPtr* {
            return this;
        }

        func release() noexcept -> void {
            release0();
        }

        $(NoIgnoreReturn)
        func operator+(sizetype offset) const noexcept -> Type* {
            return static_cast<Type*>(pointer) + offset;
        }

        $(NoIgnoreReturn)
        func operator-(sizetype offset) const noexcept -> Type* {
            return static_cast<Type*>(pointer) - offset;
        }

        $(NoIgnoreReturn)
        func operator&() noexcept -> Type** {
            return &static_cast<Type*>(pointer);
        }

        $(NoIgnoreReturn)
        func operator->() -> Type* {
            nullPointerCheck();
            return static_cast<Type*>(pointer);
        }

        $(NoIgnoreReturn)
        func operator*() -> Type& {
            nullPointerCheck();
            return *static_cast<Type*>(pointer);
        }

        $(NoIgnoreReturn)
        func operator[](sizetype offset) -> Type& {
            nullPointerCheck();
            return static_cast<Type*>(pointer)[offset];
        }

        func operator=(const SharedPtr<Type>& other) noexcept -> SharedPtr<Type>& {
            assign0(other);
            return *this;
        }

        func operator=(SharedPtr<Type>&& other) noexcept -> SharedPtr<Type>& {
            assign0(other);
            return *this;
        }

        $(NoIgnoreReturn)
        operator Type*() noexcept {
            return static_cast<Type*>(pointer);
        }
    };
}
