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

#ifndef ENHANCED_BASIC_CORE_ANY_HPP
#define ENHANCED_BASIC_CORE_ANY_HPP

#include "EnhancedBasic/generic/Any.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#ifdef CXX_LANGUAGE

namespace EnhancedBasic {
    namespace generic {
        Any::Any() : any(null) {}

        template <typename Type>
        Any::Any(const Type &value) : any((void *) &value) {}

        template <typename Type>
        Any::Any(const Any &other) : any(other.any) {}

        template <typename Type>
        $RetNotIgnored()
        bool Any::operator==(const Type &value) const {
            return this->cast<Type>() == value;
        }

        template <typename Type>
        $RetNotIgnored()
        bool Any::operator!=(const Type &value) const {
            return this->cast<Type>() != value;
        }

        template <typename Type>
        void Any::copy(Type &destination) const {
            destination = this->cast<Type>();
        }

        template <typename Type>
        $RetNotIgnored()
        Type &Any::cast() const {
            return *this;
        }

        template <typename Type>
        $RetNotIgnored()
        Any::operator Type &() const {
            return *static_cast<Type *>(this->any);
        }

        template <typename Type, typename... Args>
        void Any::allocate(Args... args) {
            this->any = new Type(args...);
        }

        template <typename Type>
        void Any::destroy() const {
            delete static_cast<Type *>(this->any);
        }
    }
}

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_CORE_ANY_HPP
