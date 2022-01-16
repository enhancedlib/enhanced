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

#include <stdlib.h>

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"
#include "EnhancedCore/jump.h"
#include "EnhancedCore/memory.h"

#include "EnhancedBasic/export.h"

#include "EnhancedBasic/core/String.h"

#if defined(C_LANGUAGE) /* C language */ || defined(ENHANCED_BASIC_C_MODE)

EXTERN_C_START

typedef enum EnhancedBasic$core$exception$TRY_BLOCK_STATUS {
    TRY_BLOCK_INTO,
    TRY_BLOCK_NO_EXCEPTION_OCCURRED,
    TRY_BLOCK_EXCEPTION_OCCURRED,
    TRY_BLOCK_EXCEPTION_CAPTURE,
    TRY_BLOCK_BREAK,
    TRY_BLOCK_FUNCTION_RETURN
} EnhancedBasic$core$exception$TRY_BLOCK_STATUS;
#define ALIAS_EnhancedBasic$core$exception$TRY_BLOCK_STATUS TRY_BLOCK_STATUS

typedef struct EnhancedBasic$core$exception$Exception {
    const char *message;

    unsigned int code;

    char *(*traceback)(struct EnhancedBasic$core$exception$Exception *self);
} EnhancedBasic$core$exception$Exception;
#define ALIAS_EnhancedBasic$core$exception$Exception Exception

typedef struct EnhancedBasic$core$exception$ExceptionContextBlock {
    EnhancedBasic$core$exception$Exception *exception;

    JumpBuffer jumpBuffer;

    struct EnhancedBasic$core$exception$ExceptionContextBlock *link;
} EnhancedBasic$core$exception$ExceptionContextBlock;
#define ALIAS_EnhancedBasic$core$exception$ExceptionContextBlock ExceptionContextBlock

ENHANCED_BASIC_API void exceptionContextBlockStackPush(
    EnhancedBasic$core$exception$ExceptionContextBlock *exceptionContextBlock);

ENHANCED_BASIC_API void exceptionContextBlockStackPopup();

ENHANCED_BASIC_API bool exceptionContextBlockStackIsEmpty();

ENHANCED_BASIC_API void exceptionRaise(unsigned int exceptionCode, const char *exceptionMessage);

#define TRY \
    { \
        EnhancedBasic$core$exception$ExceptionContextBlock _CONTEXT_BLOCK; \
        bool _IN_FINALLY = false; \
        exceptionContextBlockStackPush(&_CONTEXT_BLOCK); \
        EnhancedBasic$core$exception$TRY_BLOCK_STATUS _STATUS = jumpSet(_CONTEXT_BLOCK.jumpBuffer); \
        if (_STATUS == TRY_BLOCK_INTO) { \
            _STATUS = TRY_BLOCK_NO_EXCEPTION_OCCURRED;

#define CATCH(exceptionCode, variable) \
        } else if (_STATUS == TRY_BLOCK_EXCEPTION_OCCURRED && \
            _CONTEXT_BLOCK.exception->code == (exceptionCode)) { \
            EnhancedBasic$core$exception$Exception *(variable) = _CONTEXT_BLOCK.exception; \
            _STATUS = TRY_BLOCK_EXCEPTION_CAPTURE;

#define PASS \
        } \
        if (_STATUS == TRY_BLOCK_NO_EXCEPTION_OCCURRED) {

#define FINALLY \
        } \
        _IN_FINALLY = true; \
        {

#define END_TRY \
        } \
        exceptionContextBlockStackPopup(); \
        if (_STATUS == TRY_BLOCK_BREAK) { \
            jumpTo(_CONTEXT_BLOCK.jumpBuffer, TRY_BLOCK_FUNCTION_RETURN); \
        } \
        if (_STATUS == TRY_BLOCK_EXCEPTION_OCCURRED && \
            exceptionContextBlockStackIsEmpty()) { \
            abort(); \
        } \
    } (void) 0

#define RETURN_IN_TRY(value) \
    { \
        if (_IN_FINALLY) { \
            exceptionContextBlockStackPopup(); \
            return value; \
        } \
        JumpBuffer jumpBuffer; \
        memoryCopy(jumpBuffer, _CONTEXT_BLOCK.jumpBuffer, sizeof(JumpBuffer)); \
        if (jumpSet(_CONTEXT_BLOCK.jumpBuffer) == TRY_BLOCK_FUNCTION_RETURN) { \
            return value; \
        } else { \
            jumpTo(jumpBuffer, TRY_BLOCK_BREAK); \
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
