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

#ifndef MODULE_ENHANCED_BASIC
#define MODULE_ENHANCED_BASIC

#include "EnhancedCore/module.h"

MODULE_INFO_START // Start defining module information.

/*!
 * This module includes basic data types and container.
 */
MODULE(Basic)

MODULE_VERSION(Basic, 0, 1, 0, 0.1, "dev", 1)
MODULE_AUTHOR(Basic, "Liu Baihao")
MODULE_ABOUT(Basic, "The basic module of Enhanced.")

MODULE_RELATIONS(Basic,
    REQUIRES_MODULE(Core),
    EXPORTS_PACKAGE(EnhancedBasic::collection),
    EXPORTS_PACKAGE(EnhancedBasic::collection::referenced),
    EXPORTS_PACKAGE(EnhancedBasic::collection::mixed),
    EXPORTS_PACKAGE(EnhancedBasic::core),
    EXPORTS_PACKAGE(EnhancedBasic::core::exception),
    EXPORTS_PACKAGE(EnhancedBasic::generic),
    EXPORTS_PACKAGE(EnhancedBasic::map),
    EXPORTS_PACKAGE(EnhancedBasic::math),
    EXPORTS_PACKAGE(EnhancedBasic::pointer)
)

MODULE_INFO_END // End defining module information.

#endif // !MODULE_ENHANCED_BASIC
