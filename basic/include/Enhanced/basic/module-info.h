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

#include "Enhanced/core/module.h"

MODULE_INFO_START // Start defining module information.

/*!
 * This module includes basic data types and container.
 */
MODULE(Basic)

MODULE_VERSION(Basic, 0, 1, 0, 0.1, "dev", 1)
MODULE_AUTHOR(Basic, "Liu Baihao")
MODULE_ABOUT(Basic, "The basic module of Enhanced.")

MODULE_RELATIONS(
    Basic,
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
