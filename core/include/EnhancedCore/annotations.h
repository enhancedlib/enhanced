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

/*!
 * This file provides annotations for APIs.\n
 * \n
 * Restrictive annotations don't affect compilation,
 * they don't have practical significance.\n
 * Attribute annotations may affect compilation.
 *
 * <p>* I will join more annotations in the future.</p>
 *
 * @note The annotation with round brackets has arguments.
 *
 * @verbatim
 *
 * Restrictive annotations:
 *
 *     $Unsupported()        Indicates an environment not supported by the API.
 *
 *     $Optional             Indicates the argument is optional.
 *
 *     $Out                  Sets the argument inside the function and pass it out
 *                           The argument must be a pointer or reference.
 *
 *     $InOut                Passes a argument and
 *                           sets the argument inside the function and pass it out.
 *
 *     $OutNotIgnored        Sets the argument inside the function and pass it out.
 *                           Passed any should not ignore.
 *
 *     $InOutRequired        Passes a argument and
 *                           sets the argument inside the function and pass it out.
 *                           Passed any should not ignore.
 *
 *     $NotNull              Indicates the pointer cannot be null.
 *
 *     $Unused               Unused argument.
 *
 *     $RetReferenced        Indicates the return value should be treated
 *                           as a reference.
 *
 *     $RetNotIgnored()      The return value cannot be ignored.
 *
 *     $RequiresRelease      Indicates the programmer release the pointer
 *                           (return value or argument).
 *
 *     $RetRequiresRelease() Merges $RetNotIgnored() and $RequiresRelease.
 *
 *     $CaseFallThrough()    Suppress warning: "switch-case" statement without
 *                           break statement.
 *
 * Attribute annotations:
 *
 *     $Attribute()          Adds an attribute to the API.
 *
 *     $NoThrow              Declare that this function does not
 *                           throw an exception (for C++11, you should use noexcept).
 *
 *     $NoVtable             Virtual tables are not created for the class.
 *
 *     $NoInline             Prevents the compiler from inlining
 *                           the function/method.
 *
 *     $NoReturn             Indicates the function/method has no a return value.
 *
 * @endverbatim
 */

#ifndef ENHANCED_ANNOTATIONS_H
#define ENHANCED_ANNOTATIONS_H

#include "EnhancedCore/defines.h"

// =============================Restrictive annotations============================

#ifdef COMPILER_MSVC
#pragma warning(disable: 4003)
#endif // COMPILER_MSVC

#define $Unsupported(options)

#ifdef COMPILER_MSVC

#include <sal.h>

#define $Optional _In_opt_
#define $Out _Out_opt_
#define $InOut _Inout_opt_
#define $OutNotIgnored _Out_
#define $InOutRequired  _Inout_
#define $NotNull _Notnull_

#else

#define $Optional
#define $Out
#define $InOut
#define $OutNotIgnored
#define $InOutRequired
#define $NotNull

#endif // COMPILER_MSVC

#define $Unused [[maybe_unused]]


#if defined(CXX_20_OR_MORE)
#define $RetNotIgnored(options) [[nodiscard options]]
#elif defined(CXX_17_OR_MORE) // C++17 or more
#define $RetNotIgnored(options) [[nodiscard]]
#elif defined(COMPILER_MSVC) // Microsoft Visual C++ compiler
#define $RetNotIgnored(options) _Check_return_
#else
#define $RetNotIgnored(options)
#endif // CXX_20_OR_MORE

#define $RetReferenced

#define $RequiresRelease

#define $RetRequiresRelease(options) $RetNotIgnored(options) $RequiresRelease

#ifdef CXX_14_OR_MORE
#define $Deprecated(options) [[deprecated options]]
#else
#define $Deprecated(options)
#endif // CXX_14_OR_MORE

// ==============================Attribute annotations=============================

#ifdef COMPILER_MSVC
#define $Attribute(options) __declspec options
#else
#define $Attribute(options) __attribute__(options)
#endif // COMPILER_MSVC

#ifdef CXX_LANGUAGE
#define $NoThrow $Attribute((nothrow))
#define $NoVtable $Attribute((novtable))
#endif // CXX_LANGUAGE

#define $NoInline $Attribute((noinline))
#define $NoReturn $Attribute((noreturn))

#endif // !ENHANCED_ANNOTATIONS_H
