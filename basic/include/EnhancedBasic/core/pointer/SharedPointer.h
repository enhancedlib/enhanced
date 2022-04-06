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

#ifndef ENHANCED_BASIC_POINTER_SHARED0POINTER_H
#define ENHANCED_BASIC_POINTER_SHARED0POINTER_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#ifdef CXX_LANGUAGE // C++ language

namespace BasicGenericImpl {
    namespace core {
        namespace pointer {
            class SharedPointerImpl {
            private:
                Size *referenceCount;

            protected:
                void *pointer;

                struct GenericOperator {
                    void (*destroy)(void *ptr);
                };

                GenericOperator genericOperator;

                SharedPointerImpl(void *ptr, GenericOperator genericOperator);

                SharedPointerImpl(const SharedPointerImpl &other);

                virtual ~SharedPointerImpl() noexcept;

                void release0() noexcept;

                void assign0(void *value) noexcept;

                void assign0(const SharedPointerImpl &other) noexcept;
            };
        }
    }
}

namespace EnhancedBasic {
    namespace core {
        namespace pointer {
            template <typename Type>
            class SharedPointer final : private BasicGenericImpl::core::pointer::SharedPointerImpl {
            private:
                using SharedPointerImpl = BasicGenericImpl::core::pointer::SharedPointerImpl;

                static void destroy(void *ptr);

            public:
                SharedPointer(Type *ptr = null);

                SharedPointer(const SharedPointer<Type> &other);

                void release() noexcept;

                $RetNotIgnored()
                SharedPointer<Type> operator+(Size offset) const noexcept;

                $RetNotIgnored()
                SharedPointer<Type> operator-(Size offset) const noexcept;

                $RetNotIgnored()
                Type **operator&() noexcept;

                $RetNotIgnored()
                Type *operator->() noexcept;

                $RetNotIgnored()
                Type &operator*() noexcept;

                $RetNotIgnored()
                Type &operator[](Size offset) noexcept;

                SharedPointer<Type> &operator=(Type *value) noexcept;

                SharedPointer<Type> &operator=(const SharedPointer<Type> &other) noexcept;

                SharedPointer<Type> operator+=(Size offset) noexcept;

                SharedPointer<Type> &operator++() noexcept;

                const SharedPointer<Type> operator++(int) noexcept;

                SharedPointer<Type> operator-=(Size offset) noexcept;

                SharedPointer<Type> &operator--() noexcept;

                const SharedPointer<Type> operator--(int) noexcept;

                $RetNotIgnored()
                operator Type *() noexcept;
            };
        } // namespace pointer
    }
} // namespace EnhancedBasic

#include "EnhancedBasic/core/pointer/SharedPointer.hpp"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_POINTER_SHARED0POINTER_H
