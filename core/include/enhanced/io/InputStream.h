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
#include <enhanced/Annotations.h>
#include <enhanced/Types.h>
#include <enhanced/MutString.h>
#include <enhanced/io/Closeable.h>
#include <enhanced/io/Flushable.h>

namespace enhanced::io {
    abstractclass ENHANCED_CORE_API InputStream : public Closeable, Flushable {
    public:
        $NoIgnoreReturn
        virtual func get() const -> byte;

        virtual func read(byte* buffer, sizetype size) const -> void;

        $NoIgnoreReturn
        virtual func readLine() const -> MutString;
    };
}
