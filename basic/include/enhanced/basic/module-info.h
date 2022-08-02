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
MODULE(basic)

MODULE_VERSION(basic, 0, 1, 0, "dev", 1, 0.1)
MODULE_AUTHOR(basic, "Liu Baihao")
MODULE_ABOUT(basic, "The basic module of Enhanced.")

MODULE_RELATIONS(
    basic,
    REQUIRES_MODULE(core),
    EXPORTS_PACKAGE(enhanced::basic),
    EXPORTS_PACKAGE(enhanced::basic::collection),
    EXPORTS_PACKAGE(enhanced::basic::collection::mixed),
    EXPORTS_PACKAGE(enhanced::basic::collection::refer),
    EXPORTS_PACKAGE(enhanced::basic::exception),
    EXPORTS_PACKAGE(enhanced::basic::math),
    EXPORTS_PACKAGE(enhanced::basic::util)
)

MODULE_INFO_END // End defining module information.
