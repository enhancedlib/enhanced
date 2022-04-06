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
