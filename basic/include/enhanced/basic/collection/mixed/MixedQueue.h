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

#include "enhanced/basic/collection/Collection.h"
#include "enhanced/basic/collection/Queue.h"

#ifdef CXX_LANGUAGE // C++ language

namespace enhanced::basic::collection::mixed {
    template <typename Type>
    struct MixedQueue : public Queue<Type> {
        virtual MixedQueue<Type>* copy() const = 0;

        virtual void addLastReference(const Type& element) = 0;

        virtual void addReference(const Type& element) = 0;

        virtual void pushReference(const Type& element) = 0;
    };
}

#endif // CXX_LANGUAGE
