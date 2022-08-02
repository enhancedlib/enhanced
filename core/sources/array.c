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

void arraySetInt(void* const array, const Size count, int64 value, const Size sizeOfType) {
    arraySet(array, count, &value, sizeOfType);
}

void arraySet(void* const array, const Size count, void* const address, const Size sizeOfType) {
    assert(array != null), assert(count > 0), assert(sizeOfType > 0);

    Size size = count * sizeOfType;

    for (Size index = 0; index < size; ++index) {
        ((byte*) array)[index] = ((byte*) address)[index % sizeOfType];
    }
}

void arrayCopy(void* const destArray, void* const srcArray, const Size count, const Size sizeOfType) {
    memoryCopy(destArray, srcArray, count * sizeOfType);
}
