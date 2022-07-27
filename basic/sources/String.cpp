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

#include "enhanced/basic/String.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/annotations.h"
#include "enhanced/core/memory.h"
#include "enhanced/core/array.h"
#include "enhanced/core/string.h"

#include "enhanced/basic/collection/ArrayList.h"

using enhanced::basic::String;
using enhanced::basic::collection::List;
using enhanced::basic::collection::ArrayList;

String::String(const char* const value) noexcept : value(const_cast<char*>(value)), length(stringLength(value)), staticString(true) {}

String::String(char* const value) noexcept : value(value), length(stringLength(value)), staticString(true) {}

String::String(const Size length) : value(stringNew(length)), length(length), staticString(false) {}

String::String(const String& other) : value(stringCopy(other)), length(other.length), staticString(false) {}

String::String(String&& other) noexcept : value(other), length(other.length), staticString(true) {}

String::~String() {
    if (!staticString) {
        delete[] value;
    }
}

RetCannotIgnored()
bool String::isEmpty() const {
    return length == 0;
}

RetCannotIgnored()
Size String::getLength() const {
    return length;
}

RetCannotIgnored()
Size String::indexOf(const char ch) const {
    for (Size index = 0; index < length; ++index) {
        if ((*this)[index] == ch) {
            return index;
        }
    }

    return -1;
}

RetCannotIgnored()
Size String::indexOf(const String& string) const {
    Size substringIndex = 0;

    for (Size index = 0; index < length; ++index) {
        (*this)[index] == string[substringIndex] ? ++substringIndex : substringIndex = 0;

        if (substringIndex == string.length) {
            return index - string.length + 1;
        }
    }

    return -1;
}

RetCannotIgnored()
Size String::lastIndexOf(const char ch) const {
    for (Size index = length - 1; index >= 0; --index) {
        if ((*this)[index] == ch) {
            return index;
        }
    }

    return -1;
}

RetCannotIgnored()
Size String::lastIndexOf(const String& string) const {
    Size substringIndex = string.length - 1;

    for (Size index = length - 1; index >= 0; --index) {
        (*this)[index] == string[substringIndex] ? --substringIndex : substringIndex = string.length - 1;

        if (substringIndex == string.length) {
            return index;
        }
    }

    return -1;
}

RetCannotIgnored()
Size String::indexOf(const char ch, const Size getN) const {
    Size indexN = 0;

    for (Size index = 0; index < length; ++index) {
        if ((*this)[index] == ch) {
            if (getN == indexN) {
                return index;
            } else {
                ++indexN;
            }
        }
    }

    return -1;
}

RetCannotIgnored()
Size String::indexOf(const String& string, const Size getN) const {
    Size indexN = 0;
    Size substringIndex = 0;

    for (Size index = 0; index < length; ++index) {
        (*this)[index] == string[substringIndex] ? ++substringIndex : substringIndex = 0;

        if (substringIndex == string.length) {
            if (getN == indexN) {
                return index - string.length + 1;
            } else {
                ++indexN;
            }
        }
    }

    return -1;
}

RetRequiresRelease()
List<Size>* String::indexOfAll(const char ch) const {
    List<Size>* allIndexes = new ArrayList<Size>();

    for (Size index = 0; index < length; ++index) {
        if ((*this)[index] == ch) {
            allIndexes->add(index);
        }
    }

    return allIndexes;
}

RetRequiresRelease()
List<Size>* String::indexOfAll(const String& string) const {
    List<Size>* allIndexes = new ArrayList<Size>();
    Size substringIndex = 0;

    for (Size index = 0; index < length; ++index) {
        (*this)[index] == string[substringIndex] ? ++substringIndex : (substringIndex = 0);

        if (substringIndex == string.length) {
            allIndexes->add(index - string.length + 1);
        }
    }

    return allIndexes;
}

RetCannotIgnored()
char* String::getCharacters() const {
    return value;
}

char& String::operator[](const Size index) const {
    return value[index];
}

bool String::operator==(const String& string) const {
    return stringEqual(*this, string);
}

String String::operator+(const String& string) const {
    String newString = *this;

    if (string.length < 1) {
        return newString;
    }
    newString.append(string);

    return newString;
}

String String::append(const String& string) {
    if (string.length < 1) {
        return *this;
    }

    Size newLength = length + string.length;
    char* charArray = new char[newLength + 1];
    charArray[newLength] = '\0';

    for (Size index = 0; index < length; ++index) {
        charArray[index] = value[index];
    }
    for (Size index = length; index < newLength; ++index) {
        charArray[index] = string.value[index - length];
    }

    if (!staticString) {
        delete value;
    } else {
        staticString = false;
    }

    length = newLength;
    value = charArray;

    return *this;
}

String String::replace(const char oldChar, const char newChar) {
    return *this;
}

String String::replace(const String& oldSubstring, const String& newSubstring) {
    return *this;
}

String String::replace(char oldChar, const String& newSubstring) {
    return *this;
}

String String::replace(const String& oldSubstring, char newChar) {
    return *this;
}

String& String::operator=(const String& other) {
    if (this == &other) {
        return *this;
    }

    if (!staticString) {
        delete[] value;
    }

    value = stringCopy(other.value);
    length = other.length;
    staticString = false;

    return *this;
}

String& String::operator=(String&& other) noexcept {
    if (!staticString) {
        delete[] value;
    }

    value = other.value;
    length = other.length;
    staticString = true;

    return *this;
}

String String::operator+=(const String& string) {
    return append(string);
}

String::operator char*() const {
    return value;
}
