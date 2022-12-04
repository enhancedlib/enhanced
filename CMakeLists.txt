##
## Copyright (C) 2022 Liu Baihao. All rights reserved.
##
## Licensed under the Enhanced Software License.
## You may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
##     https://sharedwonder.github.io/enhanced/LICENSE.txt
##
## UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING,
## THE SOFTWARE IS ALWAYS PROVIDED "AS IS",
## WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
## INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY.
##

cmake_minimum_required(VERSION 3.0)

project("Enhanced")

function (setup_module MODULE_NAME)
    set(PROMPT "[Module: ${MODULE_NAME}]")
    set(MODULE_DIR "${CMAKE_SOURCE_DIR}/${MODULE_NAME}")

    message("${PROMPT} Configuring module: ${MODULE_NAME}")
    message("${PROMPT} Module path: \"${MODULE_DIR}\"")

    if (NOT EXISTS "${MODULE_DIR}")
        return()
    endif ()

    file(GLOB_RECURSE SOURCES ${MODULE_DIR}/sources/*.cpp)
    file(GLOB_RECURSE HEADERS ${MODULE_DIR}/include/*.h)

    string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

    if (DEPENDENT_MODULES)
        message("${PROMPT} Dependent modules: ${DEPENDENT_MODULES}")
    else ()
        message("${PROMPT} This module doesn't requires other modules")
    endif ()

    set(INCLUDE_DIRECTORIES "${MODULE_DIR}/include")
    foreach (DEPENDENT_MODULE IN ITEMS ${DEPENDENT_MODULES})
        set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${CMAKE_SOURCE_DIR}/${DEPENDENT_MODULE}/include")
    endforeach ()
    message("${PROMPT} Included directories: ${INCLUDE_DIRECTORIES}")

    install(DIRECTORY "include" DESTINATION "${CMAKE_INSTALL_PREFIX}")
    message("${PROMPT} Set the installation directory for the \"include\" directory")

    add_library(${MODULE_NAME}-static STATIC ${SOURCES} ${HEADERS})
    message("${PROMPT} Adds target (static library) \"${MODULE_NAME}-static\"")

    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
        target_compile_definitions(${MODULE_NAME}-static PUBLIC _DEBUG)
    else ()
        target_compile_definitions(${MODULE_NAME}-static PUBLIC NDEBUG)
    endif ()
    target_include_directories(${MODULE_NAME}-static PRIVATE ${INCLUDE_DIRECTORIES})

    target_compile_definitions(${MODULE_NAME}-static PRIVATE ENHANCED_BUILDING)
    target_compile_definitions(${MODULE_NAME}-static PRIVATE ENHANCED_${MODULE_NAME_UPPER}_BUILDING)

    set_target_properties(${MODULE_NAME}-static PROPERTIES OUTPUT_NAME enhanced.${MODULE_NAME})
    if (WIN32)
        set_target_properties(${MODULE_NAME}-static PROPERTIES PREFIX "lib")
    endif ()
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
        set_target_properties(${MODULE_NAME}-static PROPERTIES POSTFIX "_d")
    endif ()

    foreach (DEPENDENT_MODULE IN ITEMS ${DEPENDENT_MODULES})
        target_link_libraries(${MODULE_NAME}-static PRIVATE ${DEPENDENT_MODULE}-static)
    endforeach ()

    install(TARGETS ${MODULE_NAME}-static)
    message("${PROMPT} Set the installation directory for the target \"${MODULE_NAME}-static\"")

    add_library(${MODULE_NAME}-shared SHARED ${SOURCES} ${HEADERS})
    message("${PROMPT} Adds target (shared library) \"${MODULE_NAME}-shared\"")

    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
        target_compile_definitions(${MODULE_NAME}-shared PUBLIC _DEBUG)
    else ()
        target_compile_definitions(${MODULE_NAME}-shared PUBLIC NDEBUG)
    endif ()

    target_compile_definitions(${MODULE_NAME}-shared PRIVATE ENHANCED_BUILDING)
    target_compile_definitions(${MODULE_NAME}-shared PRIVATE ENHANCED_${MODULE_NAME_UPPER}_BUILDING)
    target_compile_definitions(${MODULE_NAME}-shared PUBLIC ENHANCED_${MODULE_NAME_UPPER}_SHARED_LIBRARY)

    target_include_directories(${MODULE_NAME}-shared PRIVATE ${INCLUDE_DIRECTORIES})

    set_target_properties(${MODULE_NAME}-shared PROPERTIES OUTPUT_NAME enhanced.${MODULE_NAME})
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug" OR ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
        set_target_properties(${MODULE_NAME}-shared PROPERTIES POSTFIX "_d")
    endif ()
    if (WIN32)
        set_target_properties(${MODULE_NAME}-shared PROPERTIES PREFIX "")
    endif ()

    foreach (DEPENDENT_MODULE IN ITEMS ${DEPENDENT_MODULES})
        target_link_libraries(${MODULE_NAME}-shared PRIVATE ${DEPENDENT_MODULE}-shared)
    endforeach ()

    install(TARGETS ${MODULE_NAME}-shared)
    message("${PROMPT} Set the installation directory for the target \"${MODULE_NAME}-shared\"")
endfunction ()

function (setup_test)
    set(PROMPT "[test]")

    message("${PROMPT} Configuring test")
    message("${PROMPT} Test sources path: \"${CMAKE_SOURCE_DIR}/test\"")

    set(DEPENDENT_MODULES ${MODULES})
    message("${PROMPT} Dependent modules: ${DEPENDENT_MODULES}")

    set(INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/test")
    foreach (DEPENDENT_MODULE IN ITEMS ${DEPENDENT_MODULES})
        set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${CMAKE_SOURCE_DIR}/${DEPENDENT_MODULE}/include")
    endforeach ()
    message("${PROMPT} Included directories: ${INCLUDE_DIRECTORIES}")

    file(GLOB_RECURSE SOURCES test/*.cpp)
    file(GLOB_RECURSE HEADERS test/*.h)

    add_executable(test ${SOURCES} ${HEADERS})

    message("${PROMPT} Adds target (executable) \"test\"")

    target_include_directories(test PRIVATE ${INCLUDE_DIRECTORIES})

    foreach (DEPENDENT_MODULE IN ITEMS ${DEPENDENT_MODULES})
        target_link_libraries(test PRIVATE ${DEPENDENT_MODULE}-shared)
    endforeach ()
endfunction ()

if (!${CMAKE_BUILD_TYPE})
    if (!${CMAKE_CONFIGURATION_TYPES})
        set(CMAKE_BUILD_TYPE ${CMAKE_CONFIGURATION_TYPES})
    else ()
        set(CMAKE_BUILD_TYPE Release)
    endif ()
endif ()

if (NOT CMAKE_CXX_STANDARD OR ${CMAKE_CXX_STANDARD} LESS 20)
    set(CMAKE_CXX_STANDARD 20)
endif ()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/targets)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/targets)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/targets)

file(STRINGS ".modules" MODULES)

set(PROMPT "[Root CMakeLists]")

message("${PROMPT} CMake version: ${CMAKE_VERSION}")
message("${PROMPT} Project path: \"${CMAKE_SOURCE_DIR}\"")
message("${PROMPT} Build directory: \"${CMAKE_BINARY_DIR}\"")
message("${PROMPT} Installation directory: \"${CMAKE_INSTALL_PREFIX}\"")
message("${PROMPT} C++ Compiler path: \"${CMAKE_CXX_COMPILER}\"")
message("${PROMPT} C++ standard: ${CMAKE_CXX_STANDARD}")
message("${PROMPT} Build type: ${CMAKE_BUILD_TYPE}")
message("${PROMPT} All modules: ${MODULES}")

message("${PROMPT} Begins configuring modules")

foreach (MODULE_NAME IN ITEMS ${MODULES})
    setup_module(${MODULE_NAME})
endforeach ()

message("${PROMPT} Configuring modules done")

if (EXISTS "${CMAKE_SOURCE_DIR}/test")
    setup_test()
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Release" OR ${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
    install(FILES "README.md" DESTINATION ".")
    message("${PROMPT} Set the installation directory for the \"README.md\" file")
    install(FILES "LICENSE" DESTINATION ".")
    message("${PROMPT} Set the installation directory for the \"LICENSE\" file")
    install(FILES "COPYRIGHT" DESTINATION ".")
    message("${PROMPT} Set the installation directory for the \"COPYRIGHT\" file")
endif ()
