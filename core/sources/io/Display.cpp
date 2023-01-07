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

#include <enhanced/io/Display.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>
#include <enhanced/MutString.h>

namespace enhanced::io {
    // TODO: Support encoding

#define _TEMPLATE(TYPE) \
    void Display<TYPE>::display(const OutputStream& out, const TYPE& value) { \
        auto string = TString<TYPE>::from(value); \
        out.write(string.toBytes(), string.getLength() * sizeof(TYPE)); \
    } \

    _TEMPLATE(char)
    _TEMPLATE(wchar)
    _TEMPLATE(u8char)
    _TEMPLATE(u16char)
    _TEMPLATE(u32char)

#undef _TEMPLATE

#define _TEMPLATE(TYPE) \
    void Display<TYPE>::display(const OutputStream& out, const TYPE& value) { \
        auto string = String::from(value); \
        out.write(string.toBytes(), string.getLength() * sizeof(char)); \
    } \

    _TEMPLATE(int8)
    _TEMPLATE(uint8)
    _TEMPLATE(uint16)
    _TEMPLATE(int16)
    _TEMPLATE(int32)
    _TEMPLATE(uint32)
    _TEMPLATE(int64)
    _TEMPLATE(uint64)

#undef _TEMPLATE

    void Display<const char*>::display(const OutputStream& out, const char* const& value) {
        out.write(String(const_cast<const char*&>(value)).toBytes(), String::from(value).getLength() * sizeof(char));
    }

    void Display<String>::display(const OutputStream& out, const String& value) {
        out.write(value.toBytes(), value.getLength() * sizeof(char));
    }

    void Display<MutString>::display(const OutputStream& out, const MutString& value) {
        out.write(value.toBytes(), value.getLength() * sizeof(char));
    }

    void Display<nulltype>::display(const OutputStream& out, const nulltype&) {
        out.write("null"_ES.toBytes(), 4 * sizeof(char));
    }
}
