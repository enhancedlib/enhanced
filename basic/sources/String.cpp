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
#include "enhanced/core/assert.h"
#include "enhanced/core/memory.h"
#include "enhanced/core/array.h"
#include "enhanced/core/string.h"

#include "enhanced/basic/IntegerWrapper.h"
#include "enhanced/basic/exception/Exception.h"
#include "enhanced/basic/collection/List.h"
#include "enhanced/basic/collection/ArrayList.h"

using enhanced::basic::String;
using enhanced::basic::IntegerWrapper;
using enhanced::basic::exception::Exception;
using enhanced::basic::collection::List;
using enhanced::basic::collection::ArrayList;

String String::from(const char* value) {
    return {value, 0};
}

String::String(const char* value, byte) noexcept :
    value(stringCopy(value)), length(stringLength(value)), staticString(false), referString(false) {}

String::String(const char* const value) : value(const_cast<char*>(value)), length(stringLength(value)), staticString(true), referString(false) {}

String::String(char* const value) : value(stringCopy(value)), length(stringLength(value)), staticString(false), referString(false) {}

String::String(const Size length) : value(stringNew(length)), length(length), staticString(false), referString(false) {}

String::String(const String& other) : value(stringCopy(other)), length(other.length), staticString(false), referString(false) {}

String::String(String&& other) noexcept : value(other.value), length(other.length), staticString(other.staticString), referString(true) {}

String::~String() {
    if (!staticString && !referString) {
        delete[] value;
    }
}

RetCannotIgnored
bool String::isEmpty() const {
    return length == 0;
}

RetCannotIgnored
Size String::getLength() const {
    return length;
}

RetCannotIgnored
Size String::indexOf(const char ch) const {
    for (Size index = 0; index < length; ++index) {
        if (value[index] == ch) {
            return index;
        }
    }

    return -1;
}

RetCannotIgnored
Size String::indexOf(const String& string) const {
    Size substringIndex = 0;

    for (Size index = 0; index < length; ++index) {
        if (value[index] == string[substringIndex]) {
            ++substringIndex;
        } else {
            substringIndex = 0;
        }

        if (substringIndex == string.length) {
            return index - string.length + 1;
        }
    }

    return -1;
}

RetCannotIgnored
Size String::indexOf(const char ch, const Size getN) const {
    Size indexN = 0;

    for (Size index = 0; index < length; ++index) {
        if (value[index] == ch) {
            if (getN == indexN) {
                return index;
            } else {
                ++indexN;
            }
        }
    }

    return -1;
}

