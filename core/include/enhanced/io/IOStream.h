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
#include <enhanced/io/ScanStream.h>
#include <enhanced/io/PrintStream.h>

namespace enhanced::io {
    ENHANCED_CORE_API extern ScanStream* const& instream;
    ENHANCED_CORE_API extern PrintStream* const& outstream;
    ENHANCED_CORE_API extern PrintStream* const& errstream;

    ENHANCED_CORE_API func setInStream(ScanStream* in) -> void;
    ENHANCED_CORE_API func setOutStream(PrintStream* out) -> void;
    ENHANCED_CORE_API func setErrStream(PrintStream* err) -> void;
}