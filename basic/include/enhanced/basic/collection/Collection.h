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
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"

#include "enhanced/basic/Iterable.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::collection {
    template <typename Type>
    struct Collection : public Iterable<Type> {
        virtual ~Collection() noexcept = default;

        RetCannotIgnored
        virtual Size getLength() const = 0;

        RetCannotIgnored
        virtual bool isEmpty() const = 0;

        RetCannotIgnored
        virtual bool contain(const Type& value) const = 0;

        RetRequiresRelease
        virtual Collection<Type>* copy() const = 0;
    };
}

#endif // CXX_LANGUAGE
