/*
 * Copyright (C) 2023 Liu Baihao. All rights reserved.
 *
 * Licensed under the MIT License with "Fairness" Exception.
 *
 * You may not use this file except in compliance with the License.
 *
 * This file is part of The Enhanced Software, and IT ALWAYS
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

#ifndef EOF
    #define EOF (-1)
#endif

namespace enhanced::io {
    class File {
    public:
    	File(const String& path);

        File(const File& file);

        File(File&& file) noexcept;

        [[RetNotIgnored]]
        MutString getFilename() const;

        [[RetNotIgnored]]
        MutString getExtension() const;

        [[RetNotIgnored]]
        const String& getPath() const;

        [[RetNotIgnored]]
        bool isExist() const;

        [[RetNotIgnored]]
        bool isReadOnly() const;

        [[RetNotIgnored]]
        bool isFile() const;

        [[RetNotIgnored]]
        bool isDirectory() const;

        [[RetNotIgnored]]
        bool isSymlink() const;

        [[RetNotIgnored]]
        bool isJunction() const;

        void create() const;

        bool createIf() const; CTIDY_NOLINT(modernize-use-nodiscard)

        void remove() const;

        bool removeIf() const; CTIDY_NOLINT(modernize-use-nodiscard)

        [[RetNotIgnored]]
        collections::ArrayList<MutString> splitPath() const;

        [[RetNotIgnored]]
        FileInputStream inStream() const;

        [[RetNotIgnored]]
        FileOutputStream outStream() const;

        [[RetNotIgnored]]
        FileReader reader() const;

        [[RetNotIgnored]]
        FileWriter writer() const;
    };
}
