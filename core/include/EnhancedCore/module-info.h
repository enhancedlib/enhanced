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

#ifndef MODULE_ENHANCED_CORE
#define MODULE_ENHANCED_CORE

#include "EnhancedCore/module.h"

MODULE_INFO_START // Start defining module information.

/*!
 * This module is the core module of Enhanced.
 * It includes based function.
 */
MODULE(Core)

MODULE_VERSION(Core, 0, 1, 0, 0.1, "dev", 1)
MODULE_AUTHOR(Core, "Liu Baihao")
MODULE_ABOUT(Core, "The core module of Enhanced.")

MODULE_RELATIONS(Core,
    EXPORTS_PACKAGE(EnhancedCore)
)

MODULE_INFO_END // End defining module information.

#endif // !MODULE_ENHANCED_CORE
