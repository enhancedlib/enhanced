/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>
#include <enhanced/MutString.h>
#include <enhanced/util/Traits.h>
#include <enhanced/io/OutputStream.h>

#define E_DECLARE_TYPE_IMPL_DISPLAY(TYPE, ...) \
    template <> \
    struct __VA_ARGS__ Display<TYPE> { \
        using DisplayType = TYPE; \
        static void display(const OutputStream& out, util::AddConstLvaRef<DisplayType> value); \
    }

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define DECLARE_TYPE_IMPL_DISPLAY E_DECLARE_TYPE_IMPL_DISPLAY
#endif

namespace enhanced::io {
    template <typename Type>
    struct Display {};

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
    E_DECLARE_TYPE_IMPL_DISPLAY(MutString, ENHANCED_CORE_API);
    E_DECLARE_TYPE_IMPL_DISPLAY(nulltype, ENHANCED_CORE_API);

    template <sizetype size>
    struct Display<char[size]> {
        static inline void display(const OutputStream& out, const char (&value)[size]) {
            Display<String>::display(out, {value, size});
        }
    };

    template <typename Type>
    inline constexpr bool isDisplayable = false;

    template <typename Type>
    requires util::assume<decltype(Display<util::RemoveRefAndCv<Type>>::
        display(util::declvalue<const OutputStream&>(), util::declvalue<const Type&>()))>
    inline constexpr bool isDisplayable<Type> = true;
}
