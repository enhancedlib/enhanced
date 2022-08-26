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

#include "enhanced/basic/exception/Exception.h"

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/jump.h"
#include "enhanced/core/memory.h"

#include <stdio.h>

const ExceptionType Exception = {
    .parent = null,
    .code = 0xFFFFFFFFFFFFFFFF
};

static ExceptionContext* exceptionContextStack = null;

static char* getTraceback(ExceptionInstance* self);

ExceptionInstance newException(const ExceptionType type, const char* const message) {
    ExceptionInstance exception = {
        .message = message,
        .type = type,
        .getTraceback = getTraceback
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

bool exceptionInstanceOf(struct ExceptionInstance* exception, ExceptionType type) {
    if (exception->type.code == type.code || type.code == Exception.code) {
        return true;
    }

    ExceptionType* parent = exception->type.parent;
    while (parent != null) {
        if (parent->code == type.code) {
            return true;
        }
        parent = parent->parent;
    }
    return false;
}

void exceptionThrow(ExceptionInstance exception) {
    if (exceptionContextStackIsEmpty()) {
        fprintf(stderr, "%s\n", exception.getTraceback(&exception));
        processAbnormalAbort();
    } else {
        exceptionContextStack->exception = &exception;
        jumpTo(exceptionContextStack->snapshot, TryBlockExceptionOccurred);
    }
}

char* getTraceback(ExceptionInstance* self) {
    return (char*) self->message;
}
