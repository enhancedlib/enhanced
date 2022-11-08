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

#pragma once

#include <enhanced/core/defines.h>
#include <enhanced/core/export.h>
#include <enhanced/core/types.h>
#include <enhanced/core/jump.h>
#include <enhanced/core/memory.h>
#include <enhanced/core/process.h>
#include <enhanced/core/String.h>

/*!
 * Set whether to enable exceptions of this library.
 * Default value: true
 */
ENHANCED_CORE_API extern bool enableExceptions;

/*!
 * Set whether to enable exceptions getTraceback of this library.
 * Default value: true
 */
ENHANCED_CORE_API extern bool enableExceptionsTraceback;

typedef struct CExceptionType {
    struct CExceptionType* parent;
    uint64 code;
} CExceptionType;

typedef struct CExceptionInstance {
    const char* message;
    CExceptionType type;

    char* (*const getTraceback)(struct CExceptionInstance* self);
} CExceptionInstance;

typedef enum CTryBlockStatus {
    TryBlockInto,
    TryBlockNoException,
    TryBlockExceptionOccurred,
    TryBlockExceptionCapture,
    TryBlockInterrupted,
    TryBlockFunctionReturn
} CTryBlockStatus;

typedef struct CExceptionContext {
    CExceptionInstance* exception;
    Snapshot snapshot;
    bool inFinally;
    CTryBlockStatus status;
    struct CExceptionContext* link;
} CExceptionContext;

ENHANCED_CORE_API extern const CExceptionType CException;

ENHANCED_CORE_API CExceptionInstance newException(CExceptionType type, const char* message);

ENHANCED_CORE_API void exceptionContextStackPush(CExceptionContext* exceptionContext);

ENHANCED_CORE_API void exceptionContextStackPopup();

ENHANCED_CORE_API bool exceptionContextStackIsEmpty();

ENHANCED_CORE_API bool exceptionInstanceOf(CExceptionInstance* exception, CExceptionType type);

ENHANCED_CORE_API void exceptionThrow(CExceptionInstance exception);

#define C_TRY \
    { \
        CExceptionContext _CONTEXT; \
        exceptionContextStackPush(&_CONTEXT); \
        _CONTEXT.status = TAKE_SNAPSHOT(_CONTEXT.snapshot); \
        if (_CONTEXT.status == TryBlockInto) { \
            _CONTEXT.status = TryBlockNoException;

#define C_CATCH(exceptionType, variable) \
        } else if (_CONTEXT.status == TryBlockExceptionOccurred && exceptionInstanceOf(_CONTEXT.exception, (exceptionType))) { \
            CExceptionInstance* (variable) = _CONTEXT.exception; \
            _CONTEXT.status = TryBlockExceptionCapture;

#define C_PASSED \
        } \
        if (_CONTEXT.status == TryBlockNoException) {

#define C_FINALLY \
        } \
        _CONTEXT.inFinally = true; \
        {

#define C_END_TRY \
        } \
            exceptionContextStackPopup(); \
            if (_CONTEXT.status == TryBlockInterrupted) { \
                JUMP_TO(_CONTEXT.snapshot, TryBlockFunctionReturn); \
            } \
            if (_CONTEXT.status == TryBlockExceptionOccurred) { \
                exceptionThrow(*_CONTEXT.exception); \
            } \
    } \
    (void) 0

#define C_RETURN_IN_TRY(value) \
    { \
        if (_CONTEXT.inFinally) { \
            exceptionContextStackPopup(); \
            return value; \
        } \
        Snapshot snapshot; \
        memoryCopy(snapshot, _CONTEXT.snapshot, sizeof(Snapshot)); \
        if (TAKE_SNAPSHOT(_CONTEXT.snapshot) == TryBlockFunctionReturn) { \
            return value; \
        } else { \
            JUMP_TO(snapshot, TryBlockInterrupted); \
        } \
    } \
    (void) 0

#define C_THROW exceptionThrow

#define C_THROW_NEW(type, message) exceptionThrow(newException(type, message))

#ifdef CXX_LANGUAGE

NAMESPACE_L3_BEGIN(enhanced, core, exception)

class ENHANCED_CORE_API Exception {
protected:
    const String message;

    const Exception* cause;

public:
    explicit Exception(const String& message = "") noexcept;

    explicit Exception(const Exception* cause) noexcept;

    Exception(const String&, const Exception* cause) noexcept;

    virtual ~Exception() noexcept;

    NoIgnoreRet
    virtual const String& getTraceback() const noexcept;

    NoIgnoreRet
    virtual const Exception* getCause() const noexcept;

    NoIgnoreRet
    virtual const String& getMessage() const noexcept;
};

NAMESPACE_L3_END

#endif
