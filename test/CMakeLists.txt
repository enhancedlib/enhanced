## Copyright (C) 2021 Liu Baihao. All rights reserved.
## This product is licensed under Enhanced License.
##
## This copyright disclaimer is subject to change without notice.
##
## This software is a free software,
## everyone can change, copy, publication, demonstrate, use, etc.
##
## If you change and publication this software,
## must credit the original software source and author's name,
## and include this copyright disclaimer and
## the license of this software in your software.
##
## This software and documentation may provide
## third-party content, product and other information.
## I am not responsible for any loss or damage caused
## by your access to or use of third-party content, products, etc.

cmake_minimum_required(VERSION 3.0)

set(PROMPT "[Module: test]")

set(REQUIRES_MODULES "EnhancedCore" "EnhancedBasic" "EnhancedContainer")

message("${PROMPT} Module path: \"${CMAKE_CURRENT_SOURCE_DIR}\"")

add_executable(TestC "test_c.c")
message("${PROMPT} Adds target (executable) \"TestC\"")
add_executable(TestCPP "test_cpp.cpp")
message("${PROMPT} Adds target (executable) \"TestCPP\"")

foreach (REQUIRES_MODULE_FULL_NAME IN ITEMS ${REQUIRES_MODULES})
    string(TOUPPER ${REQUIRES_MODULE_FULL_NAME} REQUIRES_MODULE_FULL_NAME_UPPER)
    set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${MODULE_${REQUIRES_MODULE_FULL_NAME_UPPER}_ROOT}/include")
endforeach ()

message("${PROMPT} Included directory: ${INCLUDE_DIRECTORIES}")

target_include_directories(TestC PRIVATE ${INCLUDE_DIRECTORIES})
target_include_directories(TestCPP PRIVATE ${INCLUDE_DIRECTORIES})

foreach (REQUIRES_MODULE_FULL_NAME IN ITEMS ${REQUIRES_MODULES})
    target_link_libraries(TestC PRIVATE ${REQUIRES_MODULE_FULL_NAME})
    message("${PROMPT} The target \"TestC\" links library \"${REQUIRES_MODULE_FULL_NAME}\"")
    target_link_libraries(TestCPP PRIVATE ${REQUIRES_MODULE_FULL_NAME})
    message("${PROMPT} The target \"TestCPP\" links library \"${REQUIRES_MODULE_FULL_NAME}\"")
endforeach ()

install(TARGETS TestC DESTINATION "${CMAKE_INSTALL_PREFIX}")
message("${PROMPT} Installs target \"TestC\" to \"${CMAKE_INSTALL_PREFIX}\"")
install(TARGETS TestCPP DESTINATION "${CMAKE_INSTALL_PREFIX}")
message("${PROMPT} Installs target \"TestCPP\" to \"${CMAKE_INSTALL_PREFIX}\"")
