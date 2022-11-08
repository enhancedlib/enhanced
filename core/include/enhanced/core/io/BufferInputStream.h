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
#include <enhanced/core/io/InputStream.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L3_BEGIN(enhanced, core, io)

class ENHANCED_CORE_API BufferInputStream : public InputStream {
public:
    NoIgnoreRet
    byte get() const override;

    void read(byte* buffer, sizetype size) const override;
};

NAMESPACE_L3_END

#endif
