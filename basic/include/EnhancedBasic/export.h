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

#ifndef ENHANCED_BASIC_DEFINES_H
#define ENHANCED_BASIC_DEFINES_H

#include "EnhancedCore/defines.h"

#if defined(WINDOWS_OS) /* Windows OS */ && defined(ENHANCED_BASIC_DYNAMIC_LIBRARY) /* Dynamic library */
#ifdef ENHANCED_BASIC_EXPORTS // Export
#define ENHANCED_BASIC_API __declspec(dllexport)
#else // Import
#define ENHANCED_BASIC_API __declspec(dllimport)
#endif // ENHANCED_BASIC_EXPORTS
#else // Static library or other operating system.
#define ENHANCED_BASIC_API
#endif // defined(WINDOWS_OS) && defined(ENHANCED_CORE_DYNAMIC_LIBRARY)

#endif // !ENHANCED_BASIC_DEFINES_H