RetCannotIgnored
Size String::indexOf(const String& string, const Size getN) const {
    Size indexN = 0;
    Size substringIndex = 0;

    for (Size index = 0; index < length; ++index) {
        if (value[index] == string[substringIndex]) {
            ++substringIndex;
        } else {
            substringIndex = 0;
        }

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

RetCannotIgnored
Size String::lastIndexOf(const char ch) const {
    for (Size index = length - 1;; --index) {
        if (value[index] == ch) {
            return index;
        }

        if (index == 0) {
            break;
        }
    }

    return -1;
}

RetCannotIgnored
Size String::lastIndexOf(const String& string) const {
    Size substringIndex = string.length - 1;

    for (Size index = length - 1;; --index) {
        if (value[index] == string[substringIndex]) {
            --substringIndex;
        } else {
            substringIndex = string.length - 1;
        }

        if (substringIndex == string.length) {
            return index;
        }

        if (index == 0) {
            break;
        }
    }

    return -1;
}

RetCannotIgnored
Size String::lastIndexOf(const char ch, const Size getN) const {
    Size indexN = 0;

    for (Size index = length - 1;; --index) {
        if (value[index] == ch) {
            if (getN == indexN) {
                return index;
            } else {
                ++indexN;
            }
        }

        if (index == 0) {
            break;
        }
    }

    return -1;
}

RetCannotIgnored
Size String::lastIndexOf(const String& string, const Size getN) const {
    Size indexN = 0;
    Size substringIndex = string.length - 1;

    for (Size index = length - 1;; --index) {
        if (value[index] == string[substringIndex]) {
            --substringIndex;
        } else {
            substringIndex = string.length - 1;
        }

        if (substringIndex == string.length) {
            if (getN == indexN) {
                return index;
            } else {
                ++indexN;
            }
        }

        if (index == 0) {
            break;
        }
    }

    return -1;
}

RetRequiresRelease
List<Size>* String::indexOfAll(const char ch) const {
    List<Size>* allIndexes = new ArrayList<Size>();

    for (Size index = 0; index < length; ++index) {
        if (value[index] == ch) {
            allIndexes->add(index);
        }
    }

    return allIndexes;
}

RetRequiresRelease
List<Size>* String::indexOfAll(const String& string) const {
    List<Size>* allIndexes = new ArrayList<Size>();
    Size substringIndex = 0;

    for (Size index = 0; index < length; ++index) {
        if (value[index] == string[substringIndex]) {
            ++substringIndex;
        } else {
            substringIndex = 0;
        }

        if (substringIndex == string.length) {
            allIndexes->add(index - string.length + 1);
        }
    }

    return allIndexes;
}

RetCannotIgnored
char* String::getCharacters() const {
    return value;
}

RetCannotIgnored
String::SafeCharRef String::at(Size index) const {
    return {value[index], !staticString};
}

RetCannotIgnored
String::SafeCharRef String::operator[](const Size index) const {
    return at(index);
}

RetCannotIgnored
bool String::operator==(const String& string) const {
    return stringEqual(value, string);
}

RetCannotIgnored
String String::operator+(const String& string) const {
    String newString = value;

    if (string.length < 1) {
        return newString;
    }
    newString.append(string);

    return newString;
}

RetCannotIgnored
String::operator char*() const {
    return value;
}

String& String::append(const String& string) {
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

    if (!staticString && !referString) {
        delete[] value;
    } else {
        staticString = false;
    }

    length = newLength;
    value = charArray;

    return *this;
}

String& String::replace(const char oldChar, const char newChar) {
    return *this;
}

String& String::replace(const String& oldSubstring, const String& newSubstring) {
    return *this;
}

String& String::replace(char oldChar, const String& newSubstring) {
    return *this;
}

String& String::replace(const String& oldSubstring, char newChar) {
    return *this;
}

char& String::set(Size index, char ch) {
    if (staticString) {
        String copy = stringCopy(value);
        value = copy;
        staticString = false;
        referString = false;
    }

    return value[index] = ch;
}

String& String::toUpperCase() {
    if (staticString) {
        String copy = stringCopy(value);
        value = copy;
        staticString = false;
        referString = false;
    }

    for (Size index = 0; index < length; ++index) {
        if (index >= 'a' && index <= 'z') {
            (value[index] -= 'a') += 'A';
        }
    }
    return *this;
}

String& String::toLowerCase() {
    if (staticString) {
        String copy = stringCopy(value);
        value = copy;
        staticString = false;
        referString = false;
    }

    for (Size index = 0; index < length; ++index) {
        if (index >= 'A' && index <= 'Z') {
            (value[index] -= 'A') += 'a';
        }
    }
    return *this;
}

String& String::operator=(const String& other) {
    if (this == &other) {
        return *this;
    }

    if (!staticString && !referString) {
        delete[] value;
    }

    value = stringCopy(other.value);
    length = other.length;
    staticString = false;
    referString = false;

    return *this;
}

String& String::operator=(String&& other) noexcept {
    if (!staticString && !referString) {
        delete[] value;
    }

    value = other.value;
    length = other.length;
    staticString = other.staticString;
    referString = true;

    return *this;
}

String& String::operator+=(const String& string) {
    return append(string);
}

String::SafeCharRef::SafeCharRef(char& value, bool canModify) : IntegerWrapper<char>(value), canModify(canModify) {}

void String::SafeCharRef::check() const {
    if (!canModify) {
        throw Exception("Static string cannot modify");
    }
}

#define OPERATOR_IMPL(_operator) \
IntegerWrapper<char>& String::SafeCharRef::operator _operator() { \
    check(); \
    return IntegerWrapper::operator _operator(); \
}

OPERATOR_IMPL(++)
OPERATOR_IMPL(--)

#undef OPERATOR_IMPL

#define OPERATOR_IMPL(_operator) \
const IntegerWrapper<char> String::SafeCharRef::operator _operator(int) { \
    check(); \
    return IntegerWrapper::operator _operator(0); \
}

OPERATOR_IMPL(++)
OPERATOR_IMPL(--)

#undef OPERATOR_IMPL

#define OPERATOR_IMPL(_operator) \
IntegerWrapper<char>& String::SafeCharRef::operator _operator(const IntegerWrapper<char>& other) { \
    check(); \
    return IntegerWrapper::operator _operator(other); \
}

OPERATOR_IMPL(=)
OPERATOR_IMPL(+=)
OPERATOR_IMPL(-=)
OPERATOR_IMPL(*=)
OPERATOR_IMPL(/=)
OPERATOR_IMPL(%=)
OPERATOR_IMPL(<<=)
OPERATOR_IMPL(>>=)
OPERATOR_IMPL(&=)
OPERATOR_IMPL(^=)
OPERATOR_IMPL(|=)

#undef OPERATOR_IMPL

#define OPERATOR_IMPL(_operator) \
IntegerWrapper<char>& String::SafeCharRef::operator _operator(const char& other) { \
    check(); \
    return IntegerWrapper::operator _operator(other); \
}

OPERATOR_IMPL(=)
OPERATOR_IMPL(+=)
OPERATOR_IMPL(-=)
OPERATOR_IMPL(*=)
OPERATOR_IMPL(/=)
OPERATOR_IMPL(%=)
OPERATOR_IMPL(<<=)
OPERATOR_IMPL(>>=)
OPERATOR_IMPL(&=)
OPERATOR_IMPL(^=)
OPERATOR_IMPL(|=)

#undef OPERATOR_IMPL
