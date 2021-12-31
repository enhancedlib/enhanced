/*
 * Copyright (C) 2021 Liu Baihao. All rights reserved.
 * This product is licensed under Enhanced License.
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

#ifndef ENHANCED_BASIC_DEFINES_H
#define ENHANCED_BASIC_DEFINES_H

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
