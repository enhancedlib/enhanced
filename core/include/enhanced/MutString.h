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
#include <enhanced/String.h>

namespace enhanced {
    template <typename CharType>
    class ENHANCED_CORE_API TMutString final : public TString<CharType> {
    public:
        TMutString();

        TMutString(const CharType* value, sizetype length);

        template <sizetype size>
        TMutString(const CharType (&value)[size]) : TMutString<CharType>(value, size - 1) {}

        TMutString(const CharType*& value);

        TMutString(CharType* const& value);

        TMutString(CharType*& value);

        explicit TMutString(sizetype length);

        TMutString(const TMutString& other);

        TMutString(TMutString&& other) noexcept;

        $NoIgnoreReturn
        CharType* chars() const noexcept;

        $NoIgnoreReturn
        CharType& at(sizetype index) const noexcept;

        $NoIgnoreReturn
        CharType& operator[](sizetype index) const noexcept;

        TMutString& append(const TString<CharType>& string);

        TMutString& append(CharType ch);

        TMutString& insertFirst(const TString<CharType>& string);

        TMutString& insertFirst(CharType ch);

        TMutString& replaceTo(sizetype start, sizetype end, CharType newChar);

        TMutString& replaceTo(sizetype start, sizetype end, const TString<CharType>& newSubstring);

        TMutString& replaceTo(CharType oldChar, CharType newChar);

        TMutString& replaceTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring);

        TMutString& replaceTo(CharType oldChar, const TString<CharType>& newSubstring);

        TMutString& replaceTo(const TString<CharType>& oldSubstring, CharType newChar);

        TMutString& replaceAllTo(CharType oldChar, CharType newChar);

        TMutString& replaceAllTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring);

        TMutString& replaceAllTo(CharType oldChar, const TString<CharType>& newSubstring);

        TMutString& replaceAllTo(const TString<CharType>& oldSubstring, CharType newChar);

        TMutString& fill(CharType ch);

        TMutString& toUppercase();

        TMutString& toLowercase();

        $RetSelf
        TMutString& operator=(const TMutString& other);

        $RetSelf
        TMutString& operator=(TMutString&& other) noexcept;

        TMutString& operator+=(const TString<CharType>& string);

        TMutString& operator+=(CharType ch);
    };

    using MutString = TMutString<char>;
#ifdef WCHAR_IS_BUILTIN_TYPE
    using WideMutString = TMutString<wchar>;
#endif
    using U8MutString = TMutString<u8char>;
    using U16MutString = TMutString<u16char>;
    using U32MutString = TMutString<u32char>;

    inline namespace literals {
        inline MutString operator""_m(const char* string, sizetype size) {
            return {string, size};
        }

    #ifdef WCHAR_IS_BUILTIN_TYPE
        inline WideMutString operator""_m(const wchar* string, sizetype size) {
            return {string, size};
        }
    #endif

        inline U8MutString operator""_m(const u8char* string, sizetype size) {
            return {string, size};
        }

        inline U16MutString operator""_m(const u16char* string, sizetype size) {
            return {string, size};
        }

        inline U32MutString operator""_m(const u32char* string, sizetype size) {
            return {string, size};
        }
    }
}

#define MUT_STR(quote) quote##_m
