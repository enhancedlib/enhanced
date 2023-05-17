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

#define E_DECLARE_TYPE_IMPL_DISPLAY(TYPE, ...) void __VA_ARGS__ display(const io::OutputStream& out, TYPE const& value);

namespace enhanced::io {
    E_DECLARE_TYPE_IMPL_DISPLAY(char, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(wchar, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(u8char, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(u16char, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(u32char, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(int8, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(uint8, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(uint16, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(int16, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(int32, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(uint32, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(int64, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(uint64, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(bool, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(const char*, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(String, ENHANCED_CORE_API);
#ifdef WCHAR_IS_BUILTIN_TYPE
    E_DECLARE_TYPE_IMPL_DISPLAY(WideString, ENHANCED_CORE_API);
#endif
    E_DECLARE_TYPE_IMPL_DISPLAY(U8String, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(U16String, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(U32String, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(nulltype, ENHANCED_CORE_API);

    template <typename Type>
    inline constexpr bool isDisplayable = false;

    template <typename Type>
    requires util::assume<decltype(display(util::declvalue<const OutputStream&>(), util::declvalue<const Type&>()))>
    inline constexpr bool isDisplayable<Type> = true;
}
