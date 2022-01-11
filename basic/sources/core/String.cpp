/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This product is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#include "EnhancedBasic/core/String.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/annotations.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/memory.h"
#include "EnhancedCore/array.h"
#include "EnhancedCore/string.h"

#include "EnhancedBasic/collection/LinkedList.h"

using EnhancedBasic::Core::String;
using EnhancedBasic::Collection::List;
using EnhancedBasic::Collection::LinkedList;

String::String(const char *const value) : value(const_cast<char *>(value)), length(stringLength(value)),
                                          isStaticString(true) {}

String::String(char *const value) : value(stringCopy(value)), length(stringLength(value)),
                                    isStaticString(false) {}

String::String(const Size length) : value(stringNew(length)), length(length), isStaticString(false) {}

String::String(const String &originalCopy) : value(stringCopy(originalCopy)), length(originalCopy.length),
                                             isStaticString(false) {}

String::~String() {
    if (!this->isStaticString) {
        delete this->value;
    }
}

$RetNotIgnored()
bool String::isEmpty() const {
    return this->length == 0;
}

$RetNotIgnored()
Size String::getLength() const {
    return this->length;
}

$RetNotIgnored()
Size String::indexOf(const char ch, const Size getN) const {
    Size indexN = 0;

    for (Size index = 0; index < this->length; ++ index) {
        if ((*this)[index] == ch) {
            if (getN == indexN) {
                return index;
            } else {
                ++ indexN;
            }
        }
    }

    return -1;
}

$RetNotIgnored()
Size String::indexOf(const String &string, const Size getN) const {
    Size indexN = 0;
    Size substringIndex = 0;

    for (Size index = 0; index < this->length; ++ index) {
        if ((*this)[index] == string[substringIndex]) {
            ++ substringIndex;
        } else {
            substringIndex = 0;
        }

        if (substringIndex == string.length) {
            if (getN == indexN) {
                return index - string.length + 1;
            } else {
                ++ indexN;
            }
        }
    }

    return -1;
}

$RetRequiresRelease()
List<Size> *String::indexOfAll(const char ch) const {
    List<Size> *allIndexes = new LinkedList<Size>();

    for (Size index = 0; index < this->length; ++ index) {
        if ((*this)[index] == ch) {
            allIndexes->add(index);
        }
    }

    return allIndexes;
}

$RetRequiresRelease()
List<Size> *String::indexOfAll(const String &string) const {
    List<Size> *allIndexes = new LinkedList<Size>();
    Size count = 0;

    for (Size index = 0; index < this->length; ++ index) {
        (*this)[index] == string[count] ? ++ count : (count = 0);

        if (count == string.length) {
            allIndexes->add(index - string.length + 1);
        }
    }

    return allIndexes;
}

$RetNotIgnored()
char *String::getCharacters() const {
    return this->value;
}

char &String::operator[](const Size index) const {
    return this->value[index];
}

bool String::operator==(const String &string) const {
    return stringEqual(*this, string);
}

String String::operator+(const String &string) const {
    String newString = String(*this);

    if (string.length < 1) {
        return newString;
    }
    newString.append(string);

    return newString;
}

String String::append(const String &string) {
    if (string.length < 1) {
        return *this;
    }

    Size newLength = this->length + string.length;
    char *charArray = new char[newLength + 1];
    charArray[newLength] = '\0';

    for (Size index = 0; index < this->length; ++ index) {
        charArray[index] = this->value[index];
    }
    for (Size index = this->length; index < newLength; ++ index) {
        charArray[index] = string.value[index - this->length];
    }

    if (this->isStaticString) {
        this->isStaticString = false;
    } else {
        delete this->value;
    }

    this->length = newLength;
    this->value = charArray;

    return *this;
}

String String::replace(const char oldChar, const char newChar) {
    return *this;
}

String String::replace(const String &oldSubstring, const String &newSubstring) {
    return *this;
}

String String::replace(char oldChar, const String &newSubstring) {
    return *this;
}

String String::replace(const String &oldSubstring, char newChar) {
    return *this;
}

String String::operator+=(const String &string) {
    return this->append(string);
}

String::operator char *() const {
    return this->getCharacters();
}
