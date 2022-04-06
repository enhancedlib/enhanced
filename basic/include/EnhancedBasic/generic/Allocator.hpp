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
 * The authors or copyright holders be not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by This software,
 * the authors or copyright holders may provide possible solutions,
 * but it does not mean that the authors or copyright holders
 * will definitely solve the problem.
 * In no event shall the author or copyright
 * owner be liable for any claims, damages or other liabilities.
 *
 * You should see the Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#ifndef ENHANCED_BASIC_GENERIC_ALLOCATOR_HPP
#define ENHANCED_BASIC_GENERIC_ALLOCATOR_HPP

#include "EnhancedBasic/generic/Allocator.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#ifdef CXX_LANGUAGE

namespace EnhancedBasic {
    namespace generic {
        template <typename Type>
        $RetNotIgnored()
        Size Allocator<Type>::getSize() const {
            return Allocator0::getSize0();
        }

        template <typename Type>
        Type &Allocator<Type>::get(Size index) const {
            return ((Type *) Allocator0::space)[index];
        }

        template <typename Type>
        void Allocator<Type>::allocate(Size newSize) {
            Allocator0::allocate0(newSize, sizeof(Type));
        }

        template <typename Type>
        void Allocator<Type>::destroy() {
            Allocator0::destroy0();
        }

        template <typename Type>
        template <typename... Args>
        Type &Allocator<Type>::construct(Size index, Args... args) {
            return this->get(index) = Type(args...);
        }

        template <typename Type>
        void Allocator<Type>::destruct(Size index) {
            this->get(index).~Type();
        }

        template <typename Type>
        template <typename... Args>
        Type *Allocator<Type>::constructAll(Args... args) {
            for (Size index = 0; index < this->getSize(); ++ index) {
                this->get(index) = Type(args...);
            }
        }

        template <typename Type>
        void Allocator<Type>::destructAll() {
            for (Size index = 0; index < this->getSize(); ++ index) {
                this->get(index).~Type();
            }
        }

        template <typename Type>
        void Allocator<Type>::resize(Size newSize) {
            Allocator0::resize0(newSize, sizeof(Type));
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_GENERIC_ALLOCATOR_HPP
