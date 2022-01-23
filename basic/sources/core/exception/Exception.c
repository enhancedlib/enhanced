/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
 *
 * This copyright disclaimer is subject to change without notice.
 *
 * This software is a free software,
 * everyone can change, copy, publication, demonstrate, use, etc.
 *
 * If you change and publication this software,
 * must credit the original software source and author's name,
 * and include this copyright disclaimer and
 * the license of this software in your software.
 *
 * This software and documentation may provide
 * third-party content, product and other information.
 * I am not responsible for any loss or damage caused
 * by your access to or use of third-party content, products, etc.
 */

#include <stdlib.h>

#include "EnhancedBasic/core/exception/Exception.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/jump.h"

using(EnhancedBasic$core$exception$Exception);
using(EnhancedBasic$core$exception$ExceptionContextBlock);

static ExceptionContextBlock *exceptionContextBlockStack = null;

static char *traceback(Exception *self);

void exceptionContextBlockStackPush(ExceptionContextBlock *exceptionContextBlock) {
    exceptionContextBlock->link = exceptionContextBlockStack;
    exceptionContextBlockStack = exceptionContextBlock;
}

void exceptionContextBlockStackPopup() {
    exceptionContextBlockStack = exceptionContextBlockStack->link;
}

bool exceptionContextBlockStackIsEmpty() {
    return exceptionContextBlockStack == null;
}

void exceptionRaise(uint exceptionCode, const char *exceptionMessage) {
    Exception exception = {
        exceptionMessage,
        exceptionCode,
        traceback
    };

    if (exceptionContextBlockStackIsEmpty()) {
        terminate();
    } else {
        exceptionContextBlockStack->exception = &exception;
        jumpTo(exceptionContextBlockStack->snapshot, TRY_BLOCK_EXCEPTION_OCCURRED);
    }
}

char *traceback(Exception *self) {
    return "";
}
