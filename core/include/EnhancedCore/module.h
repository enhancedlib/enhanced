/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 * This software is licensed under Enhanced License.
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

#ifndef ENHANCED_CORE_MODULE_H
#define ENHANCED_CORE_MODULE_H

typedef const struct {
    int major;
    int minor;
    int patch;
    double build;
    const char *releaseLevel;
    int serial;
} ModuleVersion;

typedef const char *ModuleAuthor;
typedef const char *ModuleAbout;

enum MODULE_RELATIONS {
    MODULE_RELATION_REQUIRES_MODULE,
    MODULE_RELATION_EXPORTS_PACKAGE
};

typedef const struct {
    enum MODULE_RELATIONS relation;
    const char *content;
} ModuleRelations[];

#define MODULE_INFO_START
#define MODULE_INFO_END

#define MODULE(name)
#define MODULE_VERSION(name, major, minor, patch, build, releaseLevel, serial) \
    static ModuleVersion Module ## name ## Version = {major, minor, patch, build, releaseLevel, serial};
#define MODULE_AUTHOR(name, author) static ModuleAuthor Module ## name ## Author = (author);
#define MODULE_ABOUT(name, about) static ModuleAbout Module ## name ## About = (about);

#define MODULE_RELATIONS(name, ...) static ModuleRelations Module ## name ## Relations = {__VA_ARGS__};
#define REQUIRES_MODULE(module) {MODULE_RELATION_REQUIRES_MODULE, #module}
#define EXPORTS_PACKAGE(package) {MODULE_RELATION_EXPORTS_PACKAGE, #package}

#endif // !ENHANCED_CORE_MODULE_H
