/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This product is licensed under Enhanced License.
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

#ifndef ENHANCED_BASIC_CORE_ANY_H
#define ENHANCED_BASIC_CORE_ANY_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace Core {
        class Any {
        private:
            void *any;

        public:
            Any() : any(null) {}

            template <typename Type>
            Any(const Type &value) : any((void *) &value) {}

            template <typename Type>
            Any(const Any &originalCopy) : any(originalCopy.any) {}

            template <typename Type>
            bool operator==(const Type &value) {
                return this->cast<Type>() == value;
            }

            template <typename Type>
            Type &cast() {
                return *this;
            }

            template <typename Type>
            operator Type &() const {
                return *static_cast<Type *>(this->any);
            }
        };
    }
} // EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_CORE_ANY_H
