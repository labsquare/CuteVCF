# This file is part of CuteVCF.
#
# CuteVCF is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# CuteVCF is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with CuteVCF.  If not, see <http://www.gnu.org/licenses/>.
#
# Copyright 2016 Labsquare <sacha@labsquare.org>

# We require CMake >= 3.0
# Minimal version is needed in order to avoid warnings
cmake_minimum_required(VERSION 3.0)

# Set projectname (must be done AFTER setting configurationtypes)
set(VERSION "0.2.0")
project(CuteVCF)

# add dependencies
# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)


# Libraries & platform specific settings
if(UNIX)
    # In order for find_package to be successful, Qt 5 must be found below the CMAKE_PREFIX_PATH
    # http://doc.qt.io/qt-5/cmake-manual.html
    set(CMAKE_PREFIX_PATH "/media/DATA/Qt5.7.0/5.7/gcc_64/" "/media/DATA/Qt5.7.0/5.7/gcc_64/lib/")
endif()

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Concurrent REQUIRED)

# Compilers FLAGS (c++ 11 & linker options)
if(CMAKE_COMPILER_IS_GNUCXX)
    # For g++/gcc/mingw32 compiler

    # Optimize
    set(CMAKE_CXX_FLAGS "-O3")
    # Strip binary
    set(CMAKE_EXE_LINKER_FLAGS "-s")
    # Add flags from dpkg-buildflags
    # https://wiki.debian.org/Hardening
    set(LDFLAGS "-Wl,-z,relro")
    set(CXXFLAGS "-g -O2 -fstack-protector-strong -Wformat -Werror=format-security")
    set(CPPFLAGS "-D_FORTIFY_SOURCE=2")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS} ${CXXFLAGS} ${CPPFLAGS}")

    set(warnings "-Wall -Wextra -Werror")

    # c++11
    MESSAGE(STATUS "Activation of c++11")
    # Other syntax: add_definitions(-std=gnu++0x)
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
    CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
    if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
    else()
        message(WARNING "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
    endif()
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # For Visual Studio etc compiler
    # MSVC does not require any special flags for c++11
    set(warnings "/W4 /WX /EHsc")

    # Optimization of linker for static libs
    # Avoid this error: json_vc71_libmt.lib(json_value.obj) : .netmodule ou module MSIL compilé avec /GL
    # Add /LTCG to the command line of the linker
    set(CMAKE_EXE_LINKER_FLAGS "/LTCG" )
    ADD_DEFINITIONS(-D_HAS_ITERATOR_DEBUGGING=0)
endif()

MESSAGE(STATUS "Cmake prefix: ${CMAKE_SOURCE_DIR}")

# Executable definition
qt5_add_resources(UI_RESOURCES files.qrc)
# Add QFontIcon header
include_directories(QFontIcon)
add_executable(
    CuteVCF #Target names may not contain slashes. This is not a supported use case.
    ../aboutdialog.h
    ../createindexdialog.h
    ../infowidget.h
    ../mainwindow.h
    ../qtabix.h
    ../samplewidget.h
    ../vcfheader.h
    ../vcfline.h
    ../vcfmodel.h
    ../QFontIcon/qfonticon.h

    ../aboutdialog.cpp
    ../createindexdialog.cpp
    ../infowidget.cpp
    ../mainwindow.cpp
    ../main.cpp
    ../qtabix.cpp
    ../samplewidget.cpp
    ../vcfheader.cpp
    ../vcfline.cpp
    ../vcfmodel.cpp
    ../QFontIcon/qfonticon.cpp
    ${UI_RESOURCES}
)

find_library(HTS_LIB hts)
if(HTS_LIB)
    MESSAGE(STATUS "Hts library found at: ${HTS_LIB}")
else()
    MESSAGE(FATAL_ERROR "Hts library NOT found ! Please install it")
#     # Try to use the pre-compiled library
#     find_library(HTS_LIB hts ${lib_dir} NO_DEFAULT_PATH)
#     if(HTS_LIB)
#         MESSAGE(STATUS "Hts library found at: ${HTS_LIB}")
#     else()
#         MESSAGE(STATUS "Hts library not found at: ${HTS_LIB} => will be built")
# => https://github.com/broadinstitute/firepony/blob/master/contrib/htslib.cmake
#     endif()
endif()

if(HTS_LIB)
    target_link_libraries(
          CuteVCF
          # We want to use the system lib
          ${HTS_LIB}
          # Use the following modules from Qt 5.
          Qt5::Widgets
          Qt5::Concurrent
    )
# else()
#     # Try to use the pre-compiled library
#     target_link_libraries(
#         CuteVCF
#         library.a
#         Qt5::Widgets
#         Qt5::Concurrent
#     )
endif()

# Build in Release-mode by default if not explicitly set
if( NOT CMAKE_BUILD_TYPE )
  set(CMAKE_BUILD_TYPE "Release")
endif()

# Installation
if(UNIX)
    # ${CMAKE_INSTALL_PREFIX} : /usr/local/
    set(CMAKE_INSTALL_PREFIX "/usr/")
    INSTALL(TARGETS CuteVCF
            DESTINATION "${CMAKE_INSTALL_PREFIX}bin")

    # Debian package
    add_subdirectory(dist_package)

endif()

#if(WIN32)
#    INSTALL(TARGETS CuteVCF DESTINATION c:/windows/)
#endif()


#notes :
#make VERBOSE=1

#CMAKE_EXE_LINKER_FLAGS
#CMAKE_SHARED_LINKER_FLAGS
#CMAKE_MODULE_LINKER_FLAGS
#STATIC_LIBRARY_FLAGS Extra flags to use when linking static libraries