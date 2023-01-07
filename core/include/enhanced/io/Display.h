/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
 */

#pragma once

#include "enhanced/ExportCore.h"
#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>
#include <enhanced/MutString.h>
#include <enhanced/util/Traits.h>
#include <enhanced/io/OutputStream.h>

namespace enhanced::io {
    template <typename Type>
    struct ENHANCED_CORE_API Display {};

#define _TEMPLATE(TYPE) \
    template <> \
    struct ENHANCED_CORE_API Display<TYPE> { \
        static void display(const OutputStream& out, const TYPE& value); \
    };

    _TEMPLATE(char)
    _TEMPLATE(wchar)
    _TEMPLATE(u8char)
    _TEMPLATE(u16char)
    _TEMPLATE(u32char)

#undef _TEMPLATE

#define _TEMPLATE(TYPE) \
    template <> \
    struct ENHANCED_CORE_API Display<TYPE> { \
        static void display(const OutputStream& out, const TYPE& value); \
    };

    _TEMPLATE(int8)
    _TEMPLATE(uint8)
    _TEMPLATE(uint16)
    _TEMPLATE(int16)
    _TEMPLATE(int32)
    _TEMPLATE(uint32)
    _TEMPLATE(int64)
    _TEMPLATE(uint64)

#undef _TEMPLATE

    template <>
    struct ENHANCED_CORE_API Display<const char*> {
        static void display(const OutputStream& out, const char* const& value);
    };

    template <>
    struct ENHANCED_CORE_API Display<String> {
        static void display(const OutputStream& out, const String& value);
    };

    template <sizetype size>
    struct Display<char[size]> {
        static inline void display(const OutputStream& out, const char (&value)[size]) {
            Display<String>::display(out, {value, size});
        }
    };

    template <>
    struct ENHANCED_CORE_API Display<MutString> {
        static void display(const OutputStream& out, const MutString& value);
    };

    template <>
    struct ENHANCED_CORE_API Display<nulltype> {
        static void display(const OutputStream& out, const nulltype&);
    };

    template <typename Type>
    inline constexpr bool isDisplayable = false;

    template <typename Type>
    requires util::isValid<decltype(Display<Type>::display(util::declvalue<const OutputStream&>(), util::declvalue<Type&>()))>
    inline constexpr bool isDisplayable<Type> = true;
}
