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

#if defined(C_LANGUAGE) /* C language */ || defined(ENHANCED_BASIC_C_MODE)

EXTERN_C_START

typedef enum EnhancedBasic$core$exception$TRY_BLOCKTRY_BLOCK_CURRENT_STATUS {
    TRY_BLOCK_INTO,
    TRY_BLOCK_NO_EXCEPTION_OCCURRED,
    TRY_BLOCK_EXCEPTION_OCCURRED,
    TRY_BLOCK_EXCEPTION_CAPTURE,
    TRY_BLOCK_BREAK,
    TRY_BLOCK_FUNCTION_RETURN
} EnhancedBasic$core$exception$TRY_BLOCKTRY_BLOCK_CURRENT_STATUS;

#define ALIAS_EnhancedBasic$core$exception$TRY_BLOCKTRY_BLOCK_CURRENT_STATUS TRY_BLOCKTRY_BLOCK_CURRENT_STATUS

typedef struct EnhancedBasic$core$exception$Exception {
    const char *message;

    uint code;

    char *(*traceback)(struct EnhancedBasic$core$exception$Exception *self);
} EnhancedBasic$core$exception$Exception;

#define ALIAS_EnhancedBasic$core$exception$Exception Exception

typedef struct EnhancedBasic$core$exception$ExceptionContextBlock {
    EnhancedBasic$core$exception$Exception *exception;

    Snapshot snapshot;

    struct EnhancedBasic$core$exception$ExceptionContextBlock *link;
} EnhancedBasic$core$exception$ExceptionContextBlock;

#define ALIAS_EnhancedBasic$core$exception$ExceptionContextBlock ExceptionContextBlock

ENHANCED_BASIC_API void exceptionContextBlockStackPush(
    EnhancedBasic$core$exception$ExceptionContextBlock *exceptionContextBlock);

ENHANCED_BASIC_API void exceptionContextBlockStackPopup();

ENHANCED_BASIC_API bool exceptionContextBlockStackIsEmpty();

ENHANCED_BASIC_API void exceptionRaise(uint exceptionCode, const char *exceptionMessage);

#ifdef COMPILER_MSVC
#pragma warning(disable: 4003)
#endif // COMPILER_MSVC

#define TRY \
    { \
        EnhancedBasic$core$exception$ExceptionContextBlock CONTEXT_BLOCK; \
        exceptionContextBlockStackPush(&CONTEXT_BLOCK); \
        EnhancedBasic$core$exception$TRY_BLOCKTRY_BLOCK_CURRENT_STATUS \
            TRY_BLOCK_CURRENT_STATUS = takeSnapshot(CONTEXT_BLOCK.snapshot); \
        bool _IN_FINALLY = false; \
        if (TRY_BLOCK_CURRENT_STATUS == TRY_BLOCK_INTO) { \
            TRY_BLOCK_CURRENT_STATUS = TRY_BLOCK_NO_EXCEPTION_OCCURRED;

#define CATCH(exceptionCode, variable) \
        } else if (TRY_BLOCK_CURRENT_STATUS == TRY_BLOCK_EXCEPTION_OCCURRED && \
            CONTEXT_BLOCK.exception->code == (exceptionCode)) { \
            EnhancedBasic$core$exception$Exception *(variable) = CONTEXT_BLOCK.exception; \
            TRY_BLOCK_CURRENT_STATUS = TRY_BLOCK_EXCEPTION_CAPTURE;

#define PASS \
        } \
        if (TRY_BLOCK_CURRENT_STATUS == TRY_BLOCK_NO_EXCEPTION_OCCURRED) {

#define FINALLY \
        } \
        _IN_FINALLY = true; \
        {

#define END_TRY \
        } \
        exceptionContextBlockStackPopup(); \
        if (TRY_BLOCK_CURRENT_STATUS == TRY_BLOCK_BREAK) { \
            jumpTo(CONTEXT_BLOCK.snapshot, TRY_BLOCK_FUNCTION_RETURN); \
        } \
        if (TRY_BLOCK_CURRENT_STATUS == TRY_BLOCK_EXCEPTION_OCCURRED && \
            exceptionContextBlockStackIsEmpty()) { \
            terminate(); \
        } \
    } (void) 0

#define RETURN_IN_TRY(value) \
    { \
        if (_IN_FINALLY) { \
            exceptionContextBlockStackPopup(); \
            return value; \
        } \
        Snapshot snapshot; \
        memoryCopy(snapshot, CONTEXT_BLOCK.snapshot, sizeof(Snapshot)); \
        if (takeSnapshot(CONTEXT_BLOCK.snapshot) == TRY_BLOCK_FUNCTION_RETURN) { \
            return value; \
        } else { \
            jumpTo(snapshot, TRY_BLOCK_BREAK); \
        } \
    } (void) 0

#define RAISE exceptionRaise

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
                 * default elements: true
                 */
                static bool enableExceptions;

                /*!
                 * Set whether to enable exceptions traceback of this library.
                 *
                 * true: Enable
                 * false: Disable
                 *
                 * default elements: true
                 */
                static bool enableExceptionsTraceback;

                explicit Exception(const String &message = "") noexcept;

                explicit Exception(const Exception *cause) noexcept;

                Exception(const String &message, const Exception *cause) noexcept;

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
