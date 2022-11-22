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
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/String.h>
#include <enhanced/core/io/OutputStream.h>

namespace enhanced::core::io {
    class ENHANCED_CORE_API WarpedOutputStream : public OutputStream {
    public:
        func print(char ch) -> void;

    #ifdef WCHAR_IS_BUILTIN_TYPE
        func print(wchar wch) -> void;
    #endif

        func print(u8char u8ch) -> void;

        func print(u16char u16ch) -> void;

        func print(u32char u32ch) -> void;

        func print(bool boolean) -> void;

        func print(int8 i8) -> void;

        func print(uint8 u8) -> void;

        func print(int16 i16) -> void;

        func print(uint16 u16) -> void;

        func print(int32 i32) -> void;

        func print(uint32 u32) -> void;

        func print(int64 i64) -> void;

        func print(uint64 u64) -> void;

        func print(float32 i32) -> void;

        func print(float64 i64) -> void;

        func print(const char* message) -> void;

        func print(const String& message) -> void;

        func print(void* address) -> void;

        func print(nulltype) -> void;

        func printf(const String& message, ...) -> void;

        func close() const -> void override;

        func flush() const -> void override;
    };
}
