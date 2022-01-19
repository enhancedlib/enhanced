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

#ifndef ENHANCED_GENERICS_ALLOCATOR_H
#define ENHANCED_GENERICS_ALLOCATOR_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/annotations.h"

#include "EnhancedBasic/export.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedBasic {
    namespace generic {
        class ENHANCED_BASIC_API Allocator0 {
        private:
            Size size = 0;

        protected:
            void *space = null;

            $RetNotIgnored()
            Size getSize0() const;

            void allocate0(Size newSize, Size sizeOfType);

            void destroy0();

            void resize0(Size resize, Size sizeOfType);
        };

        template <typename Type>
        class Allocator : private Allocator0 {
        public:
            $RetNotIgnored()
            Size getSize() const;

            $RetNotIgnored()
            Type &get(Size index) const;

            void allocate(Size newSize);

            void destroy();

            template <typename ...Args>
            $RetReferenced
            $RetNotIgnored()
            Type &construct(Size index, Args ...args);

            void destruct(Size index);

            template <typename ...Args>
            $RetReferenced
            $RetNotIgnored()
            Type *constructAll(Args ...args);

            void destructAll();

            void resize(Size newSize);
        };
    } // namespace core
} // namespace EnhancedBasic

#include "EnhancedBasic/generic/Allocator.tcc"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_GENERICS_ALLOCATOR_H
