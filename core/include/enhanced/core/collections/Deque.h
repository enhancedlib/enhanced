/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/collections/Queue.h>

namespace enhanced::core::collections {
    template <typename Type>
    interface Deque : Queue<Type> {
        virtual func getFirst() const -> Type& = abstract;

        virtual func getLast() const -> Type& = abstract;

        virtual void addLast(const Type& element) = abstract;

        virtual func removeLast() -> Type = abstract;

        virtual void addFirst(const Type& element) = abstract;

        virtual func removeFirst() -> Type = abstract;

        virtual void add(const Type& element) = abstract;

        virtual func remove() -> Type = abstract;

        virtual void push(const Type& element) = abstract;

        virtual func popup() -> Type = abstract;
    };
}
