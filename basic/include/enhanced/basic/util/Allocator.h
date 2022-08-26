/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#include "enhanced/basic/export.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::generic_impl::util {
    class ENHANCED_BASIC_API Allocator0 {
    private:
        Size size = 0;

    protected:
        void* space = null;

        RetCannotIgnored
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
        RetCannotIgnored
        Size getSize() const {
            return getSize0();
        }

        RetCannotIgnored
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
        RetCannotIgnored
        Type& construct(Size index, Args ...args) {
            Type value = Type(args...);
            memoryCopy(((Type*) space) + index, &value, sizeof(Type));
            return get(index);
        }

        void destruct(Size index) {
            get(index).~Type();
        }

        template <typename ...Args>
        void constructAll(Args ...args) {
            for (Size index = 0; index < getSize(); ++index) {
                Type value = Type(args...);
                memoryCopy(((Type*) space) + index, &value, sizeof(Type));
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
