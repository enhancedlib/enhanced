cmake_minimum_required(VERSION 3.0)

project("Enhanced")

set(PROMPT "[Main CMakeLists]")

set(
    MODULES
    "core"
    "basic"
)

set(
    MODULES_FULL_NAME
    "EnhancedCore"
    "EnhancedBasic"
)

if (!${CMAKE_BUILD_TYPE})
    set(CMAKE_BUILD_TYPE ${CMAKE_CONFIGURATION_TYPES})
endif ()

message("${PROMPT} CMake version: ${CMAKE_VERSION}")
message("${PROMPT} Project path: \"${CMAKE_CURRENT_SOURCE_DIR}\"")
message("${PROMPT} Build directory: \"${CMAKE_CURRENT_BINARY_DIR}\"")
message("${PROMPT} C Compiler path: \"${CMAKE_C_COMPILER}\"")
message("${PROMPT} C++ Compiler path: \"${CMAKE_CXX_COMPILER}\"")
message("${PROMPT} C standard: ${CMAKE_C_STANDARD}")
message("${PROMPT} C++ standard: ${CMAKE_CXX_STANDARD}")
message("${PROMPT} Build type: ${CMAKE_BUILD_TYPE}")
message("${PROMPT} Installation directory: ${CMAKE_INSTALL_PREFIX}")

message("${PROMPT} All modules: ${MODULES_FULL_NAME}")

foreach (MODULE_NAME IN ITEMS ${MODULES})
    string(TOUPPER ${MODULE_NAME} MODULE_NAME_UPPER)
    set(MODULE_ENHANCED${MODULE_NAME_UPPER}_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/${MODULE_NAME}")
endforeach ()

message("${PROMPT} Begins configuring modules")
foreach (MODULE_NAME IN ITEMS ${MODULES})
    add_subdirectory(${MODULE_NAME})
endforeach ()

add_subdirectory("test")

message("${PROMPT} Configuring modules done")

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    install(FILES "README.md" DESTINATION ".")
    message("${PROMPT} Set the installation directory for the \"README.md\" file")
    install(FILES "LICENSE" DESTINATION ".")
    message("${PROMPT} Set the installation directory for the \"LICENSE\" file")
    install(FILES "COPYRIGHT" DESTINATION ".")
    message("${PROMPT} Set the installation directory for the \"COPYRIGHT\" file")
endif ()
