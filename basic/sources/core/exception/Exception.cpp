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

#include "EnhancedBasic/core/String.h"

using EnhancedBasic::core::exception::Exception;
using EnhancedBasic::core::String;

bool Exception::enableExceptions = true;
bool Exception::enableExceptionsTraceback = true;

Exception::Exception(String &&message) noexcept:
    message(message), cause(null) {
}

Exception::Exception(const Exception *cause) noexcept:
    message(""), cause(cause) {
}

Exception::Exception(String &&message, const Exception *cause) noexcept:
    message(message), cause(cause) {
}

Exception::~Exception() noexcept = default;

String Exception::traceback() noexcept {
    return (String) this->message;
}

const Exception *Exception::getCause() noexcept {
    return this->cause;
}

const String &Exception::getMessage() noexcept {
    return this->message;
}
