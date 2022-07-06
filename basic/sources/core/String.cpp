/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#include "Enhanced/basic/core/String.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/annotations.h"
#include "Enhanced/core/memory.h"
#include "Enhanced/core/array.h"
#include "Enhanced/core/string.h"

#include "Enhanced/basic/collection/ArrayList.h"

using Enhanced::basic::core::String;
using Enhanced::basic::collection::List;
using Enhanced::basic::collection::ArrayList;

String::String(const char* const value) : value(const_cast<char*>(value)), length(stringLength(value)), dynamic(false) {}

String::String(char* const value) : value(value), length(stringLength(value)), dynamic(false) {}

String::String(const Size length) : value(stringNew(length)), length(length), dynamic(true) {}

String::String(const String& other) : value(stringCopy(other)), length(other.length), dynamic(true) {}

String::String(String&& other) noexcept: value(other), length(other.length), dynamic(other.dynamic) {}

String::~String() {
    if (dynamic) {
        delete value;
    }
}

RetNotIgnored()
bool String::isEmpty() const {
    return length == 0;
}

RetNotIgnored()
Size String::getLength() const {
    return length;
}

RetNotIgnored()
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

RetNotIgnored()
Size String::indexOf(const String& string, const Size getN) const {
    Size indexN = 0;
    Size substringIndex = 0;

    for (Size index = 0; index < length; ++index) {
        if ((*this)[index] == string[substringIndex]) {
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
    Size count = 0;

    for (Size index = 0; index < length; ++index) {
        (*this)[index] == string[count] ? ++count : (count = 0);

        if (count == string.length) {
            allIndexes->add(index - string.length + 1);
        }
    }

    return allIndexes;
}

RetNotIgnored()
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
    String newString = String(*this);

    if (string.length < 1) {
        return newString;
    }
    newString.append(string);

    return newString;
}

String& String::operator=(const String& other) {
    value = stringCopy(other.value);
    length = other.length;
    dynamic = true;

    return *this;
}

String& String::operator=(String&& other) noexcept {
    value = other.value;
    length = other.length;
    dynamic = other.dynamic;

    return *this;
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

    if (dynamic) {
        delete value;
    } else {
        dynamic = true;
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

String String::operator+=(const String& string) {
    return append(string);
}

String::operator char*() const {
    return value;
}
