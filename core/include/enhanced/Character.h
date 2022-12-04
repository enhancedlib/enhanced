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

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/util/Traits.h>

#define WIDE_TEXT(quote) L##quote
#define U8_TEXT(quote) u8##quote
#define U16_TEXT(quote) u##quote
#define U32_TEXT(quote) U##quote

#define ST_CHAR(type, ch) enhanced::util::switchType<type>(ch, WIDE_TEXT(ch), U8_TEXT(ch), U16_TEXT(ch), U32_TEXT(ch))
