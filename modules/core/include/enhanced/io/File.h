/*
 * This file is part of Enhanced Framework.
 *
 * Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
 *
 * Permission is hereby granted, to any person obtaining a copy of this software
 * and associated documentation files (the "Software"), to deal in the Software,
 * including without limitation the rights to use, copy, modify, merge,
 * distribute. Unless you have obtained permission from the copyright holders,
 * subject to the following restrictions:
 *
 * 1. The above copyright notice and this permission notice shall be included in
 *    all copies of the Software and modified versions.
 *
 * 2. You may not misrepresent the source of the Software, and you may not claim
 *    that you wrote the original version.
 *
 * 3. You may not misrepresent the modified version as the original version.
 *
 * 4. You may not charge any fees or receive other compensation for the
 *    distribution of the Software, excluding distribution of modified versions
 *    and products using the Software.
 *
 * 5. If you use this Software in your product, you shall indicate it.
 *
 * 6. Neither the name of the author nor the names of its contributors may
 *    be used to endorse or promote products derived from the Software
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
#include <enhanced/Warnings.h>
#include <enhanced/String.h>
#include <enhanced/collections/ArrayList.h>
#include <enhanced/io/FileInputStream.h>
#include <enhanced/io/FileOutputStream.h>
#include <enhanced/io/FileReader.h>
#include <enhanced/io/FileWriter.h>

#define E_EOF (-1)

namespace enhanced::io {
    class E_API(core) File {
        E_CLASS(File)

    E_CLASS_BODY
    	File(const String& path);

        File(const File& file);

        File(File&& file) noexcept;

        E_RET_NO_DISCARD()
        String getFilename() const;

        E_RET_NO_DISCARD()
        String getExtension() const;

        E_RET_NO_DISCARD()
        const String& getPath() const;

        E_RET_NO_DISCARD()
        bool isExist() const;

        E_RET_NO_DISCARD()
        bool isReadOnly() const;

        E_RET_NO_DISCARD()
        bool isFile() const;

        E_RET_NO_DISCARD()
        bool isDirectory() const;

        E_RET_NO_DISCARD()
        bool isSymlink() const;

        void create() const;

        bool createIf() const; E_CTIDY_NOLINT(modernize-use-nodiscard)

        void remove() const;

        bool removeIf() const; E_CTIDY_NOLINT(modernize-use-nodiscard)

        E_RET_NO_DISCARD()
        collections::ArrayList<String> splitPath() const;

        E_RET_NO_DISCARD()
        FileInputStream inStream() const;

        E_RET_NO_DISCARD()
        FileOutputStream outStream() const;

        E_RET_NO_DISCARD()
        FileReader reader() const;

        E_RET_NO_DISCARD()
        FileWriter writer() const;
    };
}
