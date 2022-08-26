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

#include "enhanced/basic/container/Collection.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::container {
    template <typename Type>
    struct List : public Collection<Type> {
        virtual Type& get(Size index) const = 0;

        virtual Type& operator[](Size index) const = 0;

        RetRequiresRelease
        virtual List<Type>* copy() const = 0;

        virtual void add(const Type& element) = 0;

        virtual Type remove() = 0;
    };
}

#endif // CXX_LANGUAGE
