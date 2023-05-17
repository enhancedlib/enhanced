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

#include <cstdlib>

#include <enhanced/Process.h>

namespace enhanced {
    E_ANNOTATE(NoReturn)
    void processExit(int status) {
        std::exit(status);
    }

    E_ANNOTATE(NoReturn)
    void processAbort() {
        std::abort();
    }
}
