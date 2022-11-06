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
#include <enhanced/core/annotations.h>
#include <enhanced/core/String.h>
#include <enhanced/core/io/Closeable.h>

#ifdef CXX_LANGUAGE

namespace enhanced::core::io {
    struct AbstractClass ENHANCED_CORE_API InputStream : public Closeable {
        RetCannotIgnored
        virtual char get() const;

        virtual void read(char* buffer, Size size) const;

        RetCannotIgnored
        virtual String readLine() const = 0;
    };
}

#endif
