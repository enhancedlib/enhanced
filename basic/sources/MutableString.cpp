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

#include "enhanced/basic/MutableString.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"
#include "enhanced/core/memory.h"
#include "enhanced/core/string.h"

#include "enhanced/basic/String.h"

using enhanced::basic::MutableString;
using enhanced::basic::String;

MutableString::MutableString(NotNull const char* value) : String(stringCopy(value)) {}

MutableString::MutableString(NotNull char* value) : String(stringCopy(value)) {}

MutableString::MutableString(Size length) : String(stringNew(length)) {}

MutableString::MutableString(const MutableString& other) : String(stringCopy(other)) {}

MutableString::~MutableString() noexcept {
    delete[] value;
}

char& MutableString::at(Size index) const {
    return value[index];
}

char& MutableString::operator[](Size index) const {
    return value[index];
}

MutableString& MutableString::append(const MutableString& string) {
    if (string.length < 1) {
        return *this;
    }

    Size newLength = length + string.length;
    char* newMutableString = new char[newLength + 1];
    newMutableString[newLength] = '\0';

    memoryCopy(newMutableString, value, newLength);
    memoryCopy(newMutableString + length, string.value, newLength);

    delete[] value;

    length = newLength;
    value = newMutableString;
    shallowClone = false;

    return *this;
}

MutableString& MutableString::replace(const char oldChar, const char newChar) {
    return *this;
}

MutableString& MutableString::replace(const MutableString& oldSubstring, const MutableString& newSubstring) {
    return *this;
}

MutableString& MutableString::replace(char oldChar, const MutableString& newSubstring) {
    return *this;
}

MutableString& MutableString::replace(const MutableString& oldSubstring, char newChar) {
    return *this;
}

MutableString& MutableString::toUppercase() {
    for (Size index = 0; index < length; ++index) {
        if (value[index] >= 'a' && value[index] <= 'z') {
            (value[index] -= 'a') += 'A';
        }
    }
    return *this;
}

MutableString& MutableString::toLowercase() {
    for (Size index = 0; index < length; ++index) {
        if (value[index] >= 'A' && value[index] <= 'Z') {
            (value[index] -= 'A') += 'a';
        }
    }
    return *this;
}

MutableString& MutableString::operator=(const MutableString& other) {
    if (this == &other) {
        return *this;
    }

    delete[] value;

    value = stringCopy(other.value);
    length = other.length;
    shallowClone = false;

    return *this;
}

MutableString& MutableString::operator+=(const MutableString& string) {
    return append(string);
}
