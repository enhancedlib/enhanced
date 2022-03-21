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

#ifndef ENHANCED_BASIC_CORE_EXCEPTION_EXCEPTION_H
#define ENHANCED_BASIC_CORE_EXCEPTION_EXCEPTION_H

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/jump.h"
#include "EnhancedCore/memory.h"
#include "EnhancedCore/process.h"

#include "EnhancedBasic/export.h"

#include "EnhancedBasic/core/String.h"

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
    const char *message;

    uint code;

    char *(*const traceback)(struct ExceptionType *self);
} ExceptionType;

typedef struct ExceptionContextBlock {
    ExceptionType *exception;

    Snapshot snapshot;

    struct ExceptionContextBlock *link;
} ExceptionContextBlock;

ENHANCED_BASIC_API ExceptionType newException(uint exceptionCode, const char *exceptionMessage);

ENHANCED_BASIC_API void exceptionContextBlockStackPush(ExceptionContextBlock *exceptionContextBlock);

ENHANCED_BASIC_API void exceptionContextBlockStackPopup();

ENHANCED_BASIC_API bool exceptionContextBlockStackIsEmpty();

ENHANCED_BASIC_API void exceptionThrow(ExceptionType exception);

#define TRY \
    { \
        ExceptionContextBlock _CONTEXT_BLOCK; \
        exceptionContextBlockStackPush(&_CONTEXT_BLOCK); \
        TryBlockCurrentStatus _TRY_BLOCK_CURRENT_STATUS = takeSnapshot(_CONTEXT_BLOCK.snapshot); \
        bool _IN_FINALLY = false; \
        ExceptionType *_EXCEPTION; \
        if (_TRY_BLOCK_CURRENT_STATUS == TryBlockExceptionOccurred) { \
            _EXCEPTION = _CONTEXT_BLOCK.exception; \
        } \
        if (_TRY_BLOCK_CURRENT_STATUS == TryBlockInto) { \
            _TRY_BLOCK_CURRENT_STATUS = TryBlockNoException;

#define CATCH(exceptionCode, variable) \
        } else if ((exceptionCode) == -1 || \
                   (_TRY_BLOCK_CURRENT_STATUS == TryBlockExceptionOccurred && _EXCEPTION->code == (exceptionCode))) { \
            ExceptionType *(variable) = _EXCEPTION; \
            _TRY_BLOCK_CURRENT_STATUS = TryBlockExceptionCapture;

#define PASS_TRY \
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

namespace EnhancedBasic {
    namespace core {
        namespace exception {
            class ENHANCED_BASIC_API Exception {
            protected:
                const String message;

                const Exception *cause;

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

                explicit Exception(String &&message = "") noexcept;

                explicit Exception(const Exception *cause) noexcept;

                Exception(String &&message, const Exception *cause) noexcept;

                virtual ~Exception() noexcept;

                $RetNotIgnored()
                String traceback() noexcept;

                $RetNotIgnored()
                const Exception *getCause() noexcept;

                $RetNotIgnored()
                const String &getMessage() noexcept;
            };
        } // namespace exception
    } // namespace core
} // namespace EnhancedBasic

#endif // defined(C_LANGUAGE) || defined(ENHANCED_BASIC_C_MODE)

#endif // !ENHANCED_BASIC_CORE_EXCEPTION_EXCEPTION_H
