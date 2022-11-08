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
#include <enhanced/core/exception/NullPointerException.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L3_BEGIN(enhanced_internal, core, util)

class ENHANCED_CORE_API SharedPtrImpl {
private:
    sizetype* referenceCount;

protected:
    void* pointer;

    struct GenericOperator {
        void (*destroy)(void* ptr);
    };

    GenericOperator genericOperator;

    SharedPtrImpl(void* ptr, GenericOperator genericOperator);

    SharedPtrImpl(const SharedPtrImpl& other) noexcept;

    SharedPtrImpl(SharedPtrImpl&& other) noexcept;

    virtual ~SharedPtrImpl() noexcept;

    void release0() noexcept;

    void assign0(void* value) noexcept;

    void assign0(const SharedPtrImpl& other) noexcept;

    void assign0(SharedPtrImpl&& other) noexcept;
};

NAMESPACE_L3_END

NAMESPACE_L3_BEGIN(enhanced, core, util)

template <typename Type>
class ENHANCED_CORE_API SharedPtr final : private enhanced_internal::core::util::SharedPtrImpl {
private:
    static void destroy(void* ptr) {
        delete static_cast<Type*>(ptr);
    }

    inline void nullPointerCheck() const {
        if (pointer == null) throw exception::NullPointerException("The pointer is null");
    }

public:
    SharedPtr(Type* ptr = null) : SharedPtrImpl(static_cast<void*>(ptr), {destroy}) {}

    SharedPtr(const SharedPtr<Type>& other) noexcept : SharedPtrImpl(other) {}

    SharedPtr(SharedPtr<Type>&& other) noexcept : SharedPtrImpl(other) {}

    void release() noexcept {
        release0();
    }

    NoIgnoreRet
    SharedPtr<Type> operator+(sizetype offset) const noexcept {
        return static_cast<Type*>(pointer) + offset;
    }

    NoIgnoreRet
    SharedPtr<Type> operator-(sizetype offset) const noexcept {
        return static_cast<Type*>(pointer) - offset;
    }

    NoIgnoreRet
    Type** operator&() noexcept {
        return &static_cast<Type*>(pointer);
    }

    NoIgnoreRet
    Type* operator->() {
        nullPointerCheck();
        return static_cast<Type*>(pointer);
    }

    NoIgnoreRet
    Type& operator*() {
        nullPointerCheck();
        return *static_cast<Type*>(pointer);
    }

    NoIgnoreRet
    Type& operator[](sizetype offset) {
        nullPointerCheck();
        return static_cast<Type*>(pointer)[offset];
    }

    SharedPtr<Type>& operator=(Type* value) noexcept {
        assign0(value);
        return *this;
    }

    SharedPtr<Type>& operator=(const SharedPtr<Type>& other) noexcept {
        assign0(other);
        return *this;
    }

    SharedPtr<Type>& operator=(SharedPtr<Type>&& other) noexcept {
        assign0(other);
        return *this;
    }

    SharedPtr<Type> operator+=(sizetype offset) noexcept {
        SharedPtr<Type> copy = *this;
        static_cast<Type*>(copy.pointer) += offset;
        return copy;
    }

    SharedPtr<Type>& operator++() noexcept {
        return ++static_cast<Type*>(pointer);
    }

    const SharedPtr<Type> operator++(int) noexcept {
        return static_cast<Type*>(pointer)++;
    }

    SharedPtr<Type> operator-=(sizetype offset) noexcept {
        SharedPtr<Type> copy = *this;
        static_cast<Type*>(copy.pointer) -= offset;
        return copy;
    }

    SharedPtr<Type>& operator--() noexcept {
        return --static_cast<Type*>(pointer);
    }

    const SharedPtr<Type> operator--(int) noexcept {
        return static_cast<Type*>(pointer)--;
    }

    NoIgnoreRet
    operator Type*() noexcept {
        return static_cast<Type*>(pointer);
    }
};

NAMESPACE_L3_END

#endif
