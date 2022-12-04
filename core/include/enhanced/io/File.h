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

#pragma once

#include <enhanced/Defines.h>
#include <enhanced/Types.h>
#include <enhanced/Annotations.h>
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
        String getFilename() const;

        $NoIgnoreReturn
        String getExtension() const;

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
        collections::ArrayList<String> splitPath() const;

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

#undef EOF
#define EOF (-1)
