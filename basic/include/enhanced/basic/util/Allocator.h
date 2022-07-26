/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#include "enhanced/basic/export.h"

#ifdef CXX_LANGUAGE // C++ language

namespace enhanced::basic::generic_impl::util {
    class ENHANCED_BASIC_API Allocator0 {
    private:
        Size size = 0;

    protected:
        void* space = null;

        RetCannotIgnored()
        Size getSize0() const;

        void allocate0(Size newSize, Size sizeOfType);

        void destroy0();

        void resize0(Size resize, Size sizeOfType);
    };
}

namespace enhanced::basic::util {
    template <typename Type>
    class Allocator : private enhanced::basic::generic_impl::util::Allocator0 {
    public:
        RetCannotIgnored()
        Size getSize() const {
            return getSize0();
        }

        RetCannotIgnored()
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
        ReferReturn RetCannotIgnored()
        Type& construct(Size index, Args ...args) {
            return get(index) = Type(args...);
        }

        void destruct(Size index) {
            get(index).~Type();
        }

        template <typename ...Args>
        ReferReturn RetCannotIgnored()
        Type* constructAll(Args ...args) {
            for (Size index = 0; index < getSize(); ++index) {
                get(index) = Type(args...);
            }
        }

        void destructAll() {
            for (Size index = 0; index < getSize(); ++index) {
                get(index).~Type();
            }
        }

        void resize(Size newSize) {
            resize0(newSize, sizeof(Type));
        }
    };
}

#endif // CXX_LANGUAGE
