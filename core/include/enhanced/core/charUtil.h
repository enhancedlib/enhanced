/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced/LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/util/traits.h>

#define __WIDE_TEXT(quote) L##quote
#define WIDE_TEXT(quote) __WIDE_TEXT(quote)

#ifdef CXX_U8CHAR_SUPPORTED
#define __U8_TEXT(quote) u8##quote
#define U8_TEXT(quote) __U8_TEXT(quote)
#endif

#define __U16_TEXT(quote) u##quote
#define U16_TEXT(quote) __U16_TEXT(quote)

#define __U32_TEXT(quote) U##quote
#define U32_TEXT(quote) __U32_TEXT(quote)

#ifdef CXX_U8CHAR_SUPPORTED
#define TCHAR(type, ch) enhanced::core::util::traits::templateSwitch<type>(ch, WIDE_TEXT(ch), U8_TEXT(ch), U16_TEXT(ch), U32_TEXT(ch))
#else
#define TCHAR(type, ch) enhanced::core::util::traits::templateSwitch<type>(ch, WIDE_TEXT(ch), U16_TEXT(ch), U32_TEXT(ch))
#endif
