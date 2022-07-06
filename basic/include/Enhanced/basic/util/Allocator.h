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

#pragma once

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"

#include "Enhanced/basic/export.h"

#ifdef CXX_LANGUAGE // C++ language

namespace EnhancedGenericImpl::basic::util {
    class ENHANCED_BASIC_API Allocator0 {
    private:
        Size size = 0;

    protected:
        void* space = null;

        RetNotIgnored()
        Size getSize0() const;

        void allocate0(Size newSize, Size sizeOfType);

        void destroy0();

        void resize0(Size resize, Size sizeOfType);
    };
}

namespace Enhanced::basic::util {
    template <typename Type>
    class Allocator : private EnhancedGenericImpl::basic::util::Allocator0 {
    public:
        RetNotIgnored()
        Size getSize() const {
            return getSize0();
        }

        RetNotIgnored()
        Type& get(Size index) const {
            return ((Type*) space)[index];
        }

        void allocate(Size newSize) {
            allocate0(newSize, sizeof(Type));
        }

        void destroy() {
            destroy0();
        }

        template <typename ...Args>
        ReferReturn RetNotIgnored()
        Type& construct(Size index, Args ...args) {
            return get(index) = Type(args...);
        }

        void destruct(Size index) {
            get(index).~Type();
        }

        template <typename ...Args>
        ReferReturn RetNotIgnored()
        Type* constructAll(Args ...args) {
            for (Size index = 0; index < getSize(); ++ index) {
                get(index) = Type(args...);
            }
        }

        void destructAll() {
            for (Size index = 0; index < getSize(); ++ index) {
                get(index).~Type();
            }
        }

        void resize(Size newSize) {
            resize0(newSize, sizeof(Type));
        }
    };
}

#endif // CXX_LANGUAGE
