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
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/io/OutputStream.h>

namespace enhanced::io {
    class ENHANCED_CORE_API PrintStream : public OutputStream {
    public:
        void print(char ch);

    #ifdef WCHAR_IS_BUILTIN_TYPE
        void print(wchar wch);
    #endif

        void print(u8char u8ch);

        void print(u16char u16ch);

        void print(u32char u32ch);

        void print(bool boolean);

        void print(int8 i8);

        void print(uint8 u8);

        void print(int16 i16);

        void print(uint16 u16);

        void print(int32 i32);

        void print(uint32 u32);

        void print(int64 i64);

        void print(uint64 u64);

        void print(float32 i32);

        void print(float64 i64);

        void print(const char* message);

        void print(const String& message);

        void print(void* address);

        void print(nulltype);

        void println();

        void println(char ch);

    #ifdef WCHAR_IS_BUILTIN_TYPE
        void println(wchar wch);
    #endif

        void println(u8char u8ch);

        void println(u16char u16ch);

        void println(u32char u32ch);

        void println(bool boolean);

        void println(int8 i8);

        void println(uint8 u8);

        void println(int16 i16);

        void println(uint16 u16);

        void println(int32 i32);

        void println(uint32 u32);

        void println(int64 i64);

        void println(uint64 u64);

        void println(float32 i32);

        void println(float64 i64);

        void println(const char* message);

        void println(const String& message);

        void println(void* address);

        void println(nulltype);

        void printf(const String& message, ...);

        void close() const override;

        void flush() const override;
    };
}
