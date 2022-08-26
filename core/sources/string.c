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

#include "enhanced/core/string.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/assert.h"
#include "enhanced/core/memory.h"

RetRequiresRelease
char* stringNew(const Size length) {
    char* str = (char*) memoryAlloc((length + 1) * sizeof(char));
    if (str == null) {
        return null;
    }
    str[length] = '\0';

    return str;
}

RetCannotIgnored
Size stringLength(const char* const string) {
    assert(string != null);

    Size length;
    for (length = 0; string[length] != '\0'; ++length) {}

    return length;
}

RetCannotIgnored
bool stringEqual(const char* const string1, const char* const string2) {
    Size length;

    if (string1 == string2) {
        return true;
    } else if ((length = stringLength(string1)) == stringLength(string2)) {
        for (Size index = 0; index < length; ++index) {
            if (string1[index] != string2[index]) {
                return false;
            }
        }
        return true;
    } else {
        return false;
    }
}

RetRequiresRelease
char* stringCopy(const char* const string) {
    assert(string != null);

    Size length = stringLength(string);
    char* copy = stringNew(length);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, string, length + 1);

    return copy;
}

RetRequiresRelease
char* stringResize(const char* const string, const Size newSize) {
    assert(string != null), assert(newSize > 1);

    Size length = stringLength(string);
    char* copy = stringNew(newSize);
    if (copy == null) {
        return null;
    }

    memoryCopy(copy, string, length + 1);

    return copy;
}
