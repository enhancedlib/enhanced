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
#include <enhanced/io/ScanStream.h>
#include <enhanced/io/PrintStream.h>

namespace enhanced::io {
    E_CORE_API extern const ScanStream& ein;
    E_CORE_API extern const PrintStream& eout;
    E_CORE_API extern const PrintStream& eerr;

    E_CORE_API void setIn(const ScanStream& in);
    E_CORE_API void setOut(const PrintStream& out);
    E_CORE_API void setErr(const PrintStream& err);
}
