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
    interface Queue : Collection<Type> {
        $NoIgnoreReturn
        virtual func indexOf(const Type& value) const -> sizetype abstract;

        $NoIgnoreReturn
        virtual func getFirst() const -> Type& abstract;

        $NoIgnoreReturn
        virtual func getLast() const -> Type& abstract;

        $NoIgnoreReturn
        virtual func get(sizetype index) const -> Type& abstract;

        $NoIgnoreReturn
        virtual func operator[](sizetype index) const -> Type& abstract;

        virtual func addLast(const Type& element) -> void abstract;

        virtual func addLast(Type&& element) -> void abstract;

        virtual inline func push(const Type& element) -> void abstract;

        virtual inline func push(Type&& element) -> void abstract;

        virtual inline func add(const Type& element) -> void abstract;

        virtual inline func add(Type&& element) -> void abstract;

        virtual func removeFirst() -> Type abstract;

        virtual func removeFirstIf() -> bool abstract;

        virtual inline func popup() -> Type abstract;

        virtual inline func remove() -> Type abstract;

        virtual inline func popupIf() -> bool abstract;

        virtual inline func removeIf() -> bool abstract;
    };
}
