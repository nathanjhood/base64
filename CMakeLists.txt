cmake_minimum_required (VERSION 3.15...3.27 FATAL_ERROR)

set (CMAKE_MODULE_PATH
  "${CMAKE_CURRENT_LIST_DIR}/share/cmake/Modules"
  "${CMAKE_MODULE_PATH}"
)

# Name of the project (will be the name of the plugin)
project (base64 VERSION 1.0.0.0)

# Add our headers to a list
set(HEADERS)
list(APPEND HEADERS
  "include/${PROJECT_NAME}/${PROJECT_NAME}.hpp"
)

set(SOURCE_FILES)
file(GLOB SOURCE_FILES
  "src/${PROJECT_NAME}/${PROJECT_NAME}.cpp"
)

# If building out-of-source...
if (NOT ${PROJECT_SOURCE_DIR} EQUAL ${PROJECT_BINARY_DIR})
  # ...copy our headers to the binary directory.
  foreach(HEADER IN LISTS HEADERS)
    configure_file("${HEADER}" "${HEADER}")
  endforeach()
endif()

# Start a list of targets to be built
set(TARGETS)

## Shared library

# Build a shared library named after the project
# Alias it to the vendor namespace
add_library(${PROJECT_NAME} SHARED)
add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# Put our target in the right output dir
set_target_properties(${PROJECT_NAME}
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"
)

# Include our configured headers
target_include_directories(${PROJECT_NAME}
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Include our sources to be compiled
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_FILES})

# Add the target to the list
list(APPEND TARGETS ${PROJECT_NAME})

## Command Line

configure_file("include/${PROJECT_NAME}/cli.hpp" "include/${PROJECT_NAME}/cli.hpp")
add_library(cli SHARED)
add_library(${PROJECT_NAME}::cli ALIAS cli)
set_target_properties(cli
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"
)
target_include_directories(cli
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
target_sources(cli PRIVATE "src/${PROJECT_NAME}/cli.cpp")
target_link_libraries(cli ${PROJECT_NAME}::${PROJECT_NAME})
list(APPEND TARGETS cli)

## Executable

# Create an exectable for testing
add_executable(main)
add_executable(${PROJECT_NAME}::main ALIAS main)
target_sources(main PRIVATE "src/main.cpp")
target_link_libraries(main ${PROJECT_NAME}::${PROJECT_NAME} cli)
set_target_properties(main
  PROPERTIES
  ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
  RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
  PDB_OUTPUT_DIRECTORY     "${CMAKE_BINARY_DIR}/bin"
  OUTPUT_NAME ${PROJECT_NAME}
)

# Add the target to the list
list(APPEND TARGETS main)

# Collect and export targets
set (${PROJECT_NAME}_TARGETS ${TARGETS} CACHE STRING "Targets to be built." FORCE)

export(
  TARGETS ${${PROJECT_NAME}_TARGETS}
  FILE ${PROJECT_BINARY_DIR}/share/cmake/${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
)

# get access to helper functions for creating config files
include(CMakePackageConfigHelpers)

include(JoinPaths)
join_paths(libdir_for_pc_file "\${exec_prefix}" "${CMAKE_INSTALL_LIBDIR}")
join_paths(includedir_for_pc_file "\${prefix}" "${CMAKE_INSTALL_INCLUDEDIR}")

# Create package config file
configure_file(
  ${PROJECT_SOURCE_DIR}/share/pkgconfig/${PROJECT_NAME}.pc.in
  ${PROJECT_BINARY_DIR}/share/pkgconfig/${PROJECT_NAME}.pc
  @ONLY
)

# create cmake config file
configure_package_config_file(
    ${PROJECT_SOURCE_DIR}/share/cmake/${PROJECT_NAME}Config.cmake.in
    ${PROJECT_BINARY_DIR}/share/cmake/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}
)

# generate the version file for the cmake config file
write_basic_package_version_file(
	${PROJECT_BINARY_DIR}/share/cmake/${PROJECT_NAME}ConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY AnyNewerVersion
)
