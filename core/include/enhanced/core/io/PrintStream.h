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
#include <enhanced/core/io/OutputStream.h>

#ifdef CXX_LANGUAGE

namespace enhanced::core::io {
    class ENHANCED_CORE_API PrintStream : public OutputStream {
    public:
        void print(int8 i8);

        void print(int16 i16);

        void print(int32 i32);

        void print(int64 i64);

        void print(float32 i32);

        void print(float64 i64);

        void close() override;
    };
}

#endif
