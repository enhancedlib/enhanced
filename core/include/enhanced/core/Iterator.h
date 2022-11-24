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

namespace enhanced::core {
    template <typename Type>
    interface Iterator {
        virtual ~Iterator() noexcept = default;

        /*!
        * Determines if there are still elements can iterate over.
        */
        $(NoIgnoreReturn)
        virtual func hasNext() const -> bool = abstract;

        /*!
        * Let the iterator pointer return to the next element.
        */
        virtual func next() const -> const Iterator<Type>* = abstract;

        /*!
        * Gets the current element.
        */
        $(NoIgnoreReturn)
        virtual func get() const -> Type& = abstract;

        /*!
        * Let the iterator pointer return to the first element.
        */
        virtual func reset() const -> void = abstract;

        /*!
        * Gets the number of elements.
        */
        $(NoIgnoreReturn)
        virtual func count() const -> sizetype = abstract;
    };
}