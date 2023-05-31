/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <enhanced/String.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Memory.h>
#include <enhanced/Array.h>
#include <enhanced/Character.h>
#include <enhanced/CharSequence.h>
#include <enhanced/InitializerList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/math/Math.h>
#include <enhanced/collections/ArrayList.h>
#include <enhanced/exceptions/NullPointerException.h>

using enhanced::util::move;
using enhanced::util::removeConst;
using enhanced::util::removePtrConst;
using enhanced::math::min;
using enhanced::math::difference;
using enhanced::collections::ArrayList;
using enhanced::exceptions::NullPointerException;

namespace enhanced {
    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::from(bool value) {
        return value ? TString(E_SWITCH_STR(CharType, "true")) : E_SWITCH_STR(CharType, "false");
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::from(CharType value) {
        TString<CharType> string {1};
        string.set(0, value);
        return string;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::from(qword value, bool isNegative) {
        // TODO: Faster implementation
        if (isNegative) value = -((int64) value);
        wrap<CharType[21]> bits;
        sizetype index = 20;
        for (; value != 0; --index) {
            bits[index] = value % 10 + '0';
            value /= 10;
        }
        if (isNegative) bits[index--] = '-';
        return own(bits + index + 1, 20 - index);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::own(const CharType* value, sizetype length) {
        return {TStringUtil<CharType>::copy(value), length, true};
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::own(const CharType* value) {
        return own(value, TStringUtil<CharType>::calcLength(value));
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(const CharType* value, sizetype length, bool isOwn) noexcept : CharSequence<CharType>(value, length, isOwn) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString() noexcept : CharSequence<CharType>(E_SWITCH_STR(CharType, ""), 0) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(const CharType* value, sizetype length) noexcept : CharSequence<CharType>(value, length) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(const CharType*& value) noexcept : TString(removePtrConst(value)) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(CharType*& value) noexcept : TString<CharType>(value, TStringUtil<CharType>::calcLength(value)) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(CharType* const& value) noexcept : TString(removeConst(value)) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(sizetype length) : TString<CharType>(TStringUtil<CharType>::make(length), length, true) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(const TString* strings, sizetype count) : TString() {
        sizetype length = 0;
        for (sizetype index = 0; index < count; ++index) {
            length += strings[index].length;
        }

        auto string = TStringUtil<CharType>::make(length);

        sizetype offset = 0;
        for (sizetype index = 0; index < count; ++index) {
            arrayCopy(string + offset, strings[index].value, strings[index].length);
            offset += strings[index].length;
        }

        this->value = string;
        this->length = length;
        this->isOwn = true;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(InitializerList<TString> list) : TString(list.toArray(), list.getSize()) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(const TString& other) :
        TString(other.isOwn ? TStringUtil<CharType>::copy(other.value) : other.value, other.length, other.isOwn) {}

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>::TString(TString&& other) noexcept = default;

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype TString<CharType>::indexOf(const CharType ch) const noexcept {
        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == ch) return index;
        }

        return E_SIZE_TYPE_MAX;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype TString<CharType>::indexOf(const TString& string) const noexcept {
        sizetype substringIndex = 0;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == string[substringIndex]) ++substringIndex;
            else substringIndex = 0;

            if (substringIndex == string.length) return index - string.length + 1;
        }

        return E_SIZE_TYPE_MAX;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype TString<CharType>::indexOf(CharType ch, sizetype getN) const noexcept {
        sizetype indexN = 0;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == ch) {
                if (getN == indexN) return index;
                else ++indexN;
            }
        }

        return E_SIZE_TYPE_MAX;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype TString<CharType>::indexOf(const TString& string, sizetype getN) const noexcept {
        sizetype indexN = 0;
        sizetype substringIndex = 0;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == string[substringIndex]) ++substringIndex;
            else substringIndex = 0;

            if (substringIndex == string.length) {
                if (getN == indexN) return index - string.length + 1;
                else ++indexN;
            }
        }

        return E_SIZE_TYPE_MAX;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype TString<CharType>::indexOfLast(CharType ch) const noexcept {
        for (sizetype index = this->length - 1;; --index) {
            if (this->value[index] == ch) return index;
            if (index == 0) break;
        }

        return E_SIZE_TYPE_MAX;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype TString<CharType>::indexOfLast(const TString& string) const noexcept {
        sizetype substringIndex = string.length - 1;

        for (sizetype index = this->length - 1;; --index) {
            if (this->value[index] == string[substringIndex]) {
                --substringIndex;
            } else {
                substringIndex = string.length - 1;
            }

            if (substringIndex == string.length) return index;
            if (index == 0) break;
        }

        return E_SIZE_TYPE_MAX;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype TString<CharType>::indexOfLast(CharType ch, sizetype getN) const noexcept {
        sizetype indexN = 0;

        for (sizetype index = this->length - 1;; --index) {
            if (this->value[index] == ch) {
                if (getN == indexN) return index;
                else ++indexN;
            }

            if (index == 0) break;
        }

        return E_SIZE_TYPE_MAX;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype TString<CharType>::indexOfLast(const TString& string, sizetype getN) const noexcept {
        sizetype indexN = 0;
        sizetype substringIndex = string.length - 1;

        for (sizetype index = this->length - 1;; --index) {
            if (this->value[index] == string[substringIndex]) --substringIndex;
            else substringIndex = string.length - 1;

            if (substringIndex == string.length) {
                if (getN == indexN) return index;
                else ++indexN;
            }

            if (index == 0) break;
        }

        return E_SIZE_TYPE_MAX;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetRequiresRelease)
    ArrayList<sizetype> TString<CharType>::indexOfAll(const CharType ch) const noexcept {
        ArrayList<sizetype> allIndexes(min(this->length, collections::ARRAY_INIT_SIZE));

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == ch) allIndexes.add(index);
        }

        return allIndexes;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetRequiresRelease)
    ArrayList<sizetype> TString<CharType>::indexOfAll(const TString& string) const noexcept {
        ArrayList<sizetype> allIndexes(min(this->length / string.length + 1, collections::ARRAY_INIT_SIZE));
        sizetype substringIndex = 0;

        for (sizetype index = 0; index < this->length; ++index) {
            if (this->value[index] == string[substringIndex]) ++substringIndex;
            else substringIndex = 0;

            if (substringIndex == string.length) {
                allIndexes.add(index - string.length + 1);
                substringIndex = 0;
            }
        }

        return allIndexes;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    bool TString<CharType>::ownStorage() const noexcept {
        return this->isOwn;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::replace(sizetype start, sizetype end, CharType newChar) const {
        return TString<CharType>(this->value).replaceTo(start, end, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::replace(sizetype start, sizetype end, const TString& newSubstring) const {
        return TString<CharType>(this->value).replaceTo(start, end, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::replace(CharType oldChar, CharType newChar) const {
        return TString<CharType>(this->value).replaceTo(oldChar, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::replace(const TString& oldSubstring, const TString& newSubstring) const {
        return TString<CharType>(this->value).replaceTo(oldSubstring, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::replace(CharType oldChar, const TString& newSubstring) const {
        return TString<CharType>(this->value).replaceTo(oldChar, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::replace(const TString& oldSubstring, CharType newChar) const {
        return TString<CharType>(this->value).replaceTo(oldSubstring, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::replaceAll(CharType oldChar, CharType newChar) const {
        return TString<CharType>(this->value).replaceAllTo(oldChar, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::replaceAll(const TString& oldSubstring, const TString& newSubstring) const {
        return TString<CharType>(this->value).replaceAllTo(oldSubstring, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::replaceAll(CharType oldChar, const TString& newSubstring) const {
        return TString<CharType>(this->value).replaceAllTo(oldChar, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::replaceAll(const TString& oldSubstring, CharType newChar) const {
        return TString<CharType>(this->value).replaceAllTo(oldSubstring, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::uppercase() const {
        return TString<CharType>(this->value).toUppercase();
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::lowercase() const {
        return TString<CharType>(this->value).toLowercase();
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::toOwn() {
        if (!this->isOwn) this->value = TStringUtil<CharType>::copy(this->value, this->length);
        this->isOwn = true;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::set(sizetype index, CharType ch) {
        toOwn();
        this->value[index] = ch;
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::append(CharType ch) {
        sizetype newLength = this->length + 1;
        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, this->length);
        newString[this->length] = ch;

        if (this->isOwn) delete[] this->value;

        this->value = newString;
        this->length = newLength;
        this->isOwn = true;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::append(const TString<CharType>& string) {
        if (string.length == 0) return *this;

        sizetype newLength = this->length + string.length;
        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, this->length);
        arrayCopy(newString + this->length, string.value, string.length);

        if (this->isOwn) delete[] this->value;

        this->value = newString;
        this->length = newLength;
        this->isOwn = true;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::insertFirst(CharType ch) {
        sizetype newLength = this->length + 1;
        auto newString = TStringUtil<CharType>::make(newLength);

        newString[0] = ch;
        arrayCopy(newString + 1, this->value, this->length);

        if (this->isOwn) delete[] this->value;

        this->value = newString;
        this->length = newLength;
        this->isOwn = true;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::insertFirst(const TString<CharType>& string) {
        if (string.length == 0) return *this;

        sizetype newLength = this->length + string.length;
        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, string.value, string.length);
        arrayCopy(newString + string.length, this->value, this->length);

        if (this->isOwn) delete[] this->value;

        this->value = newString;
        this->length = newLength;
        this->isOwn = true;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::replaceTo(sizetype start, sizetype end, CharType newChar) {
        sizetype newLength = this->length - (end - start) + 1;
        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, start);
        newString[start] = newChar;
        arrayCopy(newString + start + 1, this->value + end, this->length - end);

        if (this->isOwn) delete[] this->value;

        this->value = newString;
        this->length = newLength;
        this->isOwn = true;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::replaceTo(sizetype start, sizetype end, const TString<CharType>& newSubstring) {
        sizetype newLength = this->length - (end - start) + newSubstring.length;
        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, start);
        arrayCopy(newString + start, newSubstring.value, newSubstring.length);
        arrayCopy(newString + start + newSubstring.length, this->value + end, this->length - end);

        if (this->isOwn) delete[] this->value;

        this->value = newString;
        this->length = newLength;
        this->isOwn = true;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::replaceTo(const CharType oldChar, const CharType newChar) {
        sizetype index = this->indexOf(oldChar);
        if (index == E_SIZE_TYPE_MAX) return *this;
        toOwn();
        this->value[index] = newChar;
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::replaceTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) {
        sizetype index = this->indexOf(oldSubstring);
        if (index == E_SIZE_TYPE_MAX) return *this;
        return this->replaceTo(index, index + oldSubstring.length, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::replaceTo(CharType oldChar, const TString<CharType>& newSubstring) {
        sizetype index = this->indexOf(oldChar);
        if (index == E_SIZE_TYPE_MAX) return *this;
        return this->replaceTo(index, index + 1, newSubstring);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::replaceTo(const TString<CharType>& oldSubstring, CharType newChar) {
        sizetype index = this->indexOf(oldSubstring);
        if (index == E_SIZE_TYPE_MAX) return *this;
        return this->replaceTo(index, index + oldSubstring.length, newChar);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::replaceAllTo(CharType oldChar, CharType newChar) {
        auto result = this->indexOfAll(oldChar);
        for (auto index : result) {
            this->value[index] = newChar;
        }
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::replaceAllTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) {
        auto result = this->indexOfAll(oldSubstring);
        if (result.isEmpty()) return *this;

        sizetype diff = difference(newSubstring.length, oldSubstring.length) * result.getSize();
        sizetype newLength = (newSubstring.length > oldSubstring.length) ? this->length + diff : this->length - diff;

        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, result[0]);

        sizetype offset = result[0];
        auto iterator = result.iterator();
        while (iterator.hasNext()) {
            iterator.next();
            arrayCopy(newString + offset, newSubstring.value, newSubstring.length);
            offset += newSubstring.length;

            sizetype begin = iterator.get() + oldSubstring.length;
            if (iterator.hasNext()) {
                arrayCopy(newString + offset, this->value + begin, iterator.next().get() - begin);
                offset += iterator.get() - begin;
                iterator.prev();
            } else {
                arrayCopy(newString + offset, this->value + begin, this->length - begin);
            }
        }

        if (this->isOwn) delete[] this->value;

        this->value = newString;
        this->length = newLength;
        this->isOwn = true;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::replaceAllTo(CharType oldChar, const TString<CharType>& newSubstring) {
        auto result = this->indexOfAll(oldChar);
        if (result.isEmpty()) return *this;

        sizetype diff = difference(newSubstring.length, 1u) * result.getSize();
        sizetype newLength = (newSubstring.length > 1) ? this->length + diff : this->length - diff;

        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, result[0]);

        sizetype offset = result[0];
        auto iterator = result.iterator();
        while (iterator.hasNext()) {
            iterator.next();
            arrayCopy(newString + offset, newSubstring.value, newSubstring.length);
            offset += newSubstring.length;

            sizetype begin = iterator.get() + 1;
            if (iterator.hasNext()) {
                arrayCopy(newString + offset, this->value + begin, iterator.next().get() - begin);
                offset += iterator.get() - begin;
                iterator.prev();
            } else {
                arrayCopy(newString + offset, this->value + begin, this->length - begin);
            }
        }

        if (this->isOwn) delete[] this->value;

        this->value = newString;
        this->length = newLength;
        this->isOwn = true;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::replaceAllTo(const TString<CharType>& oldSubstring, CharType newChar) {
        auto result = this->indexOfAll(oldSubstring);
        if (result.isEmpty()) return *this;

        sizetype diff = difference(1u, oldSubstring.length) * result.getSize();
        sizetype newLength = (1 > oldSubstring.length) ? this->length + diff : this->length - diff;

        auto newString = TStringUtil<CharType>::make(newLength);

        arrayCopy(newString, this->value, result[0]);

        sizetype offset = result[0];
        auto iterator = result.iterator();
        while (iterator.hasNext()) {
            iterator.next();
            newString[offset] = newChar;
            offset += 1;

            sizetype begin = iterator.get() + oldSubstring.length;
            if (iterator.hasNext()) {
                arrayCopy(newString + offset, this->value + begin, iterator.next().get() - begin);
                offset += iterator.get() - begin;
                iterator.prev();
            } else {
                arrayCopy(newString + offset, this->value + begin, this->length - begin);
            }
        }

        if (this->isOwn) delete[] this->value;

        this->value = newString;
        this->length = newLength;
        this->isOwn = true;

        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::fill(CharType ch) noexcept {
        toOwn();
        arrayFill(this->value, ch, this->length);
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::toUppercase() {
        toOwn();
        for (sizetype index = 0; index < this->length; ++index) {
            this->value[index] = enhanced::uppercase(this->value[index]);
        }
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    TString<CharType>& TString<CharType>::toLowercase() {
        toOwn();
        for (sizetype index = 0; index < this->length; ++index) {
            this->value[index] = enhanced::lowercase(this->value[index]);
        }
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    bool TString<CharType>::operator==(const TString& string) const noexcept {
        return TStringUtil<CharType>::isEqual(this->value, this->length, string.value, string.length);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::operator+(CharType ch) const {
        sizetype newLength = this->length + 1;
        TString newString(newLength);

        arrayCopy(newString.value, this->value, this->length);
        newString.set(this->length, ch);

        return newString;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType> TString<CharType>::operator+(const TString& string) const {
        sizetype newLength = this->length + string.length;
        TString newString(newLength);

        arrayCopy(newString.value, this->value, this->length);
        arrayCopy(newString.value + this->length, string.value, string.length);

        return newString;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType>& TString<CharType>::operator+=(CharType ch) {
        return append(ch);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    TString<CharType>& TString<CharType>::operator+=(const TString& string) {
        return append(string);
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(ReturnSelf)
    TString<CharType>& TString<CharType>::operator=(const TString& other) noexcept {
        CharSequence<CharType>::operator=(other);
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(ReturnSelf)
    TString<CharType>& TString<CharType>::operator=(TString&& other) noexcept {
        CharSequence<CharType>::operator=(move(other));
        return *this;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetRequiresRelease)
    CharType* TStringUtil<CharType>::make(sizetype length) {
        auto str = new CharType[length + 1];
        str[length] = E_SWITCH_CHAR(CharType, '\0');
        return str;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetRequiresRelease)
    CharType* TStringUtil<CharType>::copy(const CharType* source) {
        return copy(source, calcLength(source));
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetRequiresRelease)
    CharType* TStringUtil<CharType>::copy(const CharType* source, sizetype length) {
        if (source == nullptr) throw NullPointerException("The given argument 'source' is nullptr");

        auto copy = make(length);
        arrayCopy(copy, source, length);

        return copy;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetRequiresRelease)
    CharType* TStringUtil<CharType>::copy(sizetype newLength, const CharType* source, sizetype oldLength) {
        if (source == nullptr) throw NullPointerException("The given argument 'source' is nullptr");

        auto copy = make(newLength);
        arrayCopy(copy, source, ((newLength > oldLength) ? oldLength : newLength));

        return copy;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    sizetype TStringUtil<CharType>::calcLength(const CharType* string) noexcept {
        if (string == nullptr) return E_SIZE_TYPE_MAX;

        sizetype length;
        for (length = 0; string[length] != E_SWITCH_CHAR(CharType, '\0'); ++length) {}

        return length;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    bool TStringUtil<CharType>::isEqual(const CharType* string1, const CharType* string2) noexcept {
        if (string1 == string2) return true;
        else if (string1 == nullptr || string2 == nullptr) return false;

        for (sizetype index = 0;; ++index) {
            if ((string1[index] == E_SWITCH_CHAR(CharType, '\0')) ^ (string2[index] == E_SWITCH_CHAR(CharType, '\0'))) {
                return false;
            }

            if (string1[index] != string2[index]) return false;
        }
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    bool TStringUtil<CharType>::isEqual(const CharType* string1, sizetype length1, const CharType* string2) noexcept {
        if (length1 != calcLength(string2)) return false;
        if (string1 == string2) return true;
        else if (string1 == nullptr || string2 == nullptr) return false;


        for (sizetype index = 0; index < length1; ++index) {
            if (string1[index] != string2[index]) return false;
        }
        return true;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    bool TStringUtil<CharType>::isEqual(const CharType* string1, const CharType* string2, sizetype length2) noexcept {
        if (calcLength(string1) != length2) return false;
        if (string1 == string2) return true;
        else if (string1 == nullptr || string2 == nullptr) return false;


        for (sizetype index = 0; index < length2; ++index) {
            if (string1[index] != string2[index]) return false;
        }
        return true;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    E_ANNOTATE(RetNotIgnored)
    bool TStringUtil<CharType>::isEqual(const CharType* string1, sizetype length1, const CharType* string2, sizetype length2) noexcept {
        if (length1 != length2) return false;
        if (string1 == string2) return true;
        else if (string1 == nullptr || string2 == nullptr) return false;


        for (sizetype index = 0; index < length1; ++index) {
            if (string1[index] != string2[index]) return false;
        }
        return true;
    }

    template class TString<char>;
    template class TString<wchar>;
    template class TString<u8char>;
    template class TString<u16char>;
    template class TString<u32char>;

    template struct TStringUtil<char>;
    template struct TStringUtil<wchar>;
    template struct TStringUtil<u8char>;
    template struct TStringUtil<u16char>;
    template struct TStringUtil<u32char>;
}