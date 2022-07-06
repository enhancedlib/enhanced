cmake_minimum_required(VERSION 3.0)

set(MODULE_NAME basic)
set(MODULE_FULL_NAME EnhancedBasic)
set(PROMPT "[Module: ${MODULE_NAME} (${MODULE_FULL_NAME})]")

set(REQUIRES_MODULES "EnhancedCore")
set(INCLUDE_DIRECTORIES "include")

set(
    SOURCES
    sources/math/LargeInteger.c
    sources/math/LargeInteger.cpp
    sources/math/Math.c
    sources/math/Math.cpp
    sources/util/Allocator.cpp
    sources/collection/ArrayList.cpp
    sources/collection/LinkedList.cpp
    sources/collection/Vector.cpp
    sources/collection/mixed/MixedArrayList.cpp
    sources/collection/mixed/MixedLinkedList.cpp
    sources/collection/refer/ReferArrayList.cpp
    sources/collection/refer/ReferLinkedList.cpp
    sources/core/String.c
    sources/core/String.cpp
    sources/core/exception/Exception.c
    sources/core/exception/Exception.cpp
    sources/core/pointer/SharedPointer.cpp
)

set(
    HEADERS
    include/Enhanced/basic/module-info.h
    include/Enhanced/basic/export.h
    include/Enhanced/basic/collection/ArrayDeque.h
    include/Enhanced/basic/collection/ArrayList.h
    include/Enhanced/basic/collection/Collection.h
    include/Enhanced/basic/collection/Deque.h
    include/Enhanced/basic/collection/LinkedList.h
    include/Enhanced/basic/collection/LinkedQueue.h
    include/Enhanced/basic/collection/List.h
    include/Enhanced/basic/collection/PriorityQueue.h
    include/Enhanced/basic/collection/Queue.h
    include/Enhanced/basic/collection/Tuple.h
    include/Enhanced/basic/collection/mixed/MixedArrayList.h
    include/Enhanced/basic/collection/mixed/MixedDeque.h
    include/Enhanced/basic/collection/mixed/MixedLinkedList.h
    include/Enhanced/basic/collection/mixed/MixedList.h
    include/Enhanced/basic/collection/mixed/MixedQueue.h
    include/Enhanced/basic/collection/refer/ReferArrayList.h
    include/Enhanced/basic/collection/refer/ReferDeque.h
    include/Enhanced/basic/collection/refer/ReferLinkedList.h
    include/Enhanced/basic/collection/refer/ReferList.h
    include/Enhanced/basic/collection/refer/ReferQueue.h
    include/Enhanced/basic/collection/RandomAccess.h
    include/Enhanced/basic/core/Iterable.h
    include/Enhanced/basic/core/Iterator.h
    include/Enhanced/basic/core/String.h
    include/Enhanced/basic/core/exception/Exception.h
    include/Enhanced/basic/core/exception/StandardExceptions.h
    include/Enhanced/basic/math/LargeInteger.h
    include/Enhanced/basic/math/Math.h
    include/Enhanced/basic/util/Allocator.h
    include/Enhanced/basic/util/Generic.h
    include/Enhanced/basic/core/pointer/SharedPointer.h
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
message("${PROMPT} Installs directory \"include\" to ${CMAKE_INSTALL_PREFIX}")

string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)
string(TOUPPER ${CMAKE_BUILD_TYPE} BUILD_TYPE_UPPER)

add_library(${MODULE_FULL_NAME}-Static STATIC ${SOURCES} ${HEADERS})
message("${PROMPT} Adds target (static library) \"${MODULE_FULL_NAME}-Static\"")

target_compile_definitions(${MODULE_FULL_NAME}-Static PUBLIC ${BUILD_TYPE_UPPER})
target_include_directories(${MODULE_FULL_NAME}-Static PRIVATE ${INCLUDE_DIRECTORIES})

set_target_properties(${MODULE_FULL_NAME}-Static PROPERTIES OUTPUT_NAME ${MODULE_FULL_NAME})
if (WIN32)
    set_target_properties(${MODULE_FULL_NAME}-Static PROPERTIES PREFIX "lib")
endif ()
if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set_target_properties(${MODULE_FULL_NAME}-Static PROPERTIES POSTFIX "_d")
endif ()

foreach (REQUIRES_MODULE_FULL_NAME IN ITEMS ${REQUIRES_MODULES})
    target_link_libraries(${MODULE_FULL_NAME}-Static PRIVATE ${REQUIRES_MODULE_FULL_NAME}-Static)
    message("${PROMPT} The target \"${MODULE_FULL_NAME}\" links library \"${REQUIRES_MODULE_FULL_NAME}\"")
endforeach ()

install(TARGETS ${MODULE_FULL_NAME}-Static)
message("${PROMPT} Installs target \"${MODULE_FULL_NAME}-Static\"")

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
message("${PROMPT} Installs target \"${MODULE_FULL_NAME}\"")

message("${PROMPT} Module configuring done")
