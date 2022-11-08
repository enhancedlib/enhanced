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
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/Iterable.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L3_BEGIN(enhanced, core, collections)

template <typename Type>
struct AbstractClass Collection : Iterable<Type> {
    virtual ~Collection() noexcept DEFAULT_CONS;

    NoIgnoreRet
    virtual sizetype getSize() const = 0;

    NoIgnoreRet
    virtual bool isEmpty() const = 0;

    NoIgnoreRet
    virtual bool contain(const Type& value) const = 0;

    RetRequiresRelease
    virtual Collection<Type>* copy() const = 0;
};

ENHANCED_CORE_API extern sizetype ARRAY_INIT_SIZE; // Default value: 255

NAMESPACE_L3_END

#endif
