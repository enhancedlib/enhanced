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

#include <enhanced/io/IOStream.h>

#include <enhanced/io/ScanStream.h>
#include <enhanced/io/PrintStream.h>

namespace enhanced::io {
    // TODO: Implementes I/O streams
    static ScanStream* _ein = nullptr;
    static PrintStream* _eout = nullptr;
    static PrintStream* _eerr = nullptr;

    const ScanStream& ein = *_ein;
    const PrintStream& eout = *_eout;
    const PrintStream& eerr = *_eerr;

    void setIn(const ScanStream& in) {
        ein.flush();
        *_ein = in;
    }

    void setOut(const PrintStream& out) {
        eout.flush();
        *_eout = out;
    }

    void setErr(const PrintStream& err) {
        eerr.flush();
        *_eerr = err;
    }
}
