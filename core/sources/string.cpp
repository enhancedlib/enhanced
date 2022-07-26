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

#include "enhanced/core/string.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/assert.h"
#include "enhanced/core/memory.h"

RetRequiresRelease()
char* stringNew(const Size length) {
    char* str = new char[length + 1];
    str[length] = '\0';
    return str;
}

RetRequiresRelease()
char* stringCopy(const char* const string) {
    assert(string != null);

    Size length = stringLength(string);
    char* copy = new char[length + 1];
    memoryCopy(copy, string, length);
    return copy;
}

RetRequiresRelease()
char* stringResize(const char* const string, const Size newSize) {
    assert(string != null), assert(newSize > 1);

    char* newString = new char[newSize];
    Size oldStringLen = stringLength(string + 1);
    for (Size index = 0; index < oldStringLen; ++index) {
        newString[index] = string[index];
    }

    return newString;
}
