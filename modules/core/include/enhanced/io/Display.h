/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
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
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
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

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/CoreApi.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Traits.h>
#include <enhanced/String.h>
#include <enhanced/io/OutputStream.h>

#define E_DISPLAY _enhanced_interface_display
#define E_DISPLAY_DECLARE(TYPE, ...) void __VA_ARGS__ E_DISPLAY(const io::OutputStream& out, const enhanced::wrap<TYPE>& value)
#define E_DISPLAY_IMPL(TYPE, OUT, VALUE, ...) void __VA_ARGS__ E_DISPLAY(const io::OutputStream& OUT, const enhanced::wrap<TYPE>& VALUE)

namespace enhanced::io {
    E_API(core) E_DISPLAY_DECLARE(String);
#ifdef E_SM_WCHAR_IS_BUILTIN_TYPE
    E_API(core) E_DISPLAY_DECLARE(WideString);
#endif
    E_API(core) E_DISPLAY_DECLARE(U8String);
    E_API(core) E_DISPLAY_DECLARE(U16String);
    E_API(core) E_DISPLAY_DECLARE(U32String);

    E_API(core) E_DISPLAY_DECLARE(const char*);
    E_API(core) E_DISPLAY_DECLARE(const wchar*);
    E_API(core) E_DISPLAY_DECLARE(const u8char*);
    E_API(core) E_DISPLAY_DECLARE(const u16char*);
    E_API(core) E_DISPLAY_DECLARE(const u32char*);

    E_API(core) E_DISPLAY_DECLARE(char);
#ifdef E_SM_WCHAR_IS_BUILTIN_TYPE
    E_API(core) E_DISPLAY_DECLARE(wchar);
#endif
    E_API(core) E_DISPLAY_DECLARE(u8char);
    E_API(core) E_DISPLAY_DECLARE(u16char);
    E_API(core) E_DISPLAY_DECLARE(u32char);

    E_API(core) E_DISPLAY_DECLARE(int8);
    E_API(core) E_DISPLAY_DECLARE(uint8);
    E_API(core) E_DISPLAY_DECLARE(uint16);
    E_API(core) E_DISPLAY_DECLARE(int16);
    E_API(core) E_DISPLAY_DECLARE(int32);
    E_API(core) E_DISPLAY_DECLARE(uint32);
    E_API(core) E_DISPLAY_DECLARE(int64);
    E_API(core) E_DISPLAY_DECLARE(uint64);

    E_API(core) E_DISPLAY_DECLARE(bool);

    E_API(core) E_DISPLAY_DECLARE(nulltype);

    template <typename Type>
    inline constexpr bool isDisplayable = false;

    template <typename Type>
    requires testValid<decltype(E_DISPLAY(declvalue<const OutputStream&>(), declvalue<const Type&>()))>
    inline constexpr bool isDisplayable<Type> = true;
}
