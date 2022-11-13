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

#include <enhanced/core/io/InputStream.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/String.h>
#include <enhanced/core/MutString.h>
#include <enhanced/core/exception/NotImplementedError.h>

using enhanced::core::io::InputStream;
using enhanced::core::MutString;

func InputStream::get() const -> byte {
    NOT_IMPLEMENTED();
}

func InputStream::read(byte *buffer, sizetype size) const -> void {
    NOT_IMPLEMENTED();
}

func InputStream::readLine() const -> MutString {
    NOT_IMPLEMENTED();
}
