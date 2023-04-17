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

#include <enhanced/io/PrintStream.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/String.h>
#include <enhanced/exceptions/NotImplementedError.h>

namespace enhanced::io {
    void PrintStream::println() const {
        E_NOT_IMPLEMENTED();
    }

    void PrintStream::printf(const String& message, ...) const {
        E_NOT_IMPLEMENTED();
    }

    void PrintStream::close() const {
        E_NOT_IMPLEMENTED();
    }

    void PrintStream::flush() const {
        E_NOT_IMPLEMENTED();
    }
}
