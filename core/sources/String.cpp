/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <enhanced/core/String.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/stringUtil.h>
#include <enhanced/core/CharSequence.h>
#include <enhanced/core/MutableString.h>
#include <enhanced/core/InitializerList.h>
#include <enhanced/core/collections/ArrayList.h>

using enhanced::core::BasicString;
using enhanced::core::MutableBasicString;
using enhanced::core::collections::ArrayList;

template <typename CharType>
MutableBasicString<CharType> BasicString<CharType>::join(InitializerList<BasicString> list) {
    return join(list.toArray(), list.count());
}

template <typename CharType>
MutableBasicString<CharType> BasicString<CharType>::join(const BasicString* strings, sizetype count) {
    sizetype length = 0;
    for (sizetype index = 0; index < count; ++index) {
        length += strings[index].length;
    }

    auto newString = MutableBasicString<CharType>(length);

    memoryCopy(newString.value, strings[0].value, strings[0].length * sizeof(CharType));
    for (sizetype index = 1; index < count; ++index) {
        memoryCopy(newString.value + strings[index - 1].length, strings[index].value, strings[index].length * sizeof(CharType));
    }

    return newString;
}

template <typename CharType>
BasicString<CharType>::BasicString(CharType* value, sizetype length) noexcept : CharSequence<CharType>(value, length)  {}

template <typename CharType>
BasicString<CharType>::BasicString(const CharType* value) noexcept : BasicString(const_cast<CharType*>(value)) {}

template <typename CharType>
BasicString<CharType>::BasicString(CharType* value) noexcept : CharSequence<CharType>(value, tstringLength(value)) {}

template <typename CharType>
BasicString<CharType>::BasicString(const BasicString& other) noexcept = default;

template <typename CharType>
BasicString<CharType>::BasicString(BasicString&& other) noexcept = default;

template <typename CharType>
NoIgnoreRet
sizetype BasicString<CharType>::indexOf(const CharType ch) const noexcept {
    for (sizetype index = 0; index < this->length; ++index) {
        if (this->value[index] == ch) {
            return index;
        }
    }

    return SIZE_TYPE_MAX;
}

template <typename CharType>
NoIgnoreRet
sizetype BasicString<CharType>::indexOf(const BasicString& string) const noexcept {
    sizetype substringIndex = 0;

    for (sizetype index = 0; index < this->length; ++index) {
        if (this->value[index] == string[substringIndex]) {
            ++substringIndex;
        } else {
            substringIndex = 0;
        }

        if (substringIndex == string.length) {
            return index - string.length + 1;
        }
    }

    return SIZE_TYPE_MAX;
}

template <typename CharType>
NoIgnoreRet
sizetype BasicString<CharType>::indexOf(const CharType ch, const sizetype getN) const noexcept {
    sizetype indexN = 0;

    for (sizetype index = 0; index < this->length; ++index) {
        if (this->value[index] == ch) {
            if (getN == indexN) {
                return index;
            } else {
                ++indexN;
            }
        }
    }

    return SIZE_TYPE_MAX;
}

