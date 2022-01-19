/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#ifndef ENHANCED_BASIC_POINTER_SHARED0POINTER_TCC
#define ENHANCED_BASIC_POINTER_SHARED0POINTER_TCC

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
                SharedPointer0(static_cast<void *>(ptr), {destroy}) {}

            template <typename Type>
            SharedPointer<Type>::SharedPointer(const SharedPointer<Type> &other) : SharedPointer0(other) {}

            template <typename Type>
            void SharedPointer<Type>::release() noexcept {
                SharedPointer0::release0();
            }

            template <typename Type>
            $RetNotIgnored()
            SharedPointer<Type> SharedPointer<Type>::operator+(Size offset) const noexcept {
                return static_cast<Type *>(SharedPointer0::pointer) + offset;
            }

            template <typename Type>
            $RetNotIgnored()
            SharedPointer<Type> SharedPointer<Type>::operator-(Size offset) const noexcept {
                return static_cast<Type *>(SharedPointer0::pointer) - offset;
            }

            template <typename Type>
            $RetNotIgnored()
            Type **SharedPointer<Type>::operator&() noexcept {
                return &static_cast<Type *>(SharedPointer0::pointer);
            }

            template <typename Type>
            $RetNotIgnored()
            Type *SharedPointer<Type>::operator->() noexcept {
                return static_cast<Type *>(SharedPointer0::pointer);
            }

            template <typename Type>
            $RetNotIgnored()
            Type &SharedPointer<Type>::operator*() noexcept {
                return *static_cast<Type *>(SharedPointer0::pointer);
            }

            template <typename Type>
            $RetNotIgnored()
            Type &SharedPointer<Type>::operator[](Size offset) noexcept {
                return static_cast<Type *>(SharedPointer0::pointer)[offset];
            }

            template <typename Type>
            SharedPointer<Type> &SharedPointer<Type>::operator=(Type *value) noexcept {
                SharedPointer::assign0(value);
                return *this;
            }

            template <typename Type>
            SharedPointer<Type> &SharedPointer<Type>::operator=(const SharedPointer<Type> &other) noexcept {
                SharedPointer0::assign0(other);
                return *this;
            }

            template <typename Type>
            SharedPointer<Type> SharedPointer<Type>::operator+=(Size offset) noexcept {
                SharedPointer<Type> copy = *this;
                static_cast<Type *>(copy.SharedPointer0::pointer) += offset;
                return copy;
            }

            template <typename Type>
            SharedPointer<Type> &SharedPointer<Type>::operator++() noexcept {
                return ++ static_cast<Type *>(SharedPointer0::pointer);
            }

            template <typename Type>
            const SharedPointer<Type> SharedPointer<Type>::operator++(int) noexcept {
                return static_cast<Type *>(SharedPointer0::pointer) ++;
            }

            template <typename Type>
            SharedPointer<Type> SharedPointer<Type>::operator-=(Size offset) noexcept {
                SharedPointer<Type> copy = *this;
                static_cast<Type *>(copy.SharedPointer0::pointer) -= offset;
                return copy;
            }

            template <typename Type>
            SharedPointer<Type> &SharedPointer<Type>::operator--() noexcept {
                return -- static_cast<Type *>(SharedPointer0::pointer);
            }

            template <typename Type>
            const SharedPointer<Type> SharedPointer<Type>::operator--(int) noexcept {
                return static_cast<Type *>(SharedPointer0::pointer) --;
            }

            template <typename Type>
            $RetNotIgnored()
            SharedPointer<Type>::operator Type *() noexcept {
                return static_cast<Type *>(SharedPointer0::pointer);
            }
        }
    }
}

#endif // !ENHANCED_BASIC_POINTER_SHARED0POINTER_TCC
