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

#include <enhanced/core/math/math.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>

namespace enhanced::core::math {
    template <typename NumberType>
    NumberType abs(NumberType number) {
        return (number < 0) ? -number : number;
    }

    template int8 abs(int8 number);
    template int16 abs(int16 number);
    template int32 abs(int32 number);
    template int64 abs(int64 number);
}
