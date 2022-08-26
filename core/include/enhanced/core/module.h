/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * Licensed under the Enhanced License, Version 0.5.4 (the "License").
 * You may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt
 *
 * UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
 * THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

typedef const struct {
    int major;
    int minor;
    int patch;
    const char* releaseLevel;
    int serial;
    double build;
} ModuleVersion;

typedef const char* ModuleAuthor;
typedef const char* ModuleAbout;

enum MODULE_RELATIONS {
    MODULE_RELATION_REQUIRES_MODULE,
    MODULE_RELATION_EXPORTS_PACKAGE
};

typedef const struct {
    enum MODULE_RELATIONS relation;
    const char* content;
} ModuleRelations[];

#define MODULE_INFO_START
#define MODULE_INFO_END

#define MODULE(name)
#define MODULE_VERSION(name, major, minor, patch, level, serial, build) \
    static ModuleVersion Module ## name ## Version = {major, minor, patch, level, serial, build};
#define MODULE_AUTHOR(name, author) static ModuleAuthor Module ## name ## Author = (author);
#define MODULE_ABOUT(name, about) static ModuleAbout Module ## name ## About = (about);

#define MODULE_RELATIONS(name, ...) static ModuleRelations Module ## name ## Relations = {__VA_ARGS__};
#define REQUIRES_MODULE(module) {MODULE_RELATION_REQUIRES_MODULE, #module}
#define EXPORTS_PACKAGE(package) {MODULE_RELATION_EXPORTS_PACKAGE, #package}
