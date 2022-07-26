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
 *
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
