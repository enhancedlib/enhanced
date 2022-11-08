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

#ifdef CXX_LANGUAGE

NAMESPACE_L2_BEGIN(enhanced, core)

template <typename Type>
struct AbstractClass Iterator {
    virtual ~Iterator() noexcept DEFAULT_CONS;

    /*!
     * Determines if there are still elements can iterate over.
     */
    NoIgnoreRet
    virtual bool hasNext() const = 0;

    /*!
     * Let the iterator pointer return to the next element.
     */
    virtual const Iterator<Type>* next() const = 0;

    /*!
     * Usage: while (<list>.each())
     */
    NoIgnoreRet
    virtual bool each() const = 0;

    /*!
     * Gets the current element.
     */
    NoIgnoreRet
    virtual Type& get() const = 0;

    /*!
     * Let the iterator pointer return to the first element.
     */
    virtual void reset() const = 0;

    /*!
     * Gets the number of elements.
     */
    NoIgnoreRet
    virtual sizetype count() const = 0;
};

NAMESPACE_L2_END

#endif
