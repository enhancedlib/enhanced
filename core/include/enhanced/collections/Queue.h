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

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/util/Traits.h>
#include <enhanced/collections/Collection.h>

namespace enhanced::collections {
    template <typename Type>
    struct Queue : Collection<Type> {
        $NoIgnoreReturn
        virtual sizetype indexOf(const Type& value) const = 0;

        $NoIgnoreReturn
        virtual Type& getFirst() const = 0;

        $NoIgnoreReturn
        virtual Type& getLast() const = 0;

        $NoIgnoreReturn
        virtual Type& get(sizetype index) const = 0;

        $NoIgnoreReturn
        virtual Type& operator[](sizetype index) const = 0;

        virtual void addLast(const Type& element) = 0;

        virtual void addLast(Type&& element) = 0;

        virtual void push(const Type& element) = 0;

        virtual void push(Type&& element) = 0;

        virtual void add(const Type& element) = 0;

        virtual void add(Type&& element) = 0;

        virtual Type removeFirst() = 0;

        virtual Type popup() = 0;

        virtual Type remove() = 0;

        virtual bool removeFirstIf() = 0;

        virtual bool popupIf() = 0;

        virtual bool removeIf() = 0;
    };
}
