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
#include <enhanced/core/Iterator.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L2_BEGIN(enhanced, core)

template <typename Type>
struct AbstractClass Iterable {
protected:
    class ForeachIterator final {
    private:
        const Iterator<Type>& iterator;

    public:
        explicit ForeachIterator(const Iterator<Type>& iterator) : iterator(iterator) {}

        bool operator!=(byte) const {
            return iterator.hasNext();
        }

        const Iterator<Type>* operator++() const {
            return iterator.next();
        }

        Type& operator*() const {
            return iterator.get();
        }
    };

public:
    NoIgnoreRet
    virtual inline Iterable<Type>::ForeachIterator begin() const {
        return Iterable<Type>::ForeachIterator(iterator());
    }

    NoIgnoreRet
    virtual inline constexpr byte end() const {
        return 0;
    }

    virtual const Iterator<Type>& iterator() const = 0;
};

NAMESPACE_L2_END

#endif
