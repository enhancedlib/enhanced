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

/*!
 * This file provides annotations for APIs. \n
 * \n
 * Restrictive annotations don't affect compilation,
 * they don't have practical significance. \n
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
 *     Unsupported()        Indicates an environment not supported by the API.
 *
 *     Optional             Indicates the argument is optional.
 *
 *     Out                  Sets the argument inside the function and pass it out
 *                          The argument must be a pointer or reference.
 *
 *     InOut                Passes a argument and
 *                          sets the argument inside the function and pass it out.
 *
 *     OutNotIgnored        Sets the argument inside the function and pass it out.
 *                          Passed any should not ignore.
 *
 *     InOutRequired        Passes a argument and
 *                          sets the argument inside the function and pass it out.
 *                          Passed any should not ignore.
 *
 *     NotNull              Indicates the pointer cannot be null.
 *
 *     Unused               Unused argument.
 *
 *     ReferReturn          Indicates the return value should be treated
 *                          as a reference.
 *
 *     RetNotIgnored()      The return value cannot be ignored.
 *
 *     RequiresRelease      Indicates the programmer release the pointer
 *                          (return value or argument).
 *
 *     RetRequiresRelease() Merges RetNotIgnored() and RequiresRelease.
 *
 *     CaseFallThrough()    Suppress warning: "switch-case" statement without
 *                          break statement.
 *
 * Attribute annotations:
 *
 *     Attribute()          Adds an attribute to the API.
 *
 *     NoThrow              Declare that this function does not
 *                          throw an exception (for C++11, you should use noexcept).
 *
 *     NoVtable             Virtual tables are not created for the class.
 *
 *     NoInline             Prevents the compiler from inlining
 *                          the function/method.
 *
 *     NoReturn             Indicates the function/method has no a return value.
 *
 * @endverbatim
 */

#pragma once

#include "defines.h"

// =============================Restrictive annotations============================

#ifdef COMPILER_MSVC
#pragma warning(disable: 4003)
#include <sal.h>
#endif // COMPILER_MSVC

#define Unsupported(options)

#ifdef COMPILER_MSVC

#define Optional _In_opt_
#define Out _Out_opt_
#define InOut _Inout_opt_
#define OutNotIgnored _Out_
#define InOutRequired  _Inout_

#define NotNull _Notnull_

#define MustInspectResult _Must_inspect_result_
#define SuccessWhen(options) _Success_ options

#define When(options) _When_ options

#else

#define SuccessWhen_(expression)

#define When_(expression, annotations)

#define Optional
#define Out
#define InOut
#define OutNotIgnored
#define InOutRequired

#define NotNull

#define NotNull

#define MustInspectResult
#define SuccessWhen(options) Success_ options

#define When(options) When_ options

#endif // COMPILER_MSVC

#define Unused [[maybe_unused]]

#if defined(CXX_20_OR_MORE)
#define RetNotIgnored(options) [[nodiscard options]]
#elif defined(CXX_17_OR_MORE) // C++17 or more
#define RetNotIgnored(options) [[nodiscard]]
#elif defined(COMPILER_MSVC) // Microsoft Visual C++ Compiler
#define RetNotIgnored(options) _Check_return_
#else
#define RetNotIgnored(options)
#endif // CXX_20_OR_MORE

#define ReferReturn

#define RequiresRelease

#define RetRequiresRelease(options) RetNotIgnored(options) RequiresRelease

#ifdef CXX_14_OR_MORE
#define Deprecated(options) [[deprecated options]]
#else
#define Deprecated(options)
#endif // CXX_14_OR_MORE

// ==============================Attribute annotations=============================

#ifdef COMPILER_MSVC
#define Attribute(options) __declspec options
#else
#define Attribute(options) __attribute__(options)
#endif // COMPILER_MSVC

#ifdef CXX_LANGUAGE
#define NoThrow Attribute((nothrow))
#define NoVtable Attribute((novtable))
#endif // CXX_LANGUAGE

#define NoInline Attribute((noinline))
#define NoReturn Attribute((noreturn))
