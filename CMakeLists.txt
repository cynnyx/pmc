#
# Building in-tree is not allowed (we take care of your craziness).
#

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

#
# Project configuration
#
set(PROJECT_NAME pmc)
project(${PROJECT_NAME})
cmake_minimum_required(VERSION 3.0)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

if(NOT LIBRARY_TYPE)
    set(LIBRARY_TYPE "Shared")
endif(NOT LIBRARY_TYPE)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 0)
set(PROJECT_VERSION ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH})
set(PROJECT_AUTHOR "Ryan A. Rossi")
set(PROJECT_YEAR_COPYRIGHT "2017")
set(PROJECT_AUTHOR_EMAIL "ryarossi@gmail.com")

set(PROJECT_BUILD_MESSAGE ${PROJECT_NAME} " v" ${PROJECT_VERSION} " (" ${LIBRARY_TYPE} "." ${CMAKE_BUILD_TYPE} ")")
set(COPYRIGHT_BUILD_MESSAGE "Copyright (c) " ${PROJECT_YEAR_COPYRIGHT} " " ${PROJECT_AUTHOR}  " <" ${PROJECT_AUTHOR_EMAIL} ">")
set(SEE_LICENSE "For more details see LICENSE.md")
set(ARCHITECTS_BUILD_MESSAGE "Designed by")
set(DEVELOPERS_BUILD_MESSAGE "Developed by")
set(CONTRIBUTORS_BUILD_MESSAGE "Contributors")
set(DEV_ROSSI_RYAN        "Ryan A. Rossi        <ryarossi@gmail.com>")
set(DEV_MATASSINI_TOMMASO "Tommaso Matassini    <tommaso.matassini@cynny.com>")
set(DEV_RINALDELLI_MAURO  "Mauro Rinaldelli     <mauro.rinaldelli@cynny.com>")
set(DEV_OTHERS            "...and all the developers from GitHub")

message("*")
message("* " ${PROJECT_BUILD_MESSAGE})
message("* " ${COPYRIGHT_BUILD_MESSAGE})
message("* " ${SEE_LICENSE})
message("*")
message("* " ${ARCHITECTS_BUILD_MESSAGE})
message("*     " ${DEV_ROSSI_RYAN})
message("*")
message("* " ${DEVELOPERS_BUILD_MESSAGE})
message("*     " ${DEV_ROSSI_RYAN})
message("*     " ${DEV_MATASSINI_TOMMASO})
message("*     " ${DEV_OTHERS})
message("*")
message("* " ${CONTRIBUTORS_BUILD_MESSAGE})
message("*     " ${DEV_RINALDELLI_MAURO})
message("*     " ${DEV_OTHERS})
message("*     " )

#
# Compile stuff
#

if(APPLE)
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-undefined,dynamic_lookup")
else()
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--export-dynamic")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

find_package(OpenMP REQUIRED)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} ")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

#
# CMake configuration
#

set(PROJECT_INSTALL_DIR install)
set(PROJECT_TEST_DIR test)

set(PROJECT_RUNTIME_OUTPUT_DIRECTORY bin)
set(PROJECT_LIBRARY_OUTPUT_DIRECTORY lib)
set(PROJECT_SHARE_OUTPUT_DIRECTORY share)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_LIBRARY_OUTPUT_DIRECTORY})

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/${PROJECT_INSTALL_DIR}/default)


set(PROJECT_CMAKE_MODULES cmake/modules)
set(PROJECT_BUILD_DIR build)
set(PROJECT_SRC_DIR src)
set(PROJECT_DEPS_DIR deps)

set(PROJECT_ARCHIVE_OUTPUT_DIRECTORY lib/static)
set(PROJECT_INCLUDE_OUTPUT_DIRECTORY include)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_CMAKE_MODULES}
)

# Directories
set(DIR_ROOT ${PROJECT_SOURCE_DIR}/${PROJECT_SRC_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_ARCHIVE_OUTPUT_DIRECTORY})

set(TARGET_PMC ${PROJECT_NAME})

find_package(Threads REQUIRED)



add_subdirectory(${PROJECT_DEPS_DIR}/pybind11)
add_subdirectory(${PROJECT_SRC_DIR})
add_subdirectory(${PROJECT_TEST_DIR})

#
# For QtCreator users
#

file(
        GLOB_RECURSE PROJECT_FILES FOLLOW_SYMLINKS
        *.txt *.mk *.c *.cpp *.hpp *.h *.java *.in *.cmake *.m *.mm
        *.djinni *.idl *.dox *.sh Makefile *.example *.config *.build
        *.xml *.py *.scala README *.sql *.patch
)