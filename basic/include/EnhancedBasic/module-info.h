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

#include "EnhancedCore/defines.h"

MODULE_INFO_START // Start defining module information.

#define MODULE_BASIC

/*!
 * This module includes basic data types and container.
 */
MODULE(basic)

MODULE_FULL_NAME(basic, "Enhanced Basic")
MODULE_VERSION(basic, 0, 1, 0, 0.1, "dev", 1)
MODULE_AUTHOR(basic, "Liu Baihao")
MODULE_ABOUT(basic, "The basic module of Enhanced.")

MODULE_RELATIONS(basic,
    REQUIRES_MODULE("Enhanced Core"),
    EXPORTS_PACKAGE("EnhancedBasic/collection"),
    EXPORTS_PACKAGE("EnhancedBasic/collection/referenced"),
    EXPORTS_PACKAGE("EnhancedBasic/collection/mixed"),
    EXPORTS_PACKAGE("EnhancedBasic/core"),
    EXPORTS_PACKAGE("EnhancedBasic/core/exception"),
    EXPORTS_PACKAGE("EnhancedBasic/generic"),
    EXPORTS_PACKAGE("EnhancedBasic/map"),
    EXPORTS_PACKAGE("EnhancedBasic/math"),
    EXPORTS_PACKAGE("EnhancedBasic/pointer")
)

MODULE_INFO_END // End defining module information.
