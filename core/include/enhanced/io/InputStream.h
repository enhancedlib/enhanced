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
#include <enhanced/Annotations.h>
#include <enhanced/Types.h>
#include <enhanced/MutString.h>
#include <enhanced/io/Closeable.h>
#include <enhanced/io/Flushable.h>

namespace enhanced::io {
    class ENHANCED_CORE_API InputStream : public Closeable, Flushable {
    public:
        $NoIgnoreReturn
        virtual byte get() const;

        virtual void read(byte* buffer, sizetype size) const;

        $NoIgnoreReturn
        virtual MutString readLine() const;
    };
}