template <typename CharType>
NoIgnoreRet
sizetype BasicString<CharType>::indexOf(const BasicString& string, const sizetype getN) const noexcept {
    sizetype indexN = 0;
    sizetype substringIndex = 0;

    for (sizetype index = 0; index < this->length; ++index) {
        if (this->value[index] == string[substringIndex]) {
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

    return SIZE_TYPE_MAX;
}

template <typename CharType>
NoIgnoreRet
sizetype BasicString<CharType>::lastIndexOf(const CharType ch) const noexcept {
    for (sizetype index = this->length - 1;; --index) {
        if (this->value[index] == ch) {
            return index;
        }

        if (index == 0) {
            break;
        }
    }

    return SIZE_TYPE_MAX;
}

template <typename CharType>
NoIgnoreRet
sizetype BasicString<CharType>::lastIndexOf(const BasicString& string) const noexcept {
    sizetype substringIndex = string.length - 1;

    for (sizetype index = this->length - 1;; --index) {
        if (this->value[index] == string[substringIndex]) {
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

    return SIZE_TYPE_MAX;
}

template <typename CharType>
NoIgnoreRet
sizetype BasicString<CharType>::lastIndexOf(const CharType ch, const sizetype getN) const noexcept {
    sizetype indexN = 0;

    for (sizetype index = this->length - 1;; --index) {
        if (this->value[index] == ch) {
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

    return SIZE_TYPE_MAX;
}

template <typename CharType>
NoIgnoreRet
sizetype BasicString<CharType>::lastIndexOf(const BasicString& string, const sizetype getN) const noexcept {
    sizetype indexN = 0;
    sizetype substringIndex = string.length - 1;

    for (sizetype index = this->length - 1;; --index) {
        if (this->value[index] == string[substringIndex]) {
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

    return SIZE_TYPE_MAX;
}

template <typename CharType>
RetRequiresRelease
ArrayList<sizetype> BasicString<CharType>::indexOfAll(const CharType ch) const noexcept {
    ArrayList<sizetype> allIndexes;

    for (sizetype index = 0; index < this->length; ++index) {
        if (this->value[index] == ch) {
            allIndexes.add(index);
        }
    }

    return allIndexes;
}

template <typename CharType>
RetRequiresRelease
ArrayList<sizetype> BasicString<CharType>::indexOfAll(const BasicString& string) const noexcept {
    ArrayList<sizetype> allIndexes;
    sizetype substringIndex = 0;

    for (sizetype index = 0; index < this->length; ++index) {
        if (this->value[index] == string[substringIndex]) {
            ++substringIndex;
        } else {
            substringIndex = 0;
        }

        if (substringIndex == string.length) {
            allIndexes.add(index - string.length + 1);
        }
    }

    return allIndexes;
}

template <typename CharType>
NoIgnoreRet
MutableBasicString<CharType> BasicString<CharType>::replace(CharType oldChar, CharType newChar) const {
    return MutableBasicString<CharType>(this->value).replaceTo(oldChar, newChar);
}

template <typename CharType>
NoIgnoreRet
MutableBasicString<CharType> BasicString<CharType>::replace(const BasicString& oldSubstring, const BasicString& newSubstring) const {
    return MutableBasicString<CharType>(this->value).replaceTo(oldSubstring, newSubstring);
}

template <typename CharType>
NoIgnoreRet
MutableBasicString<CharType> BasicString<CharType>::replace(CharType oldChar, const BasicString& newSubstring) const {
    return MutableBasicString<CharType>(this->value).replaceTo(oldChar, newSubstring);
}

template <typename CharType>
NoIgnoreRet
MutableBasicString<CharType> BasicString<CharType>::replace(const BasicString& oldSubstring, CharType newChar) const {
    return MutableBasicString<CharType>(this->value).replaceTo(oldSubstring, newChar);
}

template <typename CharType>
MutableBasicString<CharType> BasicString<CharType>::uppercase() const {
    return MutableBasicString<CharType>(this->value).toUppercase();
}

template <typename CharType>
MutableBasicString<CharType> BasicString<CharType>::lowercase() const {
    return MutableBasicString<CharType>(this->value).toLowercase();
}

template <typename CharType>
bool BasicString<CharType>::operator==(const BasicString& string) const noexcept {
    if (this->length != string.length) return false;
    return tstringEqual(this->value, string.value);
}

template <typename CharType>
NoIgnoreRet
MutableBasicString<CharType> BasicString<CharType>::operator+(const BasicString& string) const {
    sizetype newLength = this->length + string.length;
    MutableBasicString<CharType> newString(newLength);

    memoryCopy(newString.value, this->value, newLength);
    memoryCopy(newString.value + this->length, string.value, newLength);

    return newString;
}

template <typename CharType>
BasicString<CharType>& BasicString<CharType>::operator=(const BasicString& other) noexcept = default;

template <typename CharType>
BasicString<CharType>& BasicString<CharType>::operator=(BasicString&& other) noexcept = default;

template class enhanced::core::BasicString<char>;
template class enhanced::core::BasicString<wchar>;
template class enhanced::core::BasicString<u8char>;
template class enhanced::core::BasicString<u16char>;
template class enhanced::core::BasicString<u32char>;
