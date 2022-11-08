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

#include <enhanced/core/io/OutputStream.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/export.h>
#include <enhanced/core/String.h>
#include <enhanced/core/exception/NotImplementedError.h>

using enhanced::core::io::OutputStream;

void OutputStream::write(byte b) const {
    NOT_IMPLEMENTED();
}

void OutputStream::write(byte* buffer, sizetype size) const {
    NOT_IMPLEMENTED();
}

void OutputStream::writeLine(const String& string) const {
    NOT_IMPLEMENTED();
}
