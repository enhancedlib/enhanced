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
#include <enhanced/core/annotations.h>
#include <enhanced/core/types.h>
#include <enhanced/core/MutableString.h>
#include <enhanced/core/io/Closeable.h>
#include <enhanced/core/io/Flushable.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L3_BEGIN(enhanced, core, io)

struct AbstractClass ENHANCED_CORE_API InputStream : public Closeable, Flushable {
    NoIgnoreRet
    virtual byte get() const;

    virtual void read(byte* buffer, sizetype size) const;

    NoIgnoreRet
    virtual MutableString readLine() const;
};

NAMESPACE_L3_END

#endif
