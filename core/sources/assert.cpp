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

#include <stdio.h>

#include <enhanced/core/assert.h>

#include <enhanced/core/defines.h>
#include <enhanced/core/types.h>
#include <enhanced/core/process.h>
#include <enhanced/core/String.h>

namespace enhanced::core {
    $(NoReturn)
    func assertionFailedImpl(const String& message, const String& file, sizetype line) -> void {
        fprintf(stderr, "Failed to assert: %s, file \"%s\", line %llu", message.getChars(), file.getChars(), line);
        processAbort();
    }
}
