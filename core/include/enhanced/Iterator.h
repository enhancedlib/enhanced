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

namespace enhanced {
    template <typename Type>
    struct Iterator {
        virtual ~Iterator() noexcept = default;

        [[RetNotIgnored]]
        virtual bool isBegin() const = 0;

        [[RetNotIgnored]]
        virtual bool isEnd() const = 0;

        /*!
         * Determines if there are still elements can iterate over.
         */
        [[RetNotIgnored]]
        virtual bool hasNext() const = 0;

        /*!
         * Let the iterator pointer return to the next element.
         */
        [[ReturnSelf]]
        virtual const Iterator<Type>& next() const = 0;

        /*!
         * Let the iterator pointer return to the next element.
         */
        [[ReturnSelf]]
        virtual const Iterator<Type>& prev() const = 0;

        /*!
         * Gets the current element.
         */
        [[RetNotIgnored]]
        virtual Type& get() const = 0;

        /*!
         * Let the iterator pointer return to the first element.
         */
        virtual void reset() const = 0;

        /*!
         * Gets the number of elements.
         */
        [[RetNotIgnored]]
        virtual sizetype count() const = 0;

        [[RetNotIgnored]]
        inline bool operator!=(byte) const {
            return !isEnd();
        }

        [[ReturnSelf]]
        inline const Iterator<Type>& operator++() const {
            return next();
        }

        [[RetNotIgnored]]
        inline Type& operator*() const {
            return get();
        }
    };
}
