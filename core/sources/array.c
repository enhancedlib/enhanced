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

#include "enhanced/core/array.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/assert.h"
#include "enhanced/core/memory.h"

RetRequiresRelease
void* arrayNew(const Size length, const Size sizeOfType) {
    return memoryAlloc(length * sizeOfType);
}

void arraySet(void* const array, const Size count, int64 value, const Size sizeOfType) {
    arraySetPtr(array, count, &value, sizeOfType);
}

void arraySetPtr(void* const array, const Size count, void* const valuePtr, const Size sizeOfType) {
    assert(array != null), assert(count > 0), assert(sizeOfType > 0);

    Size size = count * sizeOfType;

    for (Size index = 0; index < size; ++index) {
        ((byte*) array)[index] = ((byte*) valuePtr)[index % sizeOfType];
    }
}

void arrayCopy(void* const destArray, void* const srcArray, const Size count, const Size sizeOfType) {
    memoryCopy(destArray, srcArray, count * sizeOfType);
}
