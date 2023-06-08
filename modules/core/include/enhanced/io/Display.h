/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute, subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not charge any fees or receive other compensation for the
 *    distribution of the Software.
 *
 * 3. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 4. If you use this Software in your product, you should indicate the it in
 *    the product documentation.
 *
 * Unless you have obtained the written consent of the copyright holders,
 * you may not break these restrictions.
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
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>
#include <enhanced/util/Traits.h>
#include <enhanced/io/OutputStream.h>

#define E_DISPLAY __E_interface_display
#define E_DISPLAY_DECLARE(TYPE, ...) void __VA_ARGS__ E_DISPLAY(const io::OutputStream& out, const enhanced::wrap<TYPE>& value)

#ifdef E_SM_MACRO_NO_PREFIX_ALIAS
    #define DISPLAY E_DISPLAY
    #define DECLARE_TYPE_IMPL_DISPLAY E_DECLARE_TYPE_IMPL_DISPLAY
#endif

namespace enhanced::io {
    E_CORE_API E_DISPLAY_DECLARE(char);
#ifdef WCHAR_IS_BUILTIN_TYPE
    E_CORE_API E_DISPLAY_DECLARE(wchar);
#endif
    E_CORE_API E_DISPLAY_DECLARE(u8char);
    E_CORE_API E_DISPLAY_DECLARE(u16char);
    E_CORE_API E_DISPLAY_DECLARE(u32char);
    E_CORE_API E_DISPLAY_DECLARE(int8);
    E_CORE_API E_DISPLAY_DECLARE(uint8);
    E_CORE_API E_DISPLAY_DECLARE(uint16);
    E_CORE_API E_DISPLAY_DECLARE(int16);
    E_CORE_API E_DISPLAY_DECLARE(int32);
    E_CORE_API E_DISPLAY_DECLARE(uint32);
    E_CORE_API E_DISPLAY_DECLARE(int64);
    E_CORE_API E_DISPLAY_DECLARE(uint64);
    E_CORE_API E_DISPLAY_DECLARE(bool);
    E_CORE_API E_DISPLAY_DECLARE(const char*);
    E_CORE_API E_DISPLAY_DECLARE(String);
#ifdef WCHAR_IS_BUILTIN_TYPE
    E_CORE_API E_DISPLAY_DECLARE(WideString);
#endif
    E_CORE_API E_DISPLAY_DECLARE(U8String);
    E_CORE_API E_DISPLAY_DECLARE(U16String);
    E_CORE_API E_DISPLAY_DECLARE(U32String);
    E_CORE_API E_DISPLAY_DECLARE(nulltype);

    template <typename Type>
    inline constexpr bool isDisplayable = false;

    template <typename Type>
    requires util::assume<decltype(E_DISPLAY(util::declvalue<const OutputStream&>(), util::declvalue<const Type&>()))>
    inline constexpr bool isDisplayable<Type> = true;
}
