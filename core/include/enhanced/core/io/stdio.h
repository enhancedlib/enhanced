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
#include <enhanced/core/io/WarpedInputStream.h>
#include <enhanced/core/io/WarpedOutputStream.h>

#ifdef CXX_LANGUAGE

NAMESPACE_L3_BEGIN(enhanced, core, io)

ENHANCED_CORE_API extern WarpedInputStream* const& instream;
ENHANCED_CORE_API extern WarpedOutputStream* const& outstream;
ENHANCED_CORE_API extern WarpedOutputStream* const& errstream;

ENHANCED_CORE_API void setIn(InputStream* in);
ENHANCED_CORE_API void setOut(WarpedOutputStream* out);
ENHANCED_CORE_API void setErr(WarpedOutputStream* err);

NAMESPACE_L3_END

#endif
