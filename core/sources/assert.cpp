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

#include <enhanced/Assert.h>

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Process.h>
#include <enhanced/String.h>
#include <enhanced/io/IOStream.h>

using enhanced::String;
using enhanced::processAbort;
using enhanced::io::errstream;

namespace enhancedInternal {
    $NoReturn
    func assertionFailedImpl(const String& message, const String& file, sizetype line) -> void {
        errstream->printf("Failed to assert: {}, at {}:{}", message.getChars(), message.getChars(), line);
        processAbort();
    }
}
