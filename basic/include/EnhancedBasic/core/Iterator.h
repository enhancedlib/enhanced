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

#ifndef ENHANCED_BASIC_CORE_ITERATOR_H
#define ENHANCED_BASIC_CORE_ITERATOR_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace core {
        template <typename Type>
        struct Iterator {
        #ifdef CXX_11_OR_MORE
            virtual ~Iterator() noexcept = default;
        #else // below C++11
            virtual ~Iterator() {}
        #endif // CXX_11_OR_MORE

            $RetNotIgnored()
            virtual bool hasNext() const = 0;

            virtual const Iterator<Type> *next() const = 0;

            $RetNotIgnored()
            virtual bool each() const = 0;

            $RetNotIgnored()
            virtual Type &get() const = 0;

            virtual void reset() const = 0;

            $RetNotIgnored()
            virtual Size count() const = 0;
        };
    } // namespace core
} // namespace EnhancedBasic

#endif // CXX_LANGUAGE

#endif // !ENHANCED_BASIC_CORE_ITERATOR_H
