/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#pragma once

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedGenericImpl::basic::core::pointer {
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

namespace Enhanced::basic::core::pointer {
    template <typename Type>
    class SharedPointer final : private EnhancedGenericImpl::basic::core::pointer::SharedPointerImpl {
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

        RetNotIgnored()
        SharedPointer<Type> operator+(Size offset) const noexcept {
            return static_cast<Type*>(pointer) + offset;
        }

        RetNotIgnored()
        SharedPointer<Type> operator-(Size offset) const noexcept {
            return static_cast<Type*>(pointer) - offset;
        }

        RetNotIgnored()
        Type** operator&() noexcept {
            return &static_cast<Type*>(pointer);
        }

        RetNotIgnored()
        Type* operator->() noexcept {
            return static_cast<Type*>(pointer);
        }

        RetNotIgnored()
        Type& operator*() noexcept {
            return *static_cast<Type*>(pointer);
        }

        RetNotIgnored()
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

        RetNotIgnored()
        operator Type*() noexcept {
            return static_cast<Type*>(pointer);
        }
    };;
}

#endif // CXX_LANGUAGE
