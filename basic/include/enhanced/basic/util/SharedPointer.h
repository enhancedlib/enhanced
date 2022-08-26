/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::generic_impl::util {
    class SharedPointerImpl {
    private:
        Size* referenceCount;

    protected:
        void* pointer;

        struct GenericOperator {
            void (*destroy)(void* ptr);
        };

        GenericOperator genericOperator;

        SharedPointerImpl(void* ptr, GenericOperator genericOperator);

        SharedPointerImpl(const SharedPointerImpl& other);

        virtual ~SharedPointerImpl() noexcept;

        void release0() noexcept;

        void assign0(void* value) noexcept;

        void assign0(const SharedPointerImpl& other) noexcept;
    };
}

namespace enhanced::basic::util {
    template <typename Type>
    class SharedPointer final : private enhanced::basic::generic_impl::util::SharedPointerImpl {
    private:
        static void destroy(void* ptr) {
            delete static_cast<Type*>(ptr);
        }

    public:
        SharedPointer(Type* ptr = null) : SharedPointerImpl(static_cast<void*>(ptr), {destroy}) {}

        SharedPointer(const SharedPointer<Type>& other) : SharedPointerImpl(other) {}

        void release() noexcept {
            release0();
        }

        RetCannotIgnored
        SharedPointer<Type> operator+(Size offset) const noexcept {
            return static_cast<Type*>(pointer) + offset;
        }

        RetCannotIgnored
        SharedPointer<Type> operator-(Size offset) const noexcept {
            return static_cast<Type*>(pointer) - offset;
        }

        RetCannotIgnored
        Type** operator&() noexcept {
            return &static_cast<Type*>(pointer);
        }

        RetCannotIgnored
        Type* operator->() noexcept {
            return static_cast<Type*>(pointer);
        }

        RetCannotIgnored
        Type& operator*() noexcept {
            return *static_cast<Type*>(pointer);
        }

        RetCannotIgnored
        Type& operator[](Size offset) noexcept {
            return static_cast<Type*>(pointer)[offset];
        }

        SharedPointer<Type>& operator=(Type* value) noexcept {
            assign0(value);
            return *this;
        }

        SharedPointer<Type>& operator=(const SharedPointer<Type>& other) noexcept {
            assign0(other);
            return *this;
        }

        SharedPointer<Type> operator+=(Size offset) noexcept {
            SharedPointer<Type> copy = *this;
            static_cast<Type*>(copy.pointer) += offset;
            return copy;
        }

        SharedPointer<Type>& operator++() noexcept {
            return ++static_cast<Type*>(pointer);
        }

        const SharedPointer<Type> operator++(int) noexcept {
            return static_cast<Type*>(pointer)++;
        }

        SharedPointer<Type> operator-=(Size offset) noexcept {
            SharedPointer<Type> copy = *this;
            static_cast<Type*>(copy.pointer) -= offset;
            return copy;
        }

        SharedPointer<Type>& operator--() noexcept {
            return --static_cast<Type*>(pointer);
        }

        const SharedPointer<Type> operator--(int) noexcept {
            return static_cast<Type*>(pointer)--;
        }

        RetCannotIgnored
        operator Type*() noexcept {
            return static_cast<Type*>(pointer);
        }
    };
}

#endif // CXX_LANGUAGE
