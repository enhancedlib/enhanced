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
#include <enhanced/io/ScanStream.h>
#include <enhanced/io/PrintStream.h>

namespace enhanced::io {
    ENHANCED_CORE_API extern const ScanStream& instream;
    ENHANCED_CORE_API extern const PrintStream& outstream;
    ENHANCED_CORE_API extern const PrintStream& errstream;

    ENHANCED_CORE_API void setInStream(const ScanStream& in);
    ENHANCED_CORE_API void setOutStream(const PrintStream& out);
    ENHANCED_CORE_API void setErrStream(const PrintStream& err);
}
