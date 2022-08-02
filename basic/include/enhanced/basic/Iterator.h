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

#ifdef CXX_LANGUAGE

namespace enhanced::basic {
    template <typename Type>
    struct Iterator {
        virtual ~Iterator() noexcept = default;

        /*!
         * Determines if there are still elements can iterate over.
         */
        RetCannotIgnored
        virtual bool hasNext() const = 0;

        /*!
         * Let the iterator pointer return to the next element.
         */
        virtual const Iterator<Type>* next() const = 0;

        /*!
         * Usage: while (<list>.each())
         */
        RetCannotIgnored
        virtual bool each() const = 0;

        /*!
         * Gets the current element.
         */
        RetCannotIgnored
        virtual Type& get() const = 0;

        /*!
         * Let the iterator pointer return to the first element.
         */
        virtual void reset() const = 0;

        /*!
         * Gets the number of elements.
         */
        RetCannotIgnored
        virtual Size count() const = 0;
    };
}

#endif // CXX_LANGUAGE
