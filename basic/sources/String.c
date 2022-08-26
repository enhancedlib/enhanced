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

#include "enhanced/basic/String.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/assert.h"
#include "enhanced/core/memory.h"
#include "enhanced/core/string.h"

/*!
 * Get the length of the string.
 *
 * @param self The string.
 * @return
 */
static Size getLength(const String* self);

/*!
 * To concatenate the current string with another string.
 *
 * @param self The string.
 * @param string
 * @return String
 */
static String add(String* self, String string);

String newEmptyString() {
    char* value = (char*) memoryAlloc(sizeof(char));
    *value = '\0';
    return newStringExt(value, 0);
}

String toString(char* const value) {
    return newStringExt(value, stringLength(value));
}

String newString(const Size length) {
    char* value = (char*) memoryAlloc((length + 1) * sizeof(char));
    return newStringExt(value, length);
}

String newStringExt(const char* const value, const Size length) {
    String string = {
        .value = (char*) value,
        .length = length,
        .getLength = getLength,
        .add = add
    };
    return string;
}

Size getLength(const String* self) {
    return self->length;
}

String add(String* self, String string) {
    assert(self != null), assert(string.length > 0);

    Size newLength = self->length + string.length;
    char* newString = stringNew(newLength + 1);
    if (newString == null) {
        return *self;
    }

    memoryCopy(newString, self->value, newLength);
    memoryCopy(newString + self->length, string.value, newLength);

    memoryFree(self->value);

    self->length = newLength;
    self->value = newString;

    return *self;
}
