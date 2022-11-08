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
#include <enhanced/core/export.h>
#include <enhanced/core/String.h>
#include <enhanced/core/io/OutputStream.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L3_BEGIN(enhanced, core, io)

class ENHANCED_CORE_API WarpedOutputStream : public OutputStream {
public:
    void print(char ch);

    void print(wchar wch);

#ifdef WCHAR_IS_BUILTIN_TYPE
    void print(ushort wch);
#endif

#ifdef CXX_U8CHAR_SUPPORTED
    void print(u8char u8ch);
#endif

#ifdef CXX_11_OR_LATER
    void print(u16char u16ch);

    void print(u32char u32ch);
#endif

    void print(int8 i8);

    void print(int16 i16);

    void print(int32 i32);

    void print(int64 i64);

    void print(float32 i32);

    void print(float64 i64);

    void print(const String& message);

    void close() const override;

    void flush() const override;
};

NAMESPACE_L3_END

#endif
