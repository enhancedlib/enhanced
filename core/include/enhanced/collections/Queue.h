/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
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
