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
    char* str = new char[length + 1];
    str[length] = '\0';
    return str;
}

RetRequiresRelease
char* stringCopy(const char* const string) {
    assert(string != null);

    Size length = stringLength(string);
    char* copy = new char[length + 1];
    memoryCopy(copy, string, length + 1);

    return copy;
}

RetRequiresRelease
char* stringResize(const char* const string, const Size newSize) {
    assert(string != null), assert(newSize > 1);

    Size length = stringLength(string);
    char* copy = new char[newSize];
    memoryCopy(copy, string, length + 1);

    return copy;
}
