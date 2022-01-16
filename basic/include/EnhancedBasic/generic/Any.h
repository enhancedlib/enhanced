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

#ifndef ENHANCED_BASIC_CORE_ANY_H
#define ENHANCED_BASIC_CORE_ANY_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace generic {
        class Any {
        private:
            void *any;

        public:
            Any() : any(null) {}

            template <typename Type>
            Any(const Type &value) : any((void *) &value) {}

            template <typename Type>
            Any(const Any &copy) : any(copy.any) {}

            template <typename Type>
            bool operator==(const Type &value) const {
                return this->cast<Type>() == value;
            }

            template <typename Type>
            bool operator!=(const Type &value) const {
                return this->cast<Type>() != value;
            }

            bool operator==(const Any &value) const {
                return this == &value;
            }

            bool operator!=(const Any &value) const {
                return this != &value;
            }

            template <typename Type>
            void copy(Type &destination) const {
                destination = this->cast<Type>();
            }

            template <typename Type>
            Type &cast() const {
                return *this;
            }

            template <typename Type>
            operator Type &() const {
                return *static_cast<Type *>(this->any);
            }

            template <typename Type, typename ...Args>
            void allocate(Args ...args) {
                this->any = new Type(args...);
            }

            template <typename Type>
            void destroy() const {
                delete static_cast<Type *>(this->any);
            }
        };
    } // namespace generic
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_CORE_ANY_H
