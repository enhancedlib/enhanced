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

#include <enhanced/io/Display.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>

namespace enhanced::io {
#define _TEMPLATE(TYPE) \
    void E_DISPLAY(const OutputStream& out, const TYPE& value) { \
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
    void E_DISPLAY(const OutputStream& out, const TYPE& value) { \
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
    _TEMPLATE(bool)

#undef _TEMPLATE

    void E_DISPLAY(const OutputStream& out, const char* const& value) {
        auto str = String::from(value);
        out.write(str.toBytes(), str.getLength() * sizeof(char));
    }

    void E_DISPLAY(const OutputStream& out, const String& value) {
        out.write(value.toBytes(), value.getLength() * sizeof(char));
    }

    void E_DISPLAY(const OutputStream& out, const nulltype&) {
        out.write("null"_e.toBytes(), 4 * sizeof(char));
    }
}
