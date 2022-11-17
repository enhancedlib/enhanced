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

#include <enhanced/core/io/WarpedOutputStream.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/String.h>
#include <enhanced/core/exception/NotImplementedError.h>

namespace enhanced::core::io {
    func WarpedOutputStream::print(char ch) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(wchar wch) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(u8char u8ch) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(u16char u16ch) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(u32char u32ch) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(bool boolean) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(int8 i8) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(int16 i16) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(int32 i32) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(int64 i64) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(float32 i32) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(float64 i64) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(const String& message) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(void* address) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::print(nulltype) -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::close() const -> void {
        NOT_IMPLEMENTED();
    }

    func WarpedOutputStream::flush() const -> void {
        NOT_IMPLEMENTED();
    }
}
