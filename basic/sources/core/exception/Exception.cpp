/*
 * Copyright (C) 2021 Liu Baihao.
 * This product is licensed under Enhanced License.
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

#include "EnhancedBasic/core/exception/Exception.h"

#include "EnhancedCore/defines.h"
#include "EnhancedCore/types.h"

#include "EnhancedBasic/core/String.h"

using EnhancedBasic::Core::Exception::Exception;
using EnhancedBasic::Core::String;

bool Exception::enableExceptions = true;
bool Exception::enableExceptionsTraceback = true;

Exception::Exception(const String &message) noexcept:
    message(message), cause(null) {
}

Exception::Exception(const Exception *cause) noexcept:
    message(""), cause(cause) {
}

Exception::Exception(const String &message, const Exception *cause) noexcept:
    message(message), cause(cause) {
}

#ifdef CXX_11_OR_MORE

Exception::~Exception() noexcept = default;

#else

Exception::~Exception() {}

#endif // CXX_11_OR_MORE

const Exception *Exception::getCause() noexcept {
    return this->cause;
}

const String &Exception::getMessage() noexcept {
    return this->message;
}
