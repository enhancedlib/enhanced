cmake_minimum_required(VERSION 3.0)

set(MODULE_NAME core)
set(MODULE_FULL_NAME EnhancedCore)
set(PROMPT "[Module: ${MODULE_NAME} (${MODULE_FULL_NAME})]")

set(INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(
    SOURCES
    sources/array.c
    sources/assert.c
    sources/memory.c
    sources/process.c
    sources/string.c
    sources/string.cpp
    sources/wstring.c
    sources/wstring.cpp
)

set(
    HEADERS
    include/enhanced/core/module-info.h
    include/enhanced/core/annotations.h
    include/enhanced/core/array.h
    include/enhanced/core/assert.h
    include/enhanced/core/export.h
    include/enhanced/core/defines.h
    include/enhanced/core/jump.h
    include/enhanced/core/memory.h
    include/enhanced/core/process.h
    include/enhanced/core/string.h
    include/enhanced/core/types.h
    include/enhanced/core/wstring.h
)

message("${PROMPT} Configuring module: ${MODULE_FULL_NAME}")
message("${PROMPT} Module path: \"${CMAKE_CURRENT_SOURCE_DIR}\"")

if (SOURCES)
    message("${PROMPT} Source files: ${SOURCES}")
else ()
    message("${PROMPT} There aren't any source files in this module")
endif ()

if (HEADERS)
    message("${PROMPT} Header files: ${HEADERS}")
else ()
    message("${PROMPT} There aren't any header files in this module")
endif ()

foreach (REQUIRES_MODULE_FULL_NAME IN ITEMS ${REQUIRES_MODULES})
    string(TOUPPER ${REQUIRES_MODULE_FULL_NAME} REQUIRES_MODULE_FULL_NAME_UPPER)
    set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${MODULE_${REQUIRES_MODULE_FULL_NAME_UPPER}_ROOT}/include")
endforeach ()

if (REQUIRES_MODULES)
    message("${PROMPT} Requires modules: ${REQUIRES_MODULES}")
else ()
    message("${PROMPT} This module doesn't requires other modules")
endif ()
message("${PROMPT} Included directories: ${INCLUDE_DIRECTORIES}")

install(DIRECTORY "include" DESTINATION "${CMAKE_INSTALL_PREFIX}")
message("${PROMPT} Set the installation directory for the \"include\" directory")

string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE_UPPER)

add_library(${MODULE_FULL_NAME}-static STATIC ${SOURCES} ${HEADERS})
message("${PROMPT} Adds target (static library) \"${MODULE_FULL_NAME}-static\"")

target_compile_definitions(${MODULE_FULL_NAME}-static PUBLIC ${BUILD_TYPE_UPPER})
target_include_directories(${MODULE_FULL_NAME}-static PRIVATE ${INCLUDE_DIRECTORIES})

set_target_properties(${MODULE_FULL_NAME}-static PROPERTIES OUTPUT_NAME ${MODULE_FULL_NAME})
if (WIN32)
    set_target_properties(${MODULE_FULL_NAME}-static PROPERTIES PREFIX "lib")
endif ()
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set_target_properties(${MODULE_FULL_NAME}-static PROPERTIES POSTFIX "_d")
endif ()

foreach (REQUIRES_MODULE_FULL_NAME IN ITEMS ${REQUIRES_MODULES})
    target_link_libraries(${MODULE_FULL_NAME}-static PRIVATE ${REQUIRES_MODULE_FULL_NAME}-static)
    message("${PROMPT} The target \"${MODULE_FULL_NAME}\" links library \"${REQUIRES_MODULE_FULL_NAME}\"")
endforeach ()

install(TARGETS ${MODULE_FULL_NAME}-static)
message("${PROMPT} Set the installation directory for the target \"${MODULE_FULL_NAME}-static\"")

add_library(${MODULE_FULL_NAME} SHARED ${SOURCES} ${HEADERS})
message("${PROMPT} Adds target (dynamic library) \"${MODULE_FULL_NAME}\"")

target_compile_definitions(${MODULE_FULL_NAME} PRIVATE ENHANCED_${MODULE_NAME_UPPER}_EXPORTS)
target_compile_definitions(${MODULE_FULL_NAME} PUBLIC ENHANCED_${MODULE_NAME_UPPER}_DYNAMIC_LIBRARY)
target_compile_definitions(${MODULE_FULL_NAME} PUBLIC ${BUILD_TYPE_UPPER})
target_include_directories(${MODULE_FULL_NAME} PRIVATE ${INCLUDE_DIRECTORIES})

set_target_properties(${MODULE_FULL_NAME} PROPERTIES OUTPUT_NAME ${MODULE_FULL_NAME})
if (WIN32)
    set_target_properties(${MODULE_FULL_NAME} PROPERTIES PREFIX "")
endif ()
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set_target_properties(${MODULE_FULL_NAME} PROPERTIES POSTFIX "_d")
endif ()

foreach (REQUIRES_MODULE_FULL_NAME IN ITEMS ${REQUIRES_MODULES})
    target_link_libraries(${MODULE_FULL_NAME} PRIVATE ${REQUIRES_MODULE_FULL_NAME})
    message("${PROMPT} The target \"${MODULE_FULL_NAME}\" links library \"${REQUIRES_MODULE_FULL_NAME}\"")
endforeach ()

install(TARGETS ${MODULE_FULL_NAME})
message("${PROMPT} Set the installation directory for the target \"${MODULE_FULL_NAME}\"")

message("${PROMPT} Module configuring done")
