/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
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
        [[RetNotIgnored]]
        virtual sizetype indexOf(const Type& value) const = 0;

        [[RetNotIgnored]]
        virtual Type& getFirst() const = 0;

        [[RetNotIgnored]]
        virtual Type& getLast() const = 0;

        [[RetNotIgnored]]
        virtual Type& get(sizetype index) const = 0;

        [[RetNotIgnored]]
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
