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

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Character.h>
#include <enhanced/CharSequence.h>
#include <enhanced/InitializerList.h>
#include <enhanced/util/Traits.h>
#include <enhanced/collections/ArrayList.h>

#define E_SWITCH_STR(TYPE, STRING) enhanced::util::switchType<const TYPE(&)[sizeof(STRING) / sizeof(char)]> \
    (STRING, L##STRING, u8##STRING, u##STRING, U##STRING)

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define SWITCH_STR E_SWITCH_STR
#endif

namespace enhanced {
    template <typename CharType>
    requires util::isCharType<CharType>
    class ENHANCED_CORE_API TString : public CharSequence<CharType> {
    protected:
        TString(const CharType* value, sizetype length, bool isOwn) noexcept;

        E_ANNOTATE(RetNotIgnored)
        static TString from(qword value, bool isNegative);

    public:
        E_ANNOTATE(RetNotIgnored)
        static TString<CharType> from(bool value);

        E_ANNOTATE(RetNotIgnored)
        static TString from(CharType value);

        template <typename IntTypeNs>
        requires util::isIntegralTypeNs<IntTypeNs>
        E_ANNOTATE(RetNotIgnored)
        static inline TString from(IntTypeNs value) {
            return from(value, value < 0);
        }

        E_ANNOTATE(RetNotIgnored)
        static inline TString<CharType> from(const CharType* value) {
            return TString(static_cast<const CharType*&>(value));
        }

        E_ANNOTATE(RetNotIgnored)
        static TString<CharType> own(const CharType* value, sizetype length);

        E_ANNOTATE(RetNotIgnored)
        static TString<CharType> own(const CharType* value);

        template <sizetype size>
        E_ANNOTATE(RetNotIgnored)
        static inline TString own(const wrap<CharType[size]>& value) {
            return own(value, size);
        }

        TString() noexcept;

        TString(const CharType* value, sizetype length) noexcept;

        template <sizetype size>
        inline TString(const wrap<CharType[size]>& value) noexcept : TString((CharType*) value, size - 1) {}

        TString(const CharType*& value) noexcept;

        TString(CharType*& value) noexcept;

        TString(CharType* const& value) noexcept;

        explicit TString(sizetype length);

        TString(const TString* strings, sizetype count);

        E_INIT_LIST_CONSTRUCTOR(TString, TString)
        TString(InitializerList<TString> list);

        TString(const TString& other);

        TString(TString&& other) noexcept;

        E_ANNOTATE(RetNotIgnored)
        sizetype indexOf(CharType ch) const noexcept;

        E_ANNOTATE(RetNotIgnored)
        sizetype indexOf(CharType ch, sizetype getN) const noexcept;

        E_ANNOTATE(RetNotIgnored)
        sizetype indexOf(const TString& string) const noexcept;

        E_ANNOTATE(RetNotIgnored)
        sizetype indexOf(const TString& string, sizetype getN) const noexcept;

        E_ANNOTATE(RetNotIgnored)
        sizetype indexOfLast(const TString& string) const noexcept;

        E_ANNOTATE(RetNotIgnored)
        sizetype indexOfLast(const TString& string, sizetype getN) const noexcept;

        E_ANNOTATE(RetNotIgnored)
        sizetype indexOfLast(CharType ch) const noexcept;

        E_ANNOTATE(RetNotIgnored)
        sizetype indexOfLast(CharType ch, sizetype getN) const noexcept;

        E_ANNOTATE(RetRequiresRelease)
        collections::ArrayList<sizetype> indexOfAll(CharType ch) const noexcept;

        E_ANNOTATE(RetRequiresRelease)
        collections::ArrayList<sizetype> indexOfAll(const TString& string) const noexcept;

        E_ANNOTATE(RetNotIgnored)
        bool ownStorage() const noexcept;

        E_ANNOTATE(RetNotIgnored)
        TString replace(sizetype start, sizetype end, CharType newChar) const;

        E_ANNOTATE(RetNotIgnored)
        TString replace(sizetype start, sizetype end, const TString& newSubstring) const;

        E_ANNOTATE(RetNotIgnored)
        TString replace(CharType oldChar, CharType newChar) const;

        E_ANNOTATE(RetNotIgnored)
        TString replace(const TString& oldSubstring, const TString& newSubstring) const;

        E_ANNOTATE(RetNotIgnored)
        TString replace(CharType oldChar, const TString& newSubstring) const;

        E_ANNOTATE(RetNotIgnored)
        TString replace(const TString& oldSubstring, CharType newChar) const;

        E_ANNOTATE(RetNotIgnored)
        TString replaceAll(CharType oldChar, CharType newChar) const;

        E_ANNOTATE(RetNotIgnored)
        TString replaceAll(const TString& oldSubstring, const TString& newSubstring) const;

        E_ANNOTATE(RetNotIgnored)
        TString replaceAll(CharType oldChar, const TString& newSubstring) const;

        E_ANNOTATE(RetNotIgnored)
        TString replaceAll(const TString& oldSubstring, CharType newChar) const;

        E_ANNOTATE(RetNotIgnored)
        TString uppercase() const;

        E_ANNOTATE(RetNotIgnored)
        TString lowercase() const;

        TString& toOwn();

        TString& set(sizetype index, CharType ch);

        TString& append(CharType ch);

        TString& append(const TString<CharType>& string);

        TString& insertFirst(CharType ch);

        TString& insertFirst(const TString<CharType>& string);

        TString& replaceTo(sizetype start, sizetype end, CharType newChar);

        TString& replaceTo(sizetype start, sizetype end, const TString<CharType>& newSubstring);

        TString& replaceTo(CharType oldChar, CharType newChar);

        TString& replaceTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring);

        TString& replaceTo(CharType oldChar, const TString<CharType>& newSubstring);

        TString& replaceTo(const TString<CharType>& oldSubstring, CharType newChar);

        TString& replaceAllTo(CharType oldChar, CharType newChar);

        TString& replaceAllTo(const TString<CharType>& oldSubstring, const TString<CharType>& newSubstring);

        TString& replaceAllTo(CharType oldChar, const TString<CharType>& newSubstring);

        TString& replaceAllTo(const TString<CharType>& oldSubstring, CharType newChar);

        TString& fill(CharType ch) noexcept;

        TString& toUppercase();

        TString& toLowercase();

        E_ANNOTATE(RetNotIgnored)
        bool operator==(const TString& string) const noexcept;

        E_ANNOTATE(RetNotIgnored)
        inline bool operator==(const CharType* string) const noexcept {
            return operator==(TString::from(string));
        }

        template <sizetype size>
        E_ANNOTATE(RetNotIgnored)
        inline bool operator==(const CharType (&string)[size]) const noexcept {
            return operator==(TString(string));
        }

        E_ANNOTATE(RetNotIgnored)
        TString operator+(const TString& string) const;

        E_ANNOTATE(RetNotIgnored)
        TString operator+(CharType ch) const;

        E_ANNOTATE(ReturnSelf)
        TString& operator=(const TString& other) noexcept;

        E_ANNOTATE(ReturnSelf)
        TString& operator=(TString&& other) noexcept;

        TString& operator+=(const TString<CharType>& string);

        TString& operator+=(CharType ch);
    };

    template <typename CharType>
    requires util::isCharType<CharType>
    struct TStringUtil {
        TStringUtil() = delete;

        ~TStringUtil() = delete;

        E_ANNOTATE(RetRequiresRelease)
        static CharType* make(sizetype length);

        E_ANNOTATE(RetRequiresRelease)
        static CharType* copy(const CharType* source);

        template <sizetype size>
        E_ANNOTATE(RetRequiresRelease)
        static inline CharType* copy(const wrap<CharType[size]>& source) {
            return copy(source, size);
        }

        E_ANNOTATE(RetRequiresRelease)
        static CharType* copy(const CharType* source, sizetype length);

        E_ANNOTATE(RetRequiresRelease)
        static CharType* copy(sizetype newLength, const CharType* source, sizetype oldLength);

        template <sizetype size>
        E_ANNOTATE(RetRequiresRelease)
        static inline CharType* copy(sizetype newLength, const wrap<CharType[size]>& source) {
            return copy(newLength, source, size);
        }

        E_ANNOTATE(RetNotIgnored)
        static sizetype calcLength(const CharType* string) noexcept;

        E_ANNOTATE(RetNotIgnored)
        static bool isEqual(const CharType* string1, const CharType* string2) noexcept;

        E_ANNOTATE(RetNotIgnored)
        static bool isEqual(const CharType* string1, sizetype length1, const CharType* string2) noexcept;

        E_ANNOTATE(RetNotIgnored)
        static bool isEqual(const CharType* string1, const CharType* string2, sizetype length2) noexcept;

        E_ANNOTATE(RetNotIgnored)
        static bool isEqual(const CharType* string1, sizetype length1, const CharType* string2, sizetype length2) noexcept;

        template <sizetype size2>
        E_ANNOTATE(RetNotIgnored)
        static inline bool isEqual(const CharType* string1, sizetype length1, const wrap<CharType[size2]>& string2) noexcept {
            return isEqual(string1, length1, string2, size2);
        }

        template <sizetype size1>
        E_ANNOTATE(RetNotIgnored)
        static inline bool isEqual(const wrap<CharType[size1]>& string1, const CharType* string2, sizetype length2) noexcept {
            return isEqual(string1, size1, string2, length2);
        }

        template <sizetype size1, sizetype size2>
        E_ANNOTATE(RetNotIgnored)
        static constexpr bool isEqual(const wrap<CharType[size1]>& string1, const wrap<CharType[size2]>& string2) noexcept {
            if (size1 != size2) return false;

            for (sizetype index = 0; index < size1; ++index) {
                if (string1[index] != string2[index]) return false;
            }

            return true;
        }
    };

    using String = TString<char>;
#ifdef WCHAR_IS_BUILTIN_TYPE
    using WideString = TString<wchar>;
#endif
    using U8String = TString<u8char>;
    using U16String = TString<u16char>;
    using U32String = TString<u32char>;

    using StringUtil = TStringUtil<char>;
#ifdef WCHAR_IS_BUILTIN_TYPE
    using WideStringUtil = TStringUtil<wchar>;
#endif
    using U8StringUtil = TStringUtil<u8char>;
    using U16StringUtil = TStringUtil<u16char>;
    using U32StringUtil = TStringUtil<u32char>;

    inline namespace literals {
        inline String operator""_e(const char* string, sizetype size) {
            return {string, size};
        }

    #ifdef WCHAR_IS_BUILTIN_TYPE
        inline WideString operator""_e(const wchar* string, sizetype size) {
            return {string, size};
        }
    #endif

        inline U8String operator""_e(const u8char* string, sizetype size) {
            return {string, size};
        }

        inline U16String operator""_e(const u16char* string, sizetype size) {
            return {string, size};
        }

        inline U32String operator""_e(const u32char* string, sizetype size) {
            return {string, size};
        }

        inline String operator""_eo(const char* string, sizetype size) {
            return String::own(string, size);
        }

    #ifdef WCHAR_IS_BUILTIN_TYPE
        inline WideString operator""_eo(const wchar* string, sizetype size) {
            return WideString::own(string, size);
        }
    #endif

        inline U8String operator""_eo(const u8char* string, sizetype size) {
            return U8String::own(string, size);
        }

        inline U16String operator""_eo(const u16char* string, sizetype size) {
            return U16String::own(string, size);
        }

        inline U32String operator""_eo(const u32char* string, sizetype size) {
            return U32String::own(string, size);
        }
    }
}
