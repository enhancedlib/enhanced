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

#ifndef ENHANCED_BASIC_GENERIC_ALLOCATOR_TCC
#define ENHANCED_BASIC_GENERIC_ALLOCATOR_TCC

#include "EnhancedBasic/generic/Allocator.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

namespace EnhancedBasic {
    namespace generic {
        template <typename Type>
        $RetNotIgnored()
        Size Allocator<Type>::getSize() const {
            return Allocator0::getSize0();
        }

        template <typename Type>
        Type &Allocator<Type>::get(Size index) const {
            return reinterpret_cast<Type *>(Allocator0::space)[index];
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

#endif // !ENHANCED_BASIC_GENERIC_ALLOCATOR_TCC
