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

#include "Queue.h"

#ifdef CXX_LANGUAGE

namespace enhanced::basic::collection {
    template <typename Type>
    struct Deque : public Queue<Type> {
        virtual Type& getFirst() const = 0;

        virtual Type& getLast() const = 0;

        RetRequiresRelease
        virtual Deque<Type>* copy() const = 0;

        virtual void addLast(const Type& element) = 0;

        virtual Type removeLast() = 0;

        virtual void addFirst(const Type& element) = 0;

        virtual Type removeFirst() = 0;

        virtual void add(const Type& element) = 0;

        virtual Type remove() = 0;

        virtual void push(const Type& element) = 0;

        virtual Type popup() = 0;
    };
}

#endif // CXX_LANGUAGE
