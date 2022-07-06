/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#pragma once

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"

#ifdef CXX_LANGUAGE // C++ language

namespace Enhanced::basic::core {
    template <typename Type>
    struct Iterator {
        virtual ~Iterator() noexcept = default;

        /*!
         * Determines if there are still elements can iterate over.
         */
        RetNotIgnored()
        virtual bool hasNext() const = 0;

        /*!
         * Let the iterator pointer return to the next element.
         */
        virtual const Iterator<Type>* next() const = 0;

        /*!
         * Usage: while (<list>.each())
         */
        RetNotIgnored()
        virtual bool each() const = 0;

        /*!
         * Gets the current element.
         */
        RetNotIgnored()
        virtual Type& get() const = 0;

        /*!
         * Let the iterator pointer return to the first element.
         */
        virtual void reset() const = 0;

        /*!
         * Gets the number of elements.
         */
        RetNotIgnored()
        virtual Size count() const = 0;
    };
}

#endif // CXX_LANGUAGE
