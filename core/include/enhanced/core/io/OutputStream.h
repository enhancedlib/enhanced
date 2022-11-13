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
#include <enhanced/core/annotations.h>
#include <enhanced/core/String.h>
#include <enhanced/core/io/Closeable.h>
#include <enhanced/core/io/Flushable.h>

namespace enhanced::core::io {
    abstractclass ENHANCED_CORE_API OutputStream : public Closeable, Flushable {
    public:
        virtual func write(byte b) const -> void;

        virtual func write(byte* buffer, sizetype size) const -> void;

        virtual func writeLine(const String& string) const -> void;
    };
}
