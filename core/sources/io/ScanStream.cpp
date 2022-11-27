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

#include <enhanced/io/PrintStream.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/exceptions/NotImplementedError.h>

namespace enhanced::io {
    func PrintStream::print(char ch) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(wchar wch) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(u8char u8ch) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(u16char u16ch) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(u32char u32ch) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(bool boolean) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(int8 i8) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(uint8 u8) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(int16 i16) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(uint16 u16) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(int32 i32) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(uint32 u32) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(int64 i64) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(uint64 u64) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(float32 i32) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(float64 i64) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(const char* message) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(const String& message) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(void* address) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::print(nulltype) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::printf(const String& message, ...) -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::close() const -> void {
        NOT_IMPLEMENTED();
    }

    func PrintStream::flush() const -> void {
        NOT_IMPLEMENTED();
    }
}
