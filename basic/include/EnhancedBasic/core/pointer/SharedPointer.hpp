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

#ifndef ENHANCED_BASIC_POINTER_SHARED0POINTER_HPP
#define ENHANCED_BASIC_POINTER_SHARED0POINTER_HPP

#include "EnhancedBasic/core/pointer/SharedPointer.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

namespace EnhancedBasic {
    namespace core {
        namespace pointer {
            template <typename Type>
            void SharedPointer<Type>::destroy(void *ptr) {
                delete static_cast<Type *>(ptr);
            }

            template <typename Type>
            SharedPointer<Type>::SharedPointer(Type *ptr) :
                SharedPointerImpl(static_cast<void *>(ptr), {destroy}) {}

            template <typename Type>
            SharedPointer<Type>::SharedPointer(const SharedPointer<Type> &other) : SharedPointerImpl(other) {}

            template <typename Type>
            void SharedPointer<Type>::release() noexcept {
                SharedPointerImpl::release0();
            }

            template <typename Type>
            $RetNotIgnored()
            SharedPointer<Type> SharedPointer<Type>::operator+(Size offset) const noexcept {
                return static_cast<Type *>(SharedPointerImpl::pointer) + offset;
            }

            template <typename Type>
            $RetNotIgnored()
            SharedPointer<Type> SharedPointer<Type>::operator-(Size offset) const noexcept {
                return static_cast<Type *>(SharedPointerImpl::pointer) - offset;
            }

            template <typename Type>
            $RetNotIgnored()
            Type **SharedPointer<Type>::operator&() noexcept {
                return &static_cast<Type *>(SharedPointerImpl::pointer);
            }

            template <typename Type>
            $RetNotIgnored()
            Type *SharedPointer<Type>::operator->() noexcept {
                return static_cast<Type *>(SharedPointerImpl::pointer);
            }

            template <typename Type>
            $RetNotIgnored()
            Type &SharedPointer<Type>::operator*() noexcept {
                return *static_cast<Type *>(SharedPointerImpl::pointer);
            }

            template <typename Type>
            $RetNotIgnored()
            Type &SharedPointer<Type>::operator[](Size offset) noexcept {
                return static_cast<Type *>(SharedPointerImpl::pointer)[offset];
            }

            template <typename Type>
            SharedPointer<Type> &SharedPointer<Type>::operator=(Type *value) noexcept {
                SharedPointer::assign0(value);
                return *this;
            }

            template <typename Type>
            SharedPointer<Type> &SharedPointer<Type>::operator=(const SharedPointer<Type> &other) noexcept {
                SharedPointerImpl::assign0(other);
                return *this;
            }

            template <typename Type>
            SharedPointer<Type> SharedPointer<Type>::operator+=(Size offset) noexcept {
                SharedPointer<Type> copy = *this;
                static_cast<Type *>(copy.SharedPointerImpl::pointer) += offset;
                return copy;
            }

            template <typename Type>
            SharedPointer<Type> &SharedPointer<Type>::operator++() noexcept {
                return ++ static_cast<Type *>(SharedPointerImpl::pointer);
            }

            template <typename Type>
            const SharedPointer<Type> SharedPointer<Type>::operator++(int) noexcept {
                return static_cast<Type *>(SharedPointerImpl::pointer) ++;
            }

            template <typename Type>
            SharedPointer<Type> SharedPointer<Type>::operator-=(Size offset) noexcept {
                SharedPointer<Type> copy = *this;
                static_cast<Type *>(copy.SharedPointerImpl::pointer) -= offset;
                return copy;
            }

            template <typename Type>
            SharedPointer<Type> &SharedPointer<Type>::operator--() noexcept {
                return -- static_cast<Type *>(SharedPointerImpl::pointer);
            }

            template <typename Type>
            const SharedPointer<Type> SharedPointer<Type>::operator--(int) noexcept {
                return static_cast<Type *>(SharedPointerImpl::pointer) --;
            }

            template <typename Type>
            $RetNotIgnored()
            SharedPointer<Type>::operator Type *() noexcept {
                return static_cast<Type *>(SharedPointerImpl::pointer);
            }
        }
    }
}

#endif // !ENHANCED_BASIC_POINTER_SHARED0POINTER_HPP
