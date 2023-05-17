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
#include <enhanced/Types.h>
#include <enhanced/util/Traits.h>

#define E_SWITCH_CHAR(TYPE, CH) enhanced::util::switchType<TYPE>(CH, L##CH, u8##CH, u##CH, U##CH)

#ifdef ENHANCED_MACRO_NO_PREFIX_ALIAS
    #define SWITCH_CHAR E_SWITCH_CHAR
#endif

namespace enhanced {
    template <typename CharType>
    requires util::isCharType<CharType>
    inline constexpr CharType uppercase(CharType ch) {
        if (ch >= E_SWITCH_CHAR(CharType, 'A') && ch <= E_SWITCH_CHAR(CharType, 'Z')) {
            (ch -= E_SWITCH_CHAR(CharType, 'A')) += E_SWITCH_CHAR(CharType, 'a');
        }
        return ch;
    }

    template <typename CharType>
    requires util::isCharType<CharType>
    inline constexpr CharType lowercase(CharType ch) {
        if (ch >= E_SWITCH_CHAR(CharType, 'A') && ch <= E_SWITCH_CHAR(CharType, 'Z')) {
            (ch -= E_SWITCH_CHAR(CharType, 'A')) += E_SWITCH_CHAR(CharType, 'a');
        }
        return ch;
    }
}
