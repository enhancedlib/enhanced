## This file is part of Enhanced Framework.
##
## Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.
##
## Permission is hereby granted, to any person obtaining a copy of this software
## and associated documentation files (the "Software"), to deal in the Software,
## including without limitation the rights to use, copy, modify, merge,
## distribute. Unless you have obtained permission from the copyright holders,
## subject to the following restrictions:
##
## 1. The above copyright notice and this permission notice shall be included in
##    all copies of the Software and modified versions.
##
## 2. You may not misrepresent the source of the Software, and you may not claim
##    that you wrote the original version.
##
## 3. You may not misrepresent the modified version as the original version.
##
## 4. You may not charge any fees or receive other compensation for the
##    distribution of the Software, except for distributing modified versions and
##    products that use the Software.
##
## 5. If you use this Software in your product, you shall indicate it.
##
## 6. Neither the name of the author nor the names of its contributors may
##    be used to endorse or promote products derived from the Software
##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
## SOFTWARE.

cmake_minimum_required(VERSION 3.13)

project("Enhanced")

message("* Enhanced Framework")
message("* Copyright (C) 2023 Liu Baihao (sharedwonder). All rights reserved.")

function (setup_module MODULE_NAME)
    file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*.cpp)
    file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

    string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)

    set(INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")
    foreach (DEPENDENT_MODULE IN ITEMS ${DEPENDENT_MODULES})
        set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${CMAKE_SOURCE_DIR}/modules/${DEPENDENT_MODULE}/include")
    endforeach ()

    install(DIRECTORY "include/" DESTINATION "${CMAKE_INSTALL_PREFIX}/include/${MODULE_NAME}")

    # static library

    add_library(${MODULE_NAME}-static STATIC ${SOURCES})

    target_include_directories(${MODULE_NAME}-static PRIVATE ${INCLUDE_DIRECTORIES})

    target_compile_definitions(${MODULE_NAME}-static PRIVATE _E_BUILDING)
    target_compile_definitions(${MODULE_NAME}-static PRIVATE _E_${MODULE_NAME_UPPER}_BUILDING)

    set_target_properties(${MODULE_NAME}-static PROPERTIES OUTPUT_NAME enhanced.${MODULE_NAME})
    if (WIN32)
        set_target_properties(${MODULE_NAME}-static PROPERTIES PREFIX "lib")
    endif ()

    if (MSVC)
        if (${CMAKE_CXX_FLAGS} MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        else ()
            target_compile_options(${MODULE_NAME}-static PRIVATE /W4)
        endif ()
        target_compile_options(${MODULE_NAME}-static PRIVATE /Zc:preprocessor)
    else ()
        target_compile_options(${MODULE_NAME}-static PRIVATE -Wall -Wextra)
    endif ()

    if (NOT WIN32 AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        target_compile_options(${MODULE_NAME}-static PRIVATE -stdlib=libc++)
        target_link_options(${MODULE_NAME}-static PRIVATE -stdlib=libc++)
    endif ()

    foreach (DEPENDENT_MODULE IN ITEMS ${DEPENDENT_MODULES})
        target_link_libraries(${MODULE_NAME}-static PRIVATE ${DEPENDENT_MODULE}-static)
    endforeach ()

    install(TARGETS ${MODULE_NAME}-static)

    # shared library

    add_library(${MODULE_NAME}-shared SHARED ${SOURCES})

    target_compile_definitions(${MODULE_NAME}-shared PRIVATE _E_BUILDING)
    target_compile_definitions(${MODULE_NAME}-shared PRIVATE _E_${MODULE_NAME_UPPER}_BUILDING)
    target_compile_definitions(${MODULE_NAME}-shared PUBLIC _E_${MODULE_NAME_UPPER}_SHARED_LIBRARY)

    target_include_directories(${MODULE_NAME}-shared PRIVATE ${INCLUDE_DIRECTORIES})

    set_target_properties(${MODULE_NAME}-shared PROPERTIES OUTPUT_NAME enhanced.${MODULE_NAME})
    if (WIN32)
        set_target_properties(${MODULE_NAME}-shared PROPERTIES PREFIX "")
    endif ()

    if (MSVC)
        if (${CMAKE_CXX_FLAGS} MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        else ()
            target_compile_options(${MODULE_NAME}-shared PRIVATE /W4)
        endif ()
        target_compile_options(${MODULE_NAME}-shared PRIVATE /Zc:preprocessor)
    else ()
        target_compile_options(${MODULE_NAME}-shared PRIVATE -Wall -Wextra)
    endif ()

    if (NOT WIN32 AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        target_compile_options(${MODULE_NAME}-shared PRIVATE -stdlib=libc++)
        target_link_options(${MODULE_NAME}-shared PRIVATE -stdlib=libc++)
    endif ()

    foreach (DEPENDENT_MODULE IN ITEMS ${DEPENDENT_MODULES})
        target_link_libraries(${MODULE_NAME}-shared PRIVATE ${DEPENDENT_MODULE}-shared)
    endforeach ()

    install(TARGETS ${MODULE_NAME}-shared)
endfunction ()

# Checks environment.

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif ()

if (NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
        set(CMAKE_BUILD_TYPE "Release")
    endif ()
    set(BUILD_CONFIG ${CMAKE_BUILD_TYPE})
else ()
    set(BUILD_CONFIG ${CMAKE_CONFIGURATION_TYPES})
endif ()

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Do not build at the project root directory")
endif ()

if (${CMAKE_CXX_STANDARD} LESS 20)
    message(FATAL_ERROR "Specified C++ standard (${CMAKE_CXX_STANDARD}) is less than 20, this project isn't supported it")
endif ()

# Configures.

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/targets)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/targets)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/targets)

file(GLOB MODULES RELATIVE "${CMAKE_SOURCE_DIR}/modules" "${CMAKE_SOURCE_DIR}/modules/*")

foreach (MODULE_NAME IN ITEMS ${MODULES})
    add_subdirectory("${CMAKE_SOURCE_DIR}/modules/${MODULE_NAME}")
endforeach ()

if (EXISTS "${CMAKE_SOURCE_DIR}/test")
    set(INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/test")
    foreach (DEPENDENT_MODULE IN ITEMS ${MODULES})
        set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${CMAKE_SOURCE_DIR}/modules/${DEPENDENT_MODULE}/include")
    endforeach ()

    file(GLOB_RECURSE SOURCES test/*.cpp)
    file(GLOB_RECURSE HEADERS test/*.h)

    add_executable(test ${SOURCES} ${HEADERS})

    target_include_directories(test PRIVATE ${INCLUDE_DIRECTORIES})

    foreach (DEPENDENT_MODULE IN ITEMS ${MODULES})
        target_link_libraries(test PRIVATE ${DEPENDENT_MODULE}-shared)
    endforeach ()

    if (MSVC)
        if (${CMAKE_CXX_FLAGS} MATCHES "/W[0-4]")
            string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
        else ()
            target_compile_options(test PRIVATE /W4)
        endif ()
        target_compile_options(test PRIVATE /Zc:preprocessor)
    else ()
        target_compile_options(test PRIVATE -Wall -Wextra)
    endif ()

    if (NOT WIN32 AND ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
        target_compile_options(test PRIVATE -stdlib=libc++)
        target_link_options(test PRIVATE -stdlib=libc++)
    endif ()
endif ()

install(FILES "README.md" "LICENSE" "COPYRIGHT" DESTINATION ".")

# Output information.

message("> CMake version: ${CMAKE_VERSION}")
message("> Project path: \"${CMAKE_SOURCE_DIR}\"")
message("> Build directory: \"${CMAKE_BINARY_DIR}\"")
message("> Installation directory: \"${CMAKE_INSTALL_PREFIX}\"")
message("> Generator: ${CMAKE_GENERATOR}")
message("> C++ compiler path: \"${CMAKE_CXX_COMPILER}\"")
message("> C++ standard: ${CMAKE_CXX_STANDARD}")
message("> Build config: ${BUILD_CONFIG}")
message("> All modules: ${MODULES}")
