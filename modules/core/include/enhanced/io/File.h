/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with the Distribution Exception.
 * You may not use this file except in compliance with the License.
 *
 * THIS FILE IS PART OF THE ENHANCED SOFTWARE, and IT ALWAYS
 * PROVIDES "AS IS" WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
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

#undef EOF
#define EOF (-1)

namespace enhanced::io {
    class File {
    public:
    	File(const String& path);

        File(const File& file);

        File(File&& file) noexcept;

        E_ANNOTATE(RetNotIgnored)
        String getFilename() const;

        E_ANNOTATE(RetNotIgnored)
        String getExtension() const;

        E_ANNOTATE(RetNotIgnored)
        const String& getPath() const;

        E_ANNOTATE(RetNotIgnored)
        bool isExist() const;

        E_ANNOTATE(RetNotIgnored)
        bool isReadOnly() const;

        E_ANNOTATE(RetNotIgnored)
        bool isFile() const;

        E_ANNOTATE(RetNotIgnored)
        bool isDirectory() const;

        E_ANNOTATE(RetNotIgnored)
        bool isSymlink() const;

        void create() const;

        bool createIf() const; E_CTIDY_NOLINT(modernize-use-nodiscard)

        void remove() const;

        bool removeIf() const; E_CTIDY_NOLINT(modernize-use-nodiscard)

        E_ANNOTATE(RetNotIgnored)
        collections::ArrayList<String> splitPath() const;

        E_ANNOTATE(RetNotIgnored)
        FileInputStream inStream() const;

        E_ANNOTATE(RetNotIgnored)
        FileOutputStream outStream() const;

        E_ANNOTATE(RetNotIgnored)
        FileReader reader() const;

        E_ANNOTATE(RetNotIgnored)
        FileWriter writer() const;
    };
}
