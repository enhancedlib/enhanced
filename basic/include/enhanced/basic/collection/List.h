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

#include "Collection.h"

#ifdef CXX_LANGUAGE // C++ language

namespace enhanced::basic::collection {
    template <typename Type>
    struct List : public Collection<Type> {
        virtual Type& get(Size index) const = 0;

        virtual Type& operator[](Size index) const = 0;

        RetRequiresRelease()
        virtual List<Type>* copy() const = 0;

        virtual void add(const Type& element) = 0;

        virtual Type remove() = 0;
    };
}

#endif // CXX_LANGUAGE
