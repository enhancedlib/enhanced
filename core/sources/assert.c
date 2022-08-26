/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#include <stdlib.h>
#include <stdio.h>

#include "enhanced/core/assert.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/string.h"
#include "enhanced/core/process.h"

void assertionFailed(const char* const message, const char* const file, const uint line) {
    printf("Failed to assert: %s, file \"%s\", line %d", message, file, line);
    processAbnormalAbort();
}
