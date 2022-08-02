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
 */

#pragma once

#include "enhanced/core/defines.h"
#include "enhanced/core/types.h"
#include "enhanced/core/jump.h"
#include "enhanced/core/memory.h"
#include "enhanced/core/process.h"

#include "enhanced/basic/export.h"
#include "enhanced/basic/String.h"

#if defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)

EXTERN_C_START

typedef struct ExceptionType {
    const char* message;
    uint code;
    char* (*const getTraceback)(struct ExceptionType* self);
} ExceptionType;

typedef enum TryBlockCurrentStatus {
    TryBlockInto,
    TryBlockNoException,
    TryBlockExceptionOccurred,
    TryBlockExceptionCapture,
    TryBlockBreak,
    TryBlockFunctionReturn
} TryBlockCurrentStatus;

typedef struct ExceptionContext {
    ExceptionType* exception;
    Snapshot snapshot;
    bool inFinally;
    TryBlockCurrentStatus status;
    struct ExceptionContext* link;
} ExceptionContext;

ENHANCED_BASIC_API ExceptionType newException(uint exceptionCode, const char* exceptionMessage);

ENHANCED_BASIC_API void exceptionContextStackPush(ExceptionContext* exceptionContext);

ENHANCED_BASIC_API void exceptionContextStackPopup();

ENHANCED_BASIC_API bool exceptionContextStackIsEmpty();

ENHANCED_BASIC_API void exceptionThrow(ExceptionType exception);

/*
 * // -*- TRY-CATCH-PASSED-END_TRY -*-
 * {
 *     ExceptionContext _CONTEXT;
 *     exceptionContextStackPush(&_CONTEXT);
 *     _CONTEXT.status = takeSnapshot(_CONTEXT.snapshot);
 *     if (_CONTEXT.status == TryBlockExceptionOccurred) {
 *     }
 *     if (_CONTEXT.status == TryBlockInto) {
 *         _CONTEXT.status = TryBlockNoException;
 *         // -*- TRY block -*-
 *     } else if ((exceptionCode) == -1 || (_CONTEXT.status == TryBlockExceptionOccurred && _CONTEXT.exception->code == (exceptionCode))) {
 *         ExceptionType* (variable) = _CONTEXT.exception;
 *         _CONTEXT.status = TryBlockExceptionCapture;
 *         // -*- CATCH block -*-
 *     }
 *     if (_CONTEXT.status == TryBlockNoException) {
 *         // -*- PASSED block -*-
 *     }
 *     _CONTEXT.inFinally = true;
 *     {
 *         // -*- FINALLY block -*-
 *     }
 *     exceptionContextStackPopup();
 *     if (_CONTEXT.status == TryBlockBreak) {
 *         jumpTo(_CONTEXT.snapshot, TryBlockFunctionReturn);
 *     }
 *     if (_CONTEXT.status == TryBlockExceptionOccurred) {
 *         exceptionThrow(*_CONTEXT.exception);
 *     }
 * }
 *
 * // -*- RETURN_IN_TRY -*-
 * {
 *     if (_CONTEXT.inFinally) {
 *         exceptionContextStackPopup();
 *         return value;
 *     }
 *     Snapshot snapshot;
 *     memoryCopy(snapshot, _CONTEXT.snapshot, sizeof(Snapshot));
 *     if (takeSnapshot(_CONTEXT.snapshot) == TryBlockFunctionReturn) {
 *         return value;
 *     } else {
 *         jumpTo(snapshot, TryBlockBreak);
 *     }
 * }
 */

// The macro definitions here is not indented to support IDE auto-indentation.

#define TRY \
{ \
ExceptionContext _CONTEXT; \
exceptionContextStackPush(&_CONTEXT); \
_CONTEXT.status = takeSnapshot(_CONTEXT.snapshot); \
if (_CONTEXT.status == TryBlockExceptionOccurred) { \
} \
if (_CONTEXT.status == TryBlockInto) { \
_CONTEXT.status = TryBlockNoException;

#define CATCH(exceptionCode, variable) \
} else if ((exceptionCode) == -1 || (_CONTEXT.status == TryBlockExceptionOccurred && _CONTEXT.exception->code == (exceptionCode))) { \
ExceptionType* (variable) = _CONTEXT.exception; \
_CONTEXT.status = TryBlockExceptionCapture;

#define PASSED \
} \
if (_CONTEXT.status == TryBlockNoException) {

#define FINALLY \
} \
_CONTEXT.inFinally = true; \
{

#define END_TRY \
} \
exceptionContextStackPopup(); \
if (_CONTEXT.status == TryBlockBreak) { \
jumpTo(_CONTEXT.snapshot, TryBlockFunctionReturn); \
} \
if (_CONTEXT.status == TryBlockExceptionOccurred) { \
exceptionThrow(*_CONTEXT.exception); \
} \
} (void) 0

#define RETURN_IN_TRY(value) \
{ \
if (_CONTEXT.inFinally) { \
exceptionContextStackPopup(); \
return value; \
} \
Snapshot snapshot; \
memoryCopy(snapshot, _CONTEXT.snapshot, sizeof(Snapshot)); \
if (takeSnapshot(_CONTEXT.snapshot) == TryBlockFunctionReturn) { \
return value; \
} else { \
jumpTo(snapshot, TryBlockBreak); \
} \
} (void) 0

#define THROW exceptionThrow

EXTERN_C_END

#else

namespace enhanced::basic::exception {
    class ENHANCED_BASIC_API Exception {
    protected:
        const String message;

        const Exception* cause;

    public:
        /*!
         * Set whether to enable exceptions of this library.
         *
         * true: Enable
         * false: Disable
         *
         * Default value: true
         */
        static bool enableExceptions;

        /*!
         * Set whether to enable exceptions getTraceback of this library.
         *
         * true: Enable
         * false: Disable
         *
         * Default value: true
         */
        static bool enableExceptionsTraceback;

        explicit Exception(String&& message = "") noexcept;

        explicit Exception(const Exception* cause) noexcept;

        Exception(String&& message, const Exception* cause) noexcept;

        virtual ~Exception() noexcept;

        RetCannotIgnored
        const String& getTraceback() const noexcept;

        RetCannotIgnored
        const Exception* getCause() const noexcept;

        RetCannotIgnored
        const String& getMessage() const noexcept;
    };
}

#endif // defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)
