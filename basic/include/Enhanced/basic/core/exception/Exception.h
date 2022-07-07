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

#pragma once

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"
#include "Enhanced/core/jump.h"
#include "Enhanced/core/memory.h"
#include "Enhanced/core/process.h"

#include "Enhanced/basic/export.h"
#include "Enhanced/basic/core/String.h"

#if defined(C_LANGUAGE) /* C language */ || defined(ENHANCED_BASIC_C_MODE)

EXTERN_C_START

typedef enum TryBlockCurrentStatus {
    TryBlockInto,
    TryBlockNoException,
    TryBlockExceptionOccurred,
    TryBlockExceptionCapture,
    TryBlockBreak,
    TryBlockFunctionReturn
} TryBlockCurrentStatus;

typedef struct ExceptionType {
    const char* message;

    uint code;

    char* (*const traceback)(struct ExceptionType* self);
} ExceptionType;

typedef struct ExceptionContextBlock {
    ExceptionType* exception;

    Snapshot snapshot;

    struct ExceptionContextBlock* link;
} ExceptionContextBlock;

ENHANCED_BASIC_API ExceptionType newException(uint exceptionCode, const char* exceptionMessage);

ENHANCED_BASIC_API void exceptionContextBlockStackPush(ExceptionContextBlock* exceptionContextBlock);

ENHANCED_BASIC_API void exceptionContextBlockStackPopup();

ENHANCED_BASIC_API bool exceptionContextBlockStackIsEmpty();

ENHANCED_BASIC_API void exceptionThrow(ExceptionType exception);

/*
 * // -*- TRY-CATCH-PASSED-END_TRY -*-
 * {
 *     ExceptionContextBlock _CONTEXT_BLOCK;
 *     exceptionContextBlockStackPush(&_CONTEXT_BLOCK);
 *     TryBlockCurrentStatus _TRY_BLOCK_CURRENT_STATUS = takeSnapshot(_CONTEXT_BLOCK.snapshot);
 *     bool _IN_FINALLY = false;
 *     ExceptionType* _EXCEPTION;
 *     if (_TRY_BLOCK_CURRENT_STATUS == TryBlockExceptionOccurred) {
 *         _EXCEPTION = _CONTEXT_BLOCK.exception;
 *     }
 *     if (_TRY_BLOCK_CURRENT_STATUS == TryBlockInto) {
 *         _TRY_BLOCK_CURRENT_STATUS = TryBlockNoException;
 *         // -*- TRY block -*-
 *     } else if ((exceptionCode) == -1 ||
 *                (_TRY_BLOCK_CURRENT_STATUS == TryBlockExceptionOccurred && _EXCEPTION->code == (exceptionCode))) {
 *         ExceptionType* (variable) = _EXCEPTION;
 *         _TRY_BLOCK_CURRENT_STATUS = TryBlockExceptionCapture;
 *         // -*- CATCH block -*-
 *     }
 *     if (_TRY_BLOCK_CURRENT_STATUS == TryBlockNoException) {
 *         // -*- PASSED block -*-
 *     }
 *     _IN_FINALLY = true;
 *     {
 *         // -*- FINALLY block -*-
 *     }
 *     exceptionContextBlockStackPopup();
 *     if (_TRY_BLOCK_CURRENT_STATUS == TryBlockBreak) {
 *         jumpTo(_CONTEXT_BLOCK.snapshot, TryBlockFunctionReturn);
 *     }
 *     if (_TRY_BLOCK_CURRENT_STATUS == TryBlockExceptionOccurred) {
 *         exceptionThrow(*_EXCEPTION);
 *     }
 * }
 *
 * // -*- RETURN_IN_TRY -*-
 * {
 *     if (_IN_FINALLY) {
 *         exceptionContextBlockStackPopup();
 *         return value;
 *     }
 *     Snapshot snapshot;
 *     memoryCopy(snapshot, _CONTEXT_BLOCK.snapshot, sizeof(Snapshot));
 *     if (takeSnapshot(_CONTEXT_BLOCK.snapshot) == TryBlockFunctionReturn) {
 *         return value;
 *     } else {
 *         jumpTo(snapshot, TryBlockBreak);
 *     }
 * }
 */

// The macro definitions here is not indented to support IDE auto-indentation.

#define TRY \
{ \
ExceptionContextBlock _CONTEXT_BLOCK; \
exceptionContextBlockStackPush(&_CONTEXT_BLOCK); \
TryBlockCurrentStatus _TRY_BLOCK_CURRENT_STATUS = takeSnapshot(_CONTEXT_BLOCK.snapshot); \
bool _IN_FINALLY = false; \
ExceptionType* _EXCEPTION; \
if (_TRY_BLOCK_CURRENT_STATUS == TryBlockExceptionOccurred) { \
_EXCEPTION = _CONTEXT_BLOCK.exception; \
} \
if (_TRY_BLOCK_CURRENT_STATUS == TryBlockInto) { \
_TRY_BLOCK_CURRENT_STATUS = TryBlockNoException;

#define CATCH(exceptionCode, variable) \
} else if ((exceptionCode) == -1 || (_TRY_BLOCK_CURRENT_STATUS == TryBlockExceptionOccurred && _EXCEPTION->code == (exceptionCode))) { \
ExceptionType* (variable) = _EXCEPTION; \
_TRY_BLOCK_CURRENT_STATUS = TryBlockExceptionCapture;

#define PASSED \
} \
if (_TRY_BLOCK_CURRENT_STATUS == TryBlockNoException) {

#define FINALLY \
} \
_IN_FINALLY = true; \
{

#define END_TRY \
} \
exceptionContextBlockStackPopup(); \
if (_TRY_BLOCK_CURRENT_STATUS == TryBlockBreak) { \
jumpTo(_CONTEXT_BLOCK.snapshot, TryBlockFunctionReturn); \
} \
if (_TRY_BLOCK_CURRENT_STATUS == TryBlockExceptionOccurred) { \
exceptionThrow(*_EXCEPTION); \
} \
} (void) 0

#define RETURN_IN_TRY(value) \
{ \
if (_IN_FINALLY) { \
exceptionContextBlockStackPopup(); \
return value; \
} \
Snapshot snapshot; \
memoryCopy(snapshot, _CONTEXT_BLOCK.snapshot, sizeof(Snapshot)); \
if (takeSnapshot(_CONTEXT_BLOCK.snapshot) == TryBlockFunctionReturn) { \
return value; \
} else { \
jumpTo(snapshot, TryBlockBreak); \
} \
} (void) 0

#define THROW exceptionThrow

EXTERN_C_END

#else // C++ language

namespace Enhanced::basic::core::exception {
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
         * Set whether to enable exceptions traceback of this library.
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

        RetNotIgnored()
        String traceback() noexcept;

        RetNotIgnored()
        const Exception* getCause() noexcept;

        RetNotIgnored()
        const String& getMessage() noexcept;
    };
}

#endif // defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)
