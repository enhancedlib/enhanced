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

#ifndef ENHANCED_GENERICS_ANY0ARRAY_H
#define ENHANCED_GENERICS_ANY0ARRAY_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/assert.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace generic {
        class AnyArray {
        private:
            void *anyArray = null;

        public:
            template <typename Type>
            AnyArray(const Type *value);

            template <typename Type>
            AnyArray(const AnyArray &other);

            template <typename Type>
            Type *cast() const;

            template <typename Type>
            operator Type *() const;

            template <typename Type>
            void copy(Type *destination, Size count) const;

            template <typename Type, typename ...Args>
            void allocate(Size count, Args ...args);

            template <typename Type>
            void destroy();
        };
    } // namespace generic
} // namespace EnhancedBasic

#include "EnhancedBasic/generic/AnyArray.tcc"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_GENERICS_ANY0ARRAY_H
