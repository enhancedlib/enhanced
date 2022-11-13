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
#include <enhanced/core/collections/Collection.h>

namespace enhanced::core::collections {
    template <typename Type>
    interface Queue : Collection<Type> {
        $(NoIgnoreReturn)
        virtual func getFirst() const -> Type& = abstract;

        $(NoIgnoreReturn)
        virtual func getLast() const -> Type& = abstract;

        $(NoIgnoreReturn)
        virtual func get(sizetype index) const -> Type& = abstract;

        $(NoIgnoreReturn)
        virtual func operator[](sizetype index) const -> Type& = abstract;

        virtual func addLast(const Type& element) -> void = abstract;

        virtual func removeFirst() -> Type = abstract;

        virtual func add(const Type& element) -> void = abstract;

        virtual func remove() -> Type = abstract;

        virtual func push(const Type& element) -> void = abstract;

        virtual func popup() -> Type = abstract;
    };
}
