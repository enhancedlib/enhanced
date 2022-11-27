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

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Iterator.h>

namespace enhanced {
    template <typename Type>
    class ArrayIterator : public Iterator<Type> {
    protected:
        mutable Type* indexer;

        const Type* end;

        const sizetype size;

    public:
        const Type* array;

        template <sizetype size>
        inline constexpr ArrayIterator(const Type array[size]) : end(array + size), size(size), array(array) {}

        inline constexpr ArrayIterator(const Type* array, sizetype size) : end(array + size), size(size), array(array) {}

        $NoIgnoreReturn
        inline func hasNext() const -> bool override {
            return indexer != end;
        }

        inline func next() const -> const Iterator<Type>* override {
            ++indexer;
            return this;
        }

        $NoIgnoreReturn
        func get() const -> Type& override {
            return *indexer;
        }

        func reset() const -> void override {
            indexer = const_cast<Type*>(array);
        }

        $NoIgnoreReturn
        func count() const -> sizetype override {
            return size;
        }
    };
}
