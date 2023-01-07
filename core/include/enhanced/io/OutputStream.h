/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
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
    class ENHANCED_CORE_API OutputStream : public Closeable, Flushable {
    public:
        virtual void write(byte b) const;

        virtual void write(const byte* buffer, sizetype size) const;

        virtual void writeLine(const String& string) const;
    };
}
