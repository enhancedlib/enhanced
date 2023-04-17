/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
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
