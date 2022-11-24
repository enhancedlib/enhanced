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

#include <enhanced/core/defines.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/annotations.h>
#include <enhanced/core/String.h>

namespace enhanced::core {
    template <typename CharType>
    class ENHANCED_CORE_API TMutString final : public TString<CharType> {
    public:
        TMutString();

        TMutString(const CharType* value, sizetype length) noexcept;

        template <sizetype size>
        TMutString(const CharType (&value)[size]) : TMutString<CharType>(value, size - 1) {}

        TMutString(const CharType*& value);

        TMutString(CharType* const& value);

        TMutString(CharType*& value);

        explicit TMutString(sizetype length);

        TMutString(const TMutString& other);

        TMutString(TMutString&& other) noexcept;

        ~TMutString() noexcept;

        $(NoIgnoreReturn)
        func at(sizetype index) const noexcept -> CharType&;

        $(NoIgnoreReturn)
        func operator[](sizetype index) const noexcept -> CharType&;

        func append(const TString<CharType>& other) -> TMutString&;

        func replaceTo(sizetype start, sizetype end, CharType newChar) -> TMutString&;

        func replaceTo(sizetype start, sizetype end, const TString<CharType>& newSubstring) -> TMutString&;

        func replaceTo(CharType oldChar, CharType newChar) -> TMutString&;

        func replaceTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) -> TMutString&;

        func replaceTo(CharType oldChar, const TString<CharType>& newSubstring) -> TMutString&;

        func replaceTo(const TString<CharType>& oldSubstring, CharType newChar) -> TMutString&;

        func replaceAllTo(CharType oldChar, CharType newChar) -> TMutString&;

        func replaceAllTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring) -> TMutString&;

        func replaceAllTo(CharType oldChar, const TString<CharType>& newSubstring) -> TMutString&;

        func replaceAllTo(const TString<CharType>& oldSubstring, CharType newChar) -> TMutString&;

        func fill(CharType ch) -> TMutString&;

        func toUppercase() -> TMutString&;

        func toLowercase() -> TMutString&;

        func operator=(const TMutString& other) -> TMutString&;

        func operator=(TMutString&& other) noexcept -> TMutString&;

        func operator+=(const TString<CharType>& other) -> TMutString&;
    };

    using MutString = TMutString<char>;
    #ifdef WCHAR_IS_BUILTIN_TYPE
    using WideMutString = TMutString<wchar>;
    #endif
    using U8MutString = TMutString<u8char>;
    using U16MutString = TMutString<u16char>;
    using U32MutString = TMutString<u32char>;

    inline namespace literals {
        inline func operator""_m(const char* string, sizetype size) -> MutString {
            return {string, size};
        }

    #ifdef WCHAR_IS_BUILTIN_TYPE
        inline func operator""_m(const wchar* string, sizetype size) -> WideMutString {
            return {string, size};
        }
    #endif

        inline func operator""_m(const u8char* string, sizetype size) -> U8MutString {
            return {string, size};
        }

        inline func operator""_m(const u16char* string, sizetype size) -> U16MutString {
            return {string, size};
        }

        inline func operator""_m(const u32char* string, sizetype size) -> U32MutString {
            return {string, size};
        }
    }
}

#define MUT_STR(quote) quote##_m
