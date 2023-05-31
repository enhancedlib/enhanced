/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/ExportCore.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/String.h>
#include <enhanced/io/Closeable.h>
#include <enhanced/io/Flushable.h>

namespace enhanced::io {
    // TODO: Support encoding
    class E_CORE_API OutputStream : public Closeable, Flushable {
    public:
        virtual void write(byte b) const;

        virtual void write(const byte* buffer, sizetype size) const;

        virtual void writeLine(const String& string) const;
    };
}
