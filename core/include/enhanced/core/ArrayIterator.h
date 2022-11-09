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
class ArrayIterator : public Iterator<Type> {
protected:
    mutable Type* indexer;

    const Type* end;

    const sizetype size;

public:
    const Type* array;

    template <sizetype size>
    inline ArrayIterator(const Type array[size]) : array(array), end(array + size), size(size) {}

    inline ArrayIterator(const Type* array, sizetype size) : array(array), end(array + size), size(size) {}

    NoIgnoreRet
    inline bool hasNext() const override {
        return indexer != end;
    }

    inline const Iterator<Type>* next() const override {
        ++indexer;
        return this;
    }

    NoIgnoreRet
    Type& get() const override {
        return *indexer;
    }

    void reset() const override {
        indexer = const_cast<Type*>(array);
    }

    NoIgnoreRet
    sizetype count() const override {
        return size;
    }
};

NAMESPACE_L2_END

#endif
