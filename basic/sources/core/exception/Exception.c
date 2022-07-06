/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright notice is subject to change without notice.
 *
 * This software is a free software, everyone can change,
 * copy, publication, demonstrate, use, etc.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#include "Enhanced/basic/core/exception/Exception.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/jump.h"
#include "Enhanced/core/memory.h"

static ExceptionContextBlock* exceptionContextBlockStack = null;

static char* traceback(ExceptionType* self);

ExceptionType newException(const uint exceptionCode, const char* const exceptionMessage) {
    ExceptionType exception = {
        .message = exceptionMessage,
        .code = exceptionCode,
        .traceback = traceback
    };
    return exception;
}

void exceptionContextBlockStackPush(ExceptionContextBlock* exceptionContextBlock) {
    exceptionContextBlock->exception = null;
    exceptionContextBlock->link = exceptionContextBlockStack;
    exceptionContextBlockStack = exceptionContextBlock;
}

void exceptionContextBlockStackPopup() {
    exceptionContextBlockStack = exceptionContextBlockStack->link;
}

bool exceptionContextBlockStackIsEmpty() {
    return exceptionContextBlockStack == null;
}

void exceptionThrow(ExceptionType exception) {
    if (exceptionContextBlockStackIsEmpty()) {
        processAbnormalAbort();
    } else {
        exceptionContextBlockStack->exception = &exception;
        jumpTo(exceptionContextBlockStack->snapshot, TryBlockExceptionOccurred);
    }
}

char* traceback(ExceptionType* self) {
    return (char*) self->message;
}
