/*
 * Copyright (C) 2022 Liu Baihao. All rights reserved.
 *
 * This software is licensed under Enhanced License.
 * You may not use this file except in compliance with the License.
 * You should see a copy of Enhanced License in this software, if not, visit
 * <https://sharedwonder.github.io/enhanced-website/ENHANCED-LICENSE.txt>
 *
 * The Software is always provided "AS IS",
 * WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
 */

#pragma once

#include "enhanced/core/module.h"

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
    EXPORTS_PACKAGE(EnhancedBasic::exception),
    EXPORTS_PACKAGE(EnhancedBasic::generic),
    EXPORTS_PACKAGE(EnhancedBasic::map),
    EXPORTS_PACKAGE(EnhancedBasic::math),
    EXPORTS_PACKAGE(EnhancedBasic::pointer)
)

MODULE_INFO_END // End defining module information.
