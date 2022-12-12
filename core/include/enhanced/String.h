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

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/CharSequence.h>
#include <enhanced/InitializerList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/collections/ArrayList.h>

namespace enhanced {
    template <typename CharType>
    class ENHANCED_CORE_API TMutString;

    template <typename CharType>
    class ENHANCED_CORE_API TString : public CharSequence<CharType> {
    protected:
        TString(const CharType* value, sizetype length, bool isMutable) noexcept;

    public:
        $RetRequiresRelease
        static CharType* make(sizetype length);

        $RetRequiresRelease
        static CharType* copy(const CharType* source);

        $RetRequiresRelease
        static CharType* copy(const CharType* source, sizetype length);

        $RetRequiresRelease
        static CharType* copy(const CharType* source, sizetype oldLength, sizetype newLength);

        $NoIgnoreReturn
        static sizetype calcLength(const CharType* string) noexcept;

        $NoIgnoreReturn
        static bool isEqual(const CharType* string1, const CharType* string2) noexcept;

        $NoIgnoreReturn
        static bool isEqual(const CharType* string1, const CharType* string2, sizetype length1, sizetype length2) noexcept;

        template <typename IntType>
        requires util::isIntegralTypeNc<IntType>
        $NoIgnoreReturn
        static TMutString<CharType> from(IntType value) {
            // TODO: Faster implementation
            TMutString<CharType> str;
            int8 bit;
            while (value != 0) {
                bit = value % 10;
                str.insertFirst(bit + '0');
                value /= 10;
            }
            return str;
        }

        template <sizetype count>
        $NoIgnoreReturn
        static inline TMutString<CharType> join(TString strings[count]) {
            return join(strings, count);
        }

        $NoIgnoreReturn
        static TMutString<CharType> join(InitializerList<TString> list);

        $NoIgnoreReturn
        static TMutString<CharType> join(const TString* strings, sizetype count);

        TString() noexcept;

        TString(const CharType* value, sizetype length) noexcept;

        template <sizetype size>
        inline TString(const CharType (&value)[size]) noexcept : TString((CharType*) value, size - 1) {}

        TString(const CharType*& value);

        TString(CharType*& value);

        TString(CharType* const& value);

        TString(const TString& other) noexcept;

        TString(TString&& other) noexcept;

        $NoIgnoreReturn
        sizetype indexOf(CharType ch) const noexcept;

        $NoIgnoreReturn
        sizetype indexOf(CharType ch, sizetype getN) const noexcept;

        $NoIgnoreReturn
        sizetype indexOf(const TString& string) const noexcept;

        $NoIgnoreReturn
        sizetype indexOf(const TString& string, sizetype getN) const noexcept;

        $NoIgnoreReturn
        sizetype indexOfLast(const TString& string) const noexcept;

        $NoIgnoreReturn
        sizetype indexOfLast(const TString& string, sizetype getN) const noexcept;

        $NoIgnoreReturn
        sizetype indexOfLast(CharType ch) const noexcept;

        $NoIgnoreReturn
        sizetype indexOfLast(CharType ch, sizetype getN) const noexcept;

        $RetRequiresRelease
        collections::ArrayList<sizetype> indexOfAll(CharType ch) const noexcept;

        $RetRequiresRelease
        collections::ArrayList<sizetype> indexOfAll(const TString& string) const noexcept;

        $NoIgnoreReturn
        TMutString<CharType> toMutable() const;

        $NoIgnoreReturn
        TMutString<CharType> replace(sizetype start, sizetype end, CharType newChar) const;

        $NoIgnoreReturn
        TMutString<CharType> replace(sizetype start, sizetype end, const TString& newSubstring) const;

        $NoIgnoreReturn
        TMutString<CharType> replace(CharType oldChar, CharType newChar) const;

        $NoIgnoreReturn
        TMutString<CharType> replace(const TString& oldSubstring, const TString& newSubstring) const;

        $NoIgnoreReturn
        TMutString<CharType> replace(CharType oldChar, const TString& newSubstring) const;

        $NoIgnoreReturn
        TMutString<CharType> replace(const TString& oldSubstring, CharType newChar) const;

        $NoIgnoreReturn
        TMutString<CharType> replaceAll(CharType oldChar, CharType newChar) const;

        $NoIgnoreReturn
        TMutString<CharType> replaceAll(const TString& oldSubstring, const TString& newSubstring) const;

        $NoIgnoreReturn
        TMutString<CharType> replaceAll(CharType oldChar, const TString& newSubstring) const;

        $NoIgnoreReturn
        TMutString<CharType> replaceAll(const TString& oldSubstring, CharType newChar) const;

        $NoIgnoreReturn
        TMutString<CharType> uppercase() const;

        $NoIgnoreReturn
        TMutString<CharType> lowercase() const;

        $NoIgnoreReturn
        bool operator==(const TString& string) const noexcept;

        $NoIgnoreReturn
        TMutString<CharType> operator+(const TString& string) const;

        $NoIgnoreReturn
        TMutString<CharType> operator+(CharType ch) const;

        $RetSelf
        TString& operator=(const TString& other) noexcept;

        $RetSelf
        TString& operator=(TString&& other) noexcept;
    };

    using String = TString<char>;
#ifdef WCHAR_IS_BUILTIN_TYPE
    using WideString = TString<wchar>;
#endif
    using U8String = TString<u8char>;
    using U16String = TString<u16char>;
    using U32String = TString<u32char>;

    inline namespace literals {
        inline String operator""_s(const char* string, sizetype size) {
            return {string, size};
        }

    #ifdef WCHAR_IS_BUILTIN_TYPE
        inline WideString operator""_s(const wchar* string, sizetype size) {
            return {string, size};
        }
    #endif

        inline U8String operator""_s(const u8char* string, sizetype size) {
            return {string, size};
        }

        inline U16String operator""_s(const u16char* string, sizetype size) {
            return {string, size};
        }

        inline U32String operator""_s(const u32char* string, sizetype size) {
            return {string, size};
        }
    }
}

#define ST_STRING(type, string) enhanced::util::switchType<const type(&)[sizeof(string) / sizeof(char)]> \
    (string, WIDE_TEXT(string), U8_TEXT(string), U16_TEXT(string), U32_TEXT(string))

#define STR(quote) quote##_s
