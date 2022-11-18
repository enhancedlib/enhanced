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

#include <initializer_list>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/Iterable.h>

namespace enhanced::core {
    template <typename Type>
    using InitializerList = std::initializer_list<Type>;

    template <typename Type>
    $(NoIgnoreReturn)
    inline constexpr func initListToArray(InitializerList<Type> list) {
        return list.begin();
    }

    template <typename Type>
    $(NoIgnoreReturn)
    inline constexpr func initListConut(InitializerList<Type> list) {
        return list.size();
    }
}
