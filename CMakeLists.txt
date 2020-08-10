cmake_minimum_required(VERSION 3.18)

project(app VERSION 1.0)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the output folder where your program will be created
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/archive")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")
set(CMAKE_CONFIG_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/includes")
set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install")

#Bring the headers into the project
#include_directories(${PROJECT_SOURCE_DIR})

# add the Renderers library
add_subdirectory(renderers)

# package the sourcers in SOURCES
file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp")

# executable
add_executable(app ${SOURCES})

target_link_libraries(app PUBLIC Renderers)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
target_include_directories(app
  PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/renderers"
)
                          
# create and include config.h
configure_file(config.h.in ${CMAKE_CONFIG_OUTPUT_DIRECTORY}/config.h)
target_include_directories(app PUBLIC "${CMAKE_CONFIG_OUTPUT_DIRECTORY}")


# install
install(TARGETS app DESTINATION bin)
install(FILES "${CMAKE_CONFIG_OUTPUT_DIRECTORY}/config.h"
  DESTINATION include
)

### Testing
enable_testing()

# does the application run
add_test(NAME Runs COMMAND app 4 5)

# define a function to simplify adding tests
function(do_test target arg1 arg2 result)
  add_test(NAME Computing${arg1}-${arg2} COMMAND ${target} ${arg1} ${arg2})
  set_tests_properties(Computing${arg1}-${arg2}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
  )
endfunction(do_test)

# do a bunch of result based tests
do_test(app 4 5 "291.5")
do_test(app 14 25 "1298.5")


# Pack for distribution
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${app_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${app_VERSION_MINOR}")
set(CPACK_PACKAGE_DIRECTORY "${PROJECT_BINARY_DIR}/releases")
include(CPack)


