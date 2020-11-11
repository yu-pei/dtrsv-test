cmake_minimum_required (VERSION 3.12)
project (DTRSM C)

include(CMakeDependentOption)
include(CMakePushCheckState)
include(CheckSymbolExists)
include(CheckCSourceCompiles)
include(CheckIncludeFiles)
include(GNUInstallDirs)

# The current version number
set (DTRSM_VERSION_MAJOR 2)
set (DTRSM_VERSION_MINOR 0)
set (DTRSM_VERSION_PATCH 0)

SET(DTRSM_VERSION "${DPLASMA_VERSION_MAJOR}.${DPLASMA_VERSION_MINOR}")

set(CMAKE_NO_SYSTEM_FROM_IMPORTED True)

# CMake Policies Tuning
if(POLICY CMP0074)
  # CMP0074: Starting with CMake 3.12, all FIND_<something> use <something>_ROOT in the search path
  #          in addition to the specified paths
  cmake_policy(SET CMP0074 NEW)
ENDIF(POLICY CMP0074)
if(POLICY CMP0094)
  # CMP0094: Starting with CMake 3.16, all FIND_Python will use the first matching version instead of
  #          of searching for the largest available version number (which defeats our selection logic)
  cmake_policy(SET CMP0094 NEW)
ENDIF(POLICY CMP0094)


option(BUILD_64bits
  "Build 64 bits mode" ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "Choose the type of build, options are None, Debug, Release, RelWithDebInfo and MinSizeRel." FORCE)
endif(NOT CMAKE_BUILD_TYPE)

option(BUILD_SHARED_LIBS
       "Enable building shared DPLASMA lib (default ON)" ON)


option(SUPPORT_C11
       "Enable support for C11 capabilities. Might not work with OpenMP support due to an OpenMP compilers restriction (default ON)." ON)
if( SUPPORT_C11 )
  set(CMAKE_C_STANDARD 11)
else (SUPPORT_C11)
  set(CMAKE_C_STANDARD 99)
endif( SUPPORT_C11 )
set(CMAKE_C_STANDARD_REQUIRED ON)


STRING(COMPARE EQUAL ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} DTRSM_BUILD_INPLACE)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dplasma/cmake_modules/")
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/dplasma/tools/PrecisionGenerator/")

#set(BLA_VENDOR CACHE STRING "Possible valid values are: Intel10_64lp_seq, IBMESSL, Apple, or All, which will default to something like Goto or ATLAS")
# Goto, ATLAS, PhiPACK, CXML, DXML, SunPerf, SCSL, SGIMATH, IBMESSL, Intel10_64lp_seq, ACML, ACML_MP, ACML_GPU, Apple, NAS, Generic
#set_property(CACHE BLA_VENDOR PROPERTY STRINGS Intel10_64lp_seq IBMESSL Apple Goto ATLAS)
#find_package(LAPACKE REQUIRED)

# we have to build it
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/dplasma/CMakeLists.txt")
    find_package(Git QUIET)
    if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
        # Update submodules as needed
        option(GIT_SUBMODULE "Check submodules during build" ON)
        if(GIT_SUBMODULE)
            message(STATUS "Submodule update")
            execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --force --init --recursive --remote
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                RESULT_VARIABLE GIT_SUBMOD_RESULT)
            if(NOT GIT_SUBMOD_RESULT EQUAL "0")
                message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
            endif()
        endif()
    endif()
endif(NOT EXISTS "${PROJECT_SOURCE_DIR}/dplasma/CMakeLists.txt")

#option(PARSEC_WITH_DEVEL_HEADERS "" ON)
add_subdirectory(dplasma)
# Import targets and load dependent libraries
#find_package(parsec-submodule NO_DEFAULT_PATH PATHS ${CMAKE_CURRENT_BINARY_DIR}/parsec REQUIRED)
#set(DPLASMA_FORCE_INTERNAL_PARSEC ${PaRSEC_FOUND} CACHE BOOL "Force using the internal PaRSEC submodule (submodule used in previous configure)" FORCE)


# Export Targets
#install(EXPORT dplasma-targets # rules to export the targets built here
#  FILE dplasma-targets.cmake
#  NAMESPACE DPlasma::
#  DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/dplasma)

# cmake config files
#include(CMakePackageConfigHelpers)

#add_custom_target(build_with_dplasma ALL DEPENDS ${pattern_files_dest})
add_library(MyLibExample dtrsm_LLT.c dtrsm_LLN.c dtrsm_LLT.h dtrsm_LLN.h)

add_executable(MyExample testing_dtrsm.c)
target_link_libraries(MyExample PRIVATE dplasma MyLibExample)
