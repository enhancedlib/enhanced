cmake_minimum_required(VERSION 3.0)

set(MODULE_NAME core)
set(MODULE_FULL_NAME EnhancedCore)
set(PROMPT "[Module: ${MODULE_NAME} (${MODULE_FULL_NAME})]")

set(INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/include")

set(
    SOURCES
    sources/array.c
    sources/assert.c
    sources/jump.c
    sources/memory.c
    sources/string.c
)

set(
    HEADERS
    include/EnhancedCore/annotations.h
    include/EnhancedCore/array.h
    include/EnhancedCore/assert.h
    include/EnhancedCore/defines.h
    include/EnhancedCore/jump.h
    include/EnhancedCore/memory.h
    include/EnhancedCore/string.h
    include/EnhancedCore/types.h
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

add_library(${MODULE_FULL_NAME}-StaticLibrary STATIC ${SOURCES} ${HEADERS})
message("${PROMPT} Adds target (static library) \"${MODULE_FULL_NAME}-StaticLibrary\"")
add_library(${MODULE_FULL_NAME} SHARED ${SOURCES} ${HEADERS})
message("${PROMPT} Adds target (dynamic library) \"${MODULE_FULL_NAME}\"")

string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)
target_compile_definitions(${MODULE_FULL_NAME} PUBLIC ENHANCED_${MODULE_NAME_UPPER}_DYNAMIC_LIBRARY)
target_compile_definitions(${MODULE_FULL_NAME} PRIVATE ENHANCED_${MODULE_NAME_UPPER}_EXPORTS)

string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE_UPPER)
target_compile_definitions(${MODULE_FULL_NAME}-StaticLibrary PUBLIC ${BUILD_TYPE_UPPER})
target_compile_definitions(${MODULE_FULL_NAME} PUBLIC ${BUILD_TYPE_UPPER})

target_include_directories(${MODULE_FULL_NAME}-StaticLibrary PRIVATE ${INCLUDE_DIRECTORIES})
target_include_directories(${MODULE_FULL_NAME} PRIVATE ${INCLUDE_DIRECTORIES})

foreach (REQUIRES_MODULE_FULL_NAME IN ITEMS ${REQUIRES_MODULES})
    target_link_libraries(${MODULE_FULL_NAME} PRIVATE ${REQUIRES_MODULE_FULL_NAME})
    message("${PROMPT} The target \"${MODULE_FULL_NAME}\" links library \"${REQUIRES_MODULE_FULL_NAME}\"")
endforeach ()

set_target_properties(${MODULE_FULL_NAME}-StaticLibrary PROPERTIES OUTPUT_NAME ${MODULE_FULL_NAME})
set_target_properties(${MODULE_FULL_NAME} PROPERTIES OUTPUT_NAME ${MODULE_FULL_NAME})

if (WIN32)
    set_target_properties(${MODULE_FULL_NAME}-StaticLibrary PROPERTIES PREFIX "lib")
    set_target_properties(${MODULE_FULL_NAME} PROPERTIES PREFIX "")
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    install(DIRECTORY "include" DESTINATION "${CMAKE_INSTALL_PREFIX}")
    message("${PROMPT} Installs directory \"include\" to ${CMAKE_INSTALL_PREFIX}")
    install(TARGETS ${MODULE_FULL_NAME}-StaticLibrary)
    message("${PROMPT} Installs target \"${MODULE_FULL_NAME}-StaticLibrary\"")
    install(TARGETS ${MODULE_FULL_NAME})
    message("${PROMPT} Installs target \"${MODULE_FULL_NAME}\"")
else ()
    install(TARGETS ${MODULE_FULL_NAME} DESTINATION "${CMAKE_INSTALL_PREFIX}")
    message("${PROMPT} Installs target \"${MODULE_FULL_NAME}\" to \"${CMAKE_INSTALL_PREFIX}\"")
endif ()

message("${PROMPT} Module configuring done")
