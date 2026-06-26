cmake_minimum_required(VERSION 4.3)
project(pinlog VERSION 1.0 DESCRIPTION "The logging library for pinpal" LANGUAGES C)
include(GNUInstallDirs)

add_library(pinlog SHARED src/pinlog.c)
add_library(pinlog_static STATIC src/pinlog.c)
set_target_properties(pinlog PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER include/pinlog/pinlog.h)

set_target_properties(pinlog_static PROPERTIES
    OUTPUT_NAME pinlog 
    CLEAN_DIRECT_OUTPUT 1)

target_include_directories(pinlog 
    PRIVATE .
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)


target_include_directories(pinlog_static
    PRIVATE .
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

configure_file(pinlog.pc.in pinlog.pc @ONLY)


add_executable(example example.c)
target_link_libraries(example pinlog)
target_include_directories(example PRIVATE include)

set_target_properties(example PROPERTIES
    INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}"
    INSTALL_RPATH_USE_LINK_PATH TRUE)

# Remove the old manual CONFIG_FILE_CONTENT and VERSION_FILE_CONTENT blocks entirely

# Instead, use CMake's built-in helpers:
include(CMakePackageConfigHelpers)

# Generate version file
write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/pinlogConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Create config file template
set(CONFIG_TEMPLATE ${CMAKE_BINARY_DIR}/pinlogConfig.cmake.in)
file(WRITE ${CONFIG_TEMPLATE}
"@PACKAGE_INIT@

# Import targets
include(\${CMAKE_CURRENT_LIST_DIR}/pinlogTargets.cmake)
")

# Configure the file
configure_package_config_file(
    ${CONFIG_TEMPLATE}
    ${CMAKE_BINARY_DIR}/pinlogConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pinlog
    PATH_VARS CMAKE_INSTALL_PREFIX
)

# Install config files
install(FILES
    ${CMAKE_BINARY_DIR}/pinlogConfig.cmake
    ${CMAKE_BINARY_DIR}/pinlogConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pinlog
)

# Export the targets (this creates pinlogTargets.cmake)
install(EXPORT pinlogTargets
    FILE pinlogTargets.cmake
    NAMESPACE pinlog::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pinlog
)

install(TARGETS pinlog pinlog_static
    EXPORT pinlogTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/pinlog)

install(FILES 
    ${CMAKE_BINARY_DIR}/pinlog.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

install(FILES 
    ${CMAKE_BINARY_DIR}/pinlogConfig.cmake
    ${CMAKE_BINARY_DIR}/pinlogConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/pinlog)
