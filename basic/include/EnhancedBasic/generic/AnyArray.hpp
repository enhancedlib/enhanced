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
