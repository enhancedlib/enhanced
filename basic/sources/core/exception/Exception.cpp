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

#include "Enhanced/basic/core/exception/Exception.h"

#include "Enhanced/core/defines.h"
#include "Enhanced/core/types.h"

#include "Enhanced/basic/core/String.h"

using Enhanced::basic::core::exception::Exception;
using Enhanced::basic::core::String;

bool Exception::enableExceptions = true;
bool Exception::enableExceptionsTraceback = true;

Exception::Exception(String&& message) noexcept: message(message), cause(null) {
}

Exception::Exception(const Exception* cause) noexcept: message(""), cause(cause) {
}

Exception::Exception(String&& message, const Exception* cause) noexcept: message(message), cause(cause) {
}

Exception::~Exception() noexcept = default;

String Exception::traceback() noexcept {
    return (String) message;
}

const Exception* Exception::getCause() noexcept {
    return cause;
}

const String& Exception::getMessage() noexcept {
    return message;
}
