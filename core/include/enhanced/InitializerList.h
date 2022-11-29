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

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Iterable.h>

namespace enhanced {
    template <typename Type>
    using InitializerList = std::initializer_list<Type>;

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr func initListToArray(const InitializerList<Type>& list) -> const Type* {
        return list.begin();
    }

    template <typename Type>
    $NoIgnoreReturn
    inline constexpr func initListSize(const InitializerList<Type>& list) -> sizetype {
        return list.size();
    }
}
