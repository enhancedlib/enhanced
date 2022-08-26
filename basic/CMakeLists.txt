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
    sources/container/ArrayList.cpp
    sources/container/ContainerConfig.cpp
    sources/container/LinkedList.cpp
    sources/container/Vector.cpp
    sources/container/mixed/MixedArrayList.cpp
    sources/container/mixed/MixedLinkedList.cpp
    sources/container/refer/ReferArrayList.cpp
    sources/container/refer/ReferLinkedList.cpp
    sources/MutableString.cpp
    sources/String.c
    sources/String.cpp
    sources/exception/Exception.c
    sources/exception/Exception.cpp
    sources/util/Allocator.cpp
    sources/util/SharedPointer.cpp
)

set(
    HEADERS
    include/enhanced/basic/module-info.h
    include/enhanced/basic/export.h
    include/enhanced/basic/container/ArrayDeque.h
    include/enhanced/basic/container/ArrayList.h
    include/enhanced/basic/container/Collection.h
    include/enhanced/basic/container/ContainerConfig.h
    include/enhanced/basic/container/Deque.h
    include/enhanced/basic/container/LinkedList.h
    include/enhanced/basic/container/LinkedQueue.h
    include/enhanced/basic/container/List.h
    include/enhanced/basic/container/PriorityQueue.h
    include/enhanced/basic/container/Queue.h
    include/enhanced/basic/container/Tuple.h
    include/enhanced/basic/container/mixed/MixedArrayList.h
    include/enhanced/basic/container/mixed/MixedDeque.h
    include/enhanced/basic/container/mixed/MixedLinkedList.h
    include/enhanced/basic/container/mixed/MixedList.h
    include/enhanced/basic/container/mixed/MixedQueue.h
    include/enhanced/basic/container/refer/ReferArrayList.h
    include/enhanced/basic/container/refer/ReferDeque.h
    include/enhanced/basic/container/refer/ReferLinkedList.h
    include/enhanced/basic/container/refer/ReferList.h
    include/enhanced/basic/container/refer/ReferQueue.h
    include/enhanced/basic/container/RandomAccess.h
    include/enhanced/basic/CharSequence.h
    include/enhanced/basic/Iterable.h
    include/enhanced/basic/Iterator.h
    include/enhanced/basic/MutableString.h
    include/enhanced/basic/String.h
    include/enhanced/basic/exception/Exception.h
    include/enhanced/basic/math/LargeInteger.h
    include/enhanced/basic/math/Math.h
    include/enhanced/basic/util/Allocator.h
    include/enhanced/basic/util/Checker.h
    include/enhanced/basic/util/convert.h
    include/enhanced/basic/util/generic.h
    include/enhanced/basic/util/SharedPointer.h

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

add_library(${MODULE_FULL_NAME} SHARED ${SOURCES} ${HEADERS} sources/CharSequence.cpp)
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
