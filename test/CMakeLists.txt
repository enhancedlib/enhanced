cmake_minimum_required(VERSION 3.0)

set(PROMPT "[Module: test]")

set(REQUIRES_MODULES ${MODULES_FULL_NAME})

message("${PROMPT} Module path: \"${CMAKE_CURRENT_SOURCE_DIR}\"")

aux_source_directory(. SOURCES)

foreach (REQUIRES_MODULE_FULL_NAME IN ITEMS ${REQUIRES_MODULES})
    string(TOUPPER ${REQUIRES_MODULE_FULL_NAME} REQUIRES_MODULE_FULL_NAME_UPPER)
    set(INCLUDE_DIRECTORIES ${INCLUDE_DIRECTORIES} "${MODULE_${REQUIRES_MODULE_FULL_NAME_UPPER}_ROOT}/include")
endforeach ()

message("${PROMPT} Requires modules: ${REQUIRES_MODULES}")
message("${PROMPT} Included directories: ${INCLUDE_DIRECTORIES}")

foreach (SOURCE IN ITEMS ${SOURCES})
    string(REPLACE "./" "" NAME ${SOURCE})

    add_executable(${NAME} ${SOURCE})
    message("${PROMPT} Adds target (executable) \"${NAME}\"")

    target_include_directories(${NAME} PRIVATE ${INCLUDE_DIRECTORIES})

    foreach (REQUIRES_MODULE_FULL_NAME IN ITEMS ${REQUIRES_MODULES})
        target_link_libraries(${NAME} PRIVATE ${REQUIRES_MODULE_FULL_NAME}-Static)
        message("${PROMPT} The target \"${NAME}\" links library \"${REQUIRES_MODULE_FULL_NAME}\"")
    endforeach ()
endforeach ()
