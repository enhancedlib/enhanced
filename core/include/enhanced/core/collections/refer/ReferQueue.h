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
#include <enhanced/core/collections/Collection.h>
#include <enhanced/core/collections/Queue.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L4_BEGIN(enhanced, core, collections, refer)

template <typename Type>
struct AbstractClass ReferQueue : Queue<Type> {
    RetRequiresRelease
    virtual ReferQueue<Type>* copy() const = 0;
};

NAMESPACE_L4_END

#endif
