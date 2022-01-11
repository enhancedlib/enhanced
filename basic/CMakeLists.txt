cmake_minimum_required(VERSION 3.0)

set(MODULE_NAME basic)
set(MODULE_FULL_NAME EnhancedBasic)
set(PROMPT "[Module: ${MODULE_NAME} (${MODULE_FULL_NAME})]")

set(REQUIRES_MODULES "EnhancedCore")
set(INCLUDE_DIRECTORIES "include")

set(
    SOURCES
    sources/core/Integer.c
    sources/core/Integer.cpp
    sources/core/String.c
    sources/core/String.cpp
    sources/core/exception/Exception.c
    sources/core/exception/Exception.cpp
    sources/math/LargeInteger.c
    sources/math/LargeInteger.cpp
    sources/math/Math.c
    sources/math/Math.cpp
    sources/collection/ArrayList.cpp
    sources/collection/LinkedList.cpp
    sources/collection/Vector.cpp
    sources/collection/mixed/MixedArrayList.cpp
    sources/collection/mixed/MixedLinkedList.cpp
    sources/collection/referenced/ReferencedArrayList.cpp
    sources/collection/referenced/ReferencedLinkedList.cpp
)

set(
    HEADERS
    include/EnhancedBasic/defines.h
    include/EnhancedBasic/core/Any.h
    include/EnhancedBasic/core/Iterable.h
    include/EnhancedBasic/core/Iterator.h
    include/EnhancedBasic/core/Integer.h
    include/EnhancedBasic/core/String.h
    include/EnhancedBasic/core/exception/Exception.h
    include/EnhancedBasic/math/LargeInteger.h
    include/EnhancedBasic/math/Math.h
    include/EnhancedBasic/collection/ArrayDeque.h
    include/EnhancedBasic/collection/ArrayList.h
    include/EnhancedBasic/collection/Collection.h
    include/EnhancedBasic/collection/Deque.h
    include/EnhancedBasic/collection/LinkedList.h
    include/EnhancedBasic/collection/LinkedQueue.h
    include/EnhancedBasic/collection/List.h
    include/EnhancedBasic/collection/PriorityQueue.h
    include/EnhancedBasic/collection/Queue.h
    include/EnhancedBasic/collection/Tuple.h
    include/EnhancedBasic/collection/mixed/MixedArrayList.h
    include/EnhancedBasic/collection/mixed/MixedDeque.h
    include/EnhancedBasic/collection/mixed/MixedLinkedList.h
    include/EnhancedBasic/collection/mixed/MixedList.h
    include/EnhancedBasic/collection/mixed/MixedQueue.h
    include/EnhancedBasic/collection/referenced/ReferencedArrayList.h
    include/EnhancedBasic/collection/referenced/ReferencedDeque.h
    include/EnhancedBasic/collection/referenced/ReferencedLinkedList.h
    include/EnhancedBasic/collection/referenced/ReferencedList.h
    include/EnhancedBasic/collection/referenced/ReferencedQueue.h
    include/EnhancedBasic/pointer/SharedPointer.h
    include/EnhancedBasic/collection/RandomAccess.h
    include/EnhancedBasic/generics/Generics.h)

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
