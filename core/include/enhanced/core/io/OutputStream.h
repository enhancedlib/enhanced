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
#include <enhanced/core/String.h>
#include <enhanced/core/io/Closeable.h>

#ifdef CXX_LANGUAGE

namespace enhanced::core::io {
    struct AbstractClass ENHANCED_CORE_API OutputStream : public Closeable {
        virtual void write(char ch) const;

        virtual void write(const char* message) const;

        virtual void write(String& message) const;

        virtual void writeLine(const char* message) const;

        virtual void writeLine(String& message) const;
    };
}

#endif
