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

#include <enhanced/Array.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Memory.h>

namespace enhanced {
    void arrayFill($InOut void* array, qword value, sizetype count, sizetype sizeOfType) {
        arrayFillPtr(array, &value, count, sizeOfType);
    }

    void arrayFillPtr($InOut void* array, void* valuePtr, sizetype count, sizetype sizeOfType) {
        if (array == nullptr || count == 0 || sizeOfType == 0) return;

        sizetype size = count * sizeOfType;

        for (sizetype index = 0; index < size; ++index) {
            ((byte*) array)[index] = ((byte*) valuePtr)[index % sizeOfType];
        }
    }

    void arrayCopy($Out void* destination, const void* source, sizetype count, sizetype sizeOfType) {
        memoryCopy(destination, source, count * sizeOfType);
    }
}
