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
            $RetReferenced $RetNotIgnored()
            Type &construct(Size index, Args ...args);

            void destruct(Size index);

            template <typename ...Args>
            $RetReferenced $RetNotIgnored()
            Type *constructAll(Args ...args);

            void destructAll();

            void resize(Size newSize);
        };
    } // namespace core
} // namespace EnhancedBasic

#include "EnhancedBasic/generic/Allocator.hpp"

#endif // CXX_LANGUAGE

#endif // !ENHANCED_GENERICS_ALLOCATOR_H
