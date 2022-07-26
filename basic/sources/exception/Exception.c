/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 */

#include "enhanced/basic/exception/Exception.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/jump.h"
#include "enhanced/core/memory.h"

#include <stdio.h>

static ExceptionContext* exceptionContextStack = null;

static char* traceback(ExceptionType* self);

ExceptionType newException(const uint exceptionCode, const char* const exceptionMessage) {
    ExceptionType exception = {
        .message = exceptionMessage,
        .code = exceptionCode,
        .traceback = traceback
    };
    return exception;
}

void exceptionContextStackPush(ExceptionContext* exceptionContext) {
    exceptionContext->exception = null;
    exceptionContext->inFinally = false;
    exceptionContext->link = exceptionContextStack;
    exceptionContextStack = exceptionContext;
}

void exceptionContextStackPopup() {
    exceptionContextStack = exceptionContextStack->link;
}

bool exceptionContextStackIsEmpty() {
    return exceptionContextStack == null;
}

void exceptionThrow(ExceptionType exception) {
    if (exceptionContextStackIsEmpty()) {
        fprintf(stderr, exception.traceback(&exception));
        processAbnormalAbort();
    } else {
        exceptionContextStack->exception = &exception;
        jumpTo(exceptionContextStack->snapshot, TryBlockExceptionOccurred);
    }
}

char* traceback(ExceptionType* self) {
    return (char*) self->message;
}
