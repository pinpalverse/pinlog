cmake_minimum_required(VERSION 4.3)
project(pinlog VERSION 1.0 DESCRIPTION "The logging library for pinpal" LANGUAGES C)
include(GNUInstallDirs)

add_library(pinlog SHARED src/pinlog.c)
set_target_properties(pinlog PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
    PUBLIC_HEADER include/pinlog.h)

configure_file(pinlog.pc.in pinlog.pc @ONLY)
target_include_directories(pinlog PRIVATE .)

add_executable(example example.c)
target_link_libraries(example pinlog)
target_include_directories(example PRIVATE include)

install(TARGETS pinlog
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/pinlog.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
