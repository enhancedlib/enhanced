/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 sharedwonder (Liu Baihao). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, except for distributing modified versions and
 *    products that use the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <enhanced/io/Display.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>

namespace enhanced::io {
#define __TEMPLATE(TYPE) \
    E_DISPLAY_IMPL(const TYPE*, out, value) { \
        auto str = TString<TYPE>::from(value); \
        out.write(str.toBytes(), str.getLength() * sizeof(TYPE)); \
    } \
    E_DISPLAY_IMPL(TString<TYPE>, out, value) { \
        out.write(value.toBytes(), value.getLength() * sizeof(TYPE)); \
    } \
    E_DISPLAY_IMPL(TYPE, out, value) { \
        auto string = TString<TYPE>::from(value); \
        out.write(string.toBytes(), string.getLength() * sizeof(TYPE)); \
    }

    __TEMPLATE(char)
    __TEMPLATE(wchar)
    __TEMPLATE(u8char)
    __TEMPLATE(u16char)
    __TEMPLATE(u32char)

#undef __TEMPLATE

#define __TEMPLATE(TYPE) \
    E_DISPLAY_IMPL(TYPE, out, value) { \
        auto string = String::from(value); \
        out.write(string.toBytes(), string.getLength() * sizeof(char)); \
    } \

    __TEMPLATE(int8)
    __TEMPLATE(uint8)
    __TEMPLATE(uint16)
    __TEMPLATE(int16)
    __TEMPLATE(int32)
    __TEMPLATE(uint32)
    __TEMPLATE(int64)
    __TEMPLATE(uint64)
    __TEMPLATE(bool)

#undef __TEMPLATE

    E_DISPLAY_IMPL(nulltype, out,) {
        out.write("null"_e.toBytes(), 4 * sizeof(char));
    }
}
