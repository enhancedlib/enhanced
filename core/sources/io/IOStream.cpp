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

#include <enhanced/io/IOStream.h>

#include <enhanced/io/ScanStream.h>
#include <enhanced/io/PrintStream.h>

namespace enhanced::io {
    // TODO: Implementes I/O streams
    static ScanStream* _instream = nullptr;
    static PrintStream* _outstream = nullptr;
    static PrintStream* _errstream = nullptr;

    ScanStream* const& instream = _instream;
    PrintStream* const& outstream = _outstream;
    PrintStream* const& errstream = _errstream;

    void setInStream(ScanStream* in) {
        instream->flush();
        _instream = in;
    }

    void setOutStream(PrintStream* out) {
        outstream->flush();
        _outstream = out;
    }

    void setErrStream(PrintStream* err) {
        errstream->flush();
        _errstream = err;
    }
}
