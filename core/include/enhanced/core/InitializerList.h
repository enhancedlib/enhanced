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
#include <enhanced/core/annotations.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/Iterable.h>
#include <enhanced/core/ArrayIterator.h>

#ifdef CXX_LANGUAGE

#include <initializer_list>

NAMESPACE_L2_BEGIN(enhanced, core)

template <typename Type>
class InitializerList : public Iterable<Type> {
private:
    const ArrayIterator<Type> iter;

public:
    constexpr InitializerList(std::initializer_list<Type> list) : iter(ArrayIterator(list.begin(), list.size())) {}

    inline const Type* toArray() const {
        return iter.array;
    }

    inline const sizetype count() {
        return iter.count();
    }

    inline constexpr const Iterator<Type>& iterator() const override {
        iter.reset();
        return iter;
    }
};

NAMESPACE_L2_END

#endif
