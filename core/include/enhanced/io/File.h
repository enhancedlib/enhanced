/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced Software License.
 *
 * This file is part of the Enhanced Software, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 *
 * You may not use this file except in compliance with the License.
 * You should obtain a copy of the License in the distribution,
 * if not, see <https://sharedwonder.github.io/enhanced/LICENSE.txt>
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

namespace enhanced::io {
    class File {
    public:
    	File(const String& path);

        File(const File& file);

        File(File&& file) noexcept;

        $NoIgnoreReturn
        MutString getFilename() const;

        $NoIgnoreReturn
        MutString getExtension() const;

        $NoIgnoreReturn
        const String& getPath() const;

        $NoIgnoreReturn
        bool isExist() const;

        $NoIgnoreReturn
        bool isReadOnly() const;

        $NoIgnoreReturn
        bool isFile() const;

        $NoIgnoreReturn
        bool isDirectory() const;

        $NoIgnoreReturn
        bool isSymlink() const;

        $NoIgnoreReturn
        bool isJunction() const;

        void create() const;

        bool createIf() const; CTIDY_NOLINT(modernize-use-nodiscard)

        void remove() const;

        bool removeIf() const; CTIDY_NOLINT(modernize-use-nodiscard)

        $NoIgnoreReturn
        collections::ArrayList<MutString> splitPath() const;

        $NoIgnoreReturn
        FileInputStream inStream() const;

        $NoIgnoreReturn
        FileOutputStream outStream() const;

        $NoIgnoreReturn
        FileReader reader() const;

        $NoIgnoreReturn
        FileWriter writer() const;
    };
}

#ifndef EOF
#define EOF (-1)
#endif
