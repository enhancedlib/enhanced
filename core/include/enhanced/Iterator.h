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

namespace enhanced {
    template <typename Type>
    struct Iterator {
        virtual ~Iterator() noexcept = default;

        $NoIgnoreReturn
        virtual bool isBegin() const = 0;

        $NoIgnoreReturn
        virtual bool isEnd() const = 0;

        /*!
         * Determines if there are still elements can iterate over.
         */
        $NoIgnoreReturn
        virtual bool hasNext() const = 0;

        /*!
         * Let the iterator pointer return to the next element.
         */
        $RetSelf
        virtual const Iterator<Type>& next() const = 0;

        /*!
         * Let the iterator pointer return to the next element.
         */
        $RetSelf
        virtual const Iterator<Type>& prev() const = 0;

        /*!
         * Gets the current element.
         */
        $NoIgnoreReturn
        virtual Type& get() const = 0;

        /*!
         * Let the iterator pointer return to the first element.
         */
        virtual void reset() const = 0;

        /*!
         * Gets the number of elements.
         */
        $NoIgnoreReturn
        virtual sizetype count() const = 0;

        $NoIgnoreReturn
        inline bool operator!=(byte) const {
            return !isEnd();
        }

        $RetSelf
        inline const Iterator<Type>& operator++() const {
            return next();
        }

        $NoIgnoreReturn
        inline Type& operator*() const {
            return get();
        }
    };
}
