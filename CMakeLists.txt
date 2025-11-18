#
# librtdebug - C++ thread-safe runtime debugging library
#              https://github.com/hzdr-MedImaging/librtdebug
#
# Copyright (C) 2003-2025 hzdr.de and contributors
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.12.0)

# Default configuration values. These must be before the project command or
# they won't work in Windows.
# If no build type is specified, default to "Release"
if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING
      "None Debug Release RelWithDebInfo MinSizeRel"
      FORCE)
endif()

# define the project and the version number
set(PKG_VERSION 3.0.0)
project(librtdebug VERSION ${PKG_VERSION})
set(PROJECT_LONGNAME "librtdebug")

# change output directory to top-level 'bin' dir.
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Global CMake options
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# set the cmake modules path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# In case we are cross compiling we have to setup
# everything for different search paths
if(CMAKE_CROSS_COMPILING)
  set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
  set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
endif()

# set the search+install prefix
if(NOT PREFIX_PATH)
  if(MSYS)
    set(PREFIX_PATH "C:/MinGW/msys/1.0/local/petlib")
  else()
    set(PREFIX_PATH "/usr/local/petlib")
  endif()
endif()

# if /usr/local/petlib is found use that one for install and search prefix
if(EXISTS ${PREFIX_PATH})
  set(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${PREFIX_PATH})
  set(CMAKE_INSTALL_PREFIX ${PREFIX_PATH})
else()
  message("WARNING: selected PREFIX path '${PREFIX_PATH}' does not exist")
endif()

message("Using Search Path: ${CMAKE_PREFIX_PATH}")
message("Using Install Prefix: ${CMAKE_INSTALL_PREFIX}")

# Configure third party packages
find_package(Threads REQUIRED)

# select shared/static build
set(STATIC_BUILD TRUE)
set(SHARED_BUILD TRUE)

# set _USE_MATH_DEFINES to have M_PI for Windows builds
if(WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_USE_MATH_DEFINES")
endif()

# Set some better optimization options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mtune=generic -std=c++11 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE, "${CMAKE_CXX_FLAGS_RELEASE} -O3 -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO, "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3 -g -fomit-frame-pointer")
set(CMAKE_CXX_FLAGS_DEBUG, "${CMAKE_CXX_FLAGS_RELEASE} -O0")

add_subdirectory(src)
