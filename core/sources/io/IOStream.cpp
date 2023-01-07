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

#include <enhanced/io/IOStream.h>

#include <enhanced/io/ScanStream.h>
#include <enhanced/io/PrintStream.h>

namespace enhanced::io {
    // TODO: Implementes I/O streams
    static ScanStream* _instream = nullptr;
    static PrintStream* _outstream = nullptr;
    static PrintStream* _errstream = nullptr;

    const ScanStream& instream = *_instream;
    const PrintStream& outstream = *_outstream;
    const PrintStream& errstream = *_errstream;

    void setInStream(const ScanStream& in) {
        instream.flush();
        *_instream = in;
    }

    void setOutStream(const PrintStream& out) {
        outstream.flush();
        *_outstream = out;
    }

    void setErrStream(const PrintStream& err) {
        errstream.flush();
        *_errstream = err;
    }
}
