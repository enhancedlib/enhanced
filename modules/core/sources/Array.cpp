/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <enhanced/Array.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Memory.h>

namespace enhanced {
    void arrayFill(E_ANNOTATE(InOut) void* array, qword value, sizetype count, sizetype sizeOfType) {
        arrayFillPtr(array, &value, count, sizeOfType);
    }

    void arrayFillPtr(E_ANNOTATE(InOut) void* array, const void* valuePtr, sizetype count, sizetype sizeOfType) {
        if (array == nullptr || valuePtr == nullptr || count == 0 || sizeOfType == 0) return;

        sizetype size = count * sizeOfType;

        for (sizetype index = 0; index < size; ++index) {
            ((byte*) array)[index] = ((byte*) valuePtr)[index % sizeOfType];
        }
    }

    void arrayCopy(E_ANNOTATE(InOut) void* destination, const void* source, sizetype count, sizetype sizeOfType) {
        memoryCopy(destination, source, count * sizeOfType);
    }
}
