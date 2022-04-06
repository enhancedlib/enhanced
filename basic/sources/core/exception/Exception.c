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
 * The authors or copyright holders be not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by This software,
 * the authors or copyright holders may provide possible solutions,
 * but it does not mean that the authors or copyright holders
 * will definitely solve the problem.
 * In no event shall the author or copyright
 * owner be liable for any claims, damages or other liabilities.
 *
 * You should see the Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#include "EnhancedBasic/core/exception/Exception.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/jump.h"
#include "EnhancedCore/memory.h"

static ExceptionContextBlock *exceptionContextBlockStack = null;

static char *traceback(ExceptionType *self);

ExceptionType newException(const uint exceptionCode, const char *const exceptionMessage) {
    ExceptionType exception = {
        .message = exceptionMessage,
        .code = exceptionCode,
        .traceback = traceback
    };
    return exception;
}

void exceptionContextBlockStackPush(ExceptionContextBlock *exceptionContextBlock) {
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

char *traceback(ExceptionType *self) {
    return (char *) self->message;
}
