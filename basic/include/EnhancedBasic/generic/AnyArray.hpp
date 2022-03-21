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

#ifndef ENHANCED_BASIC_GENERIC_ANY0ARRAY_HPP
#define ENHANCED_BASIC_GENERIC_ANY0ARRAY_HPP

#include "EnhancedBasic/generic/AnyArray.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#ifdef CXX_LANGUAGE

namespace EnhancedBasic {
    namespace generic {
        template <typename Type>
        AnyArray::AnyArray(const Type *value) : anyArray((void *) value) {}

        template <typename Type>
        AnyArray::AnyArray(const AnyArray &copy) : anyArray(copy) {}

        template <typename Type>
        Type *AnyArray::cast() const {
            return *this;
        }

        template <typename Type>
        AnyArray::operator Type *() const {
            return static_cast<Type *>(this->anyArray);
        }

        template <typename Type>
        void AnyArray::copy(Type *destination, const Size count) const {
            assert(count > 0);

            for (Size index = 0; index < count; ++ index) {
                destination[index] = this->cast<Type *>()[index];
            }
        }

        template <typename Type, typename... Args>
        void AnyArray::allocate(const Size count, Args... args) {
            assert(count > 0);

            Type *array = static_cast<Type *>(operator new(count));
            for (Size index = 0; index < count; ++ index) {
                array[index] = new Type(args...);
            }
        }

        template <typename Type>
        void AnyArray::destroy() {
            delete[] static_cast<Type *>(this->anyArray);
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_GENERIC_ANY0ARRAY_HPP
