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
