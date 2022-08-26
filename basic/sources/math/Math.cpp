/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include "enhanced/basic/math/Math.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"

using enhanced::basic::math::Math;

template <typename NumberType, typename ReturnType>
ReturnType Math::abs(NumberType number) {
    return (number < 0) ? -number : number;
}

template <> uint8 Math::abs(int8 number);
template <> uint16 Math::abs(int16 number);
template <> uint32 Math::abs(int32 number);
template <> uint64 Math::abs(int64 number);
