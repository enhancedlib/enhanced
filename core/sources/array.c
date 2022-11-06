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

#include <enhanced/core/array.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/assert.h>
#include <enhanced/core/memory.h>

void arraySet(void* array, Size count, int64 value, Size sizeOfType) {
    arraySetPtr(array, count, &value, sizeOfType);
}

void arraySetPtr(void* array, Size count, void* valuePtr, Size sizeOfType) {
    assert(array != null), assert(count > 0), assert(sizeOfType > 0);

    Size size = count * sizeOfType;

    for (Size index = 0; index < size; ++index) {
        ((byte*) array)[index] = ((byte*) valuePtr)[index % sizeOfType];
    }
}

void arrayCopy(void* destArray, void* srcArray, Size count, Size sizeOfType) {
    memoryCopy(destArray, srcArray, count * sizeOfType);
}
