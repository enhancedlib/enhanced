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

#include <enhanced/core/io/iostream.h>

#include <enhanced/core/io/WarpedInputStream.h>
#include <enhanced/core/io/WarpedOutputStream.h>

namespace enhanced::core::io {
    // TODO
    static WarpedInputStream* _instream = null;
    static WarpedOutputStream* _outstream = null;
    static WarpedOutputStream* _errstream = null;

    WarpedInputStream* const& instream = _instream;
    WarpedOutputStream* const& outstream = _outstream;
    WarpedOutputStream* const& errstream = _errstream;

    func setIn(WarpedInputStream* in) -> void {
        instream->flush();
        _instream = in;
    }

    func setOut(WarpedOutputStream* out) -> void {
        outstream->flush();
        _outstream = out;
    }

    func setErr(WarpedOutputStream* err) -> void {
        errstream->flush();
        _errstream = err;
    }
}
