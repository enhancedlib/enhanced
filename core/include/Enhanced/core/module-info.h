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
 * The Licensor is not responsible for any loss or damage
 * caused by your access to or use of third-party content, products, etc.
 *
 * For any loss or damage caused by this software,
 * the licensor may provide possible solutions,
 * but it does not mean that the licensor will definitely solve the problem.
 * In no event shall the licensor be liable for any claims,
 * damages or other liabilities.
 *
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 */

#pragma once

#include "module.h"

MODULE_INFO_START // Start defining module information.

/*!
 * This module is the core module of Enhanced.
 * It includes based function.
 */
MODULE(Core)

MODULE_VERSION(Core, 0, 1, 0, 0.1, "dev", 1)
MODULE_AUTHOR(Core, "Liu Baihao")
MODULE_ABOUT(Core, "The core module of Enhanced.")

MODULE_RELATIONS(
    Core,
    EXPORTS_PACKAGE(EnhancedCore)
)

MODULE_INFO_END // End defining module information.
