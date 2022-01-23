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
    sources/generic/Any.cpp
    sources/generic/Allocator.cpp
    sources/collection/ArrayList.cpp
    sources/collection/LinkedList.cpp
    sources/collection/Vector.cpp
    sources/collection/mixed/MixedArrayList.cpp
    sources/collection/mixed/MixedLinkedList.cpp
    sources/collection/referenced/ReferencedArrayList.cpp
    sources/collection/referenced/ReferencedLinkedList.cpp
    sources/core/Integer.c
    sources/core/Integer.cpp
    sources/core/String.c
    sources/core/String.cpp
    sources/core/exception/Exception.c
    sources/core/exception/Exception.cpp
    sources/core/pointer/SharedPointer.cpp
)

set(
    HEADERS
    include/EnhancedBasic/module-info.h
    include/EnhancedBasic/export.h
    include/EnhancedBasic/collection/Vector.tcc
    include/EnhancedBasic/collection/ArrayDeque.h
    include/EnhancedBasic/collection/ArrayList.h
    include/EnhancedBasic/collection/ArrayList.tcc
    include/EnhancedBasic/collection/Collection.h
    include/EnhancedBasic/collection/Deque.h
    include/EnhancedBasic/collection/LinkedList.h
    include/EnhancedBasic/collection/LinkedList.tcc
    include/EnhancedBasic/collection/LinkedQueue.h
    include/EnhancedBasic/collection/List.h
    include/EnhancedBasic/collection/PriorityQueue.h
    include/EnhancedBasic/collection/Queue.h
    include/EnhancedBasic/collection/Tuple.h
    include/EnhancedBasic/collection/mixed/MixedArrayList.h
    include/EnhancedBasic/collection/mixed/MixedArrayList.tcc
    include/EnhancedBasic/collection/mixed/MixedDeque.h
    include/EnhancedBasic/collection/mixed/MixedLinkedList.h
    include/EnhancedBasic/collection/mixed/MixedLinkedList.tcc
    include/EnhancedBasic/collection/mixed/MixedList.h
    include/EnhancedBasic/collection/mixed/MixedQueue.h
    include/EnhancedBasic/collection/referenced/ReferencedArrayList.h
    include/EnhancedBasic/collection/referenced/ReferencedArrayList.tcc
    include/EnhancedBasic/collection/referenced/ReferencedDeque.h
    include/EnhancedBasic/collection/referenced/ReferencedLinkedList.h
    include/EnhancedBasic/collection/referenced/ReferencedLinkedList.tcc
    include/EnhancedBasic/collection/referenced/ReferencedList.h
    include/EnhancedBasic/collection/referenced/ReferencedQueue.h
    include/EnhancedBasic/collection/RandomAccess.h
    include/EnhancedBasic/core/Integer.h
    include/EnhancedBasic/core/Iterable.h
    include/EnhancedBasic/core/Iterable.tcc
    include/EnhancedBasic/core/Iterator.h
    include/EnhancedBasic/core/String.h
    include/EnhancedBasic/core/exception/Exception.h
    include/EnhancedBasic/math/LargeInteger.h
    include/EnhancedBasic/math/Math.h
    include/EnhancedBasic/generic/Allocator.h
    include/EnhancedBasic/generic/Allocator.tcc
    include/EnhancedBasic/generic/Any.h
    include/EnhancedBasic/generic/Any.tcc
    include/EnhancedBasic/generic/AnyArray.h
    include/EnhancedBasic/generic/AnyArray.tcc
    include/EnhancedBasic/generic/Generic.h
    include/EnhancedBasic/core/pointer/SharedPointer.h
    include/EnhancedBasic/core/pointer/SharedPointer.tcc
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
