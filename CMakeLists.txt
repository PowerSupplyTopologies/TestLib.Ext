cmake_minimum_required(VERSION 3.5)
project(libtestlibext VERSION 1.0.0 LANGUAGES CXX)

#Make sure that custom modules like FindRapidJSON are found
list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

##############################################
# Create target and set properties

set(TARGET_NAME testlibext)

add_library(${TARGET_NAME}
    src/ClassC.cpp
)

#Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(TestLib::${TARGET_NAME} ALIAS ${TARGET_NAME})

find_package(TestLib COMPONENTS Base)

#Set target properties
target_include_directories(${TARGET_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(${TARGET_NAME} PRIVATE cxx_auto_type)
target_compile_options(${TARGET_NAME} PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

#target_link_libraries(${TARGET_NAME}
#    PUBLIC
#        Boost::boost RapidJSON::RapidJSON
#    PRIVATE
#        Boost::regex
#)

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/TestLib)

install(TARGETS ${TARGET_NAME}
    EXPORT ${TARGET_NAME}-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

set_target_properties(${TARGET_NAME} PROPERTIES EXPORT_NAME Ext)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

#Export the targets to a script
install(EXPORT ${TARGET_NAME}-targets
  FILE
    TestLibExtTargets.cmake
  NAMESPACE
    TestLib::
  DESTINATION
    ${INSTALL_CONFIGDIR}
)

#Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/TestLibExtConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/TestLibExtConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/TestLibExtConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

#Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/TestLibExtConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/TestLibExtConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree

export(EXPORT ${TARGET_NAME}-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/TestLibExtTargets.cmake NAMESPACE TestLib::)

#Register package in user's package registry
export(PACKAGE TestLib)

#add_subdirectory(test)
