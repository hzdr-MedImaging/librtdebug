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

# check for certain functions to exist
include(CheckFunctionExists)
check_function_exists(gettimeofday HAVE_GETTIMEOFDAY)
check_function_exists(GetTickCount HAVE_GETTICKCOUNT)
check_function_exists(vasprintf HAVE_VASPRINTF)
check_function_exists(vsnprintf HAVE_VSNPRINTF)
check_function_exists(localtime_r HAVE_LOCALTIME_R)
check_function_exists(localtime_s HAVE_LOCALTIME_S)
check_function_exists(localtime HAVE_LOCALTIME)
check_function_exists(strftime HAVE_STRFTIME)

# check if pthread library was found
if(CMAKE_USE_PTHREADS_INIT)
  set(HAVE_LIBPTHREAD 1)
endif()

# configure files where variables should be replaced.
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/config.h)

# specify include directories
include_directories(${CMAKE_CURRENT_BINARY_DIR}/include
                    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# consider all *.ccp files found to be actual code files
file(GLOB_RECURSE CODE_FILES *.cpp)

# specify that we are creating a shared and static library at the
# same time
if(STATIC_BUILD)
  add_library(${CMAKE_PROJECT_NAME}-static STATIC ${CODE_FILES})

  set_target_properties(${CMAKE_PROJECT_NAME}-static PROPERTIES OUTPUT_NAME rtdebug 
                                                                VERSION ${PROJECT_VERSION} 
                                                                SOVERSION ${PROJECT_VERSION_MAJOR})

  # define link libraries dependencies
  target_link_libraries(${CMAKE_PROJECT_NAME}-static)

  # definition of install targets
  install(TARGETS ${CMAKE_PROJECT_NAME}-static
          ARCHIVE DESTINATION lib
          LIBRARY DESTINATION lib
          RUNTIME DESTINATION bin
          COMPONENT library
  )
endif()

if(SHARED_BUILD)
  add_library(${CMAKE_PROJECT_NAME}-shared SHARED ${CODE_FILES})

  set_target_properties(${CMAKE_PROJECT_NAME}-shared PROPERTIES OUTPUT_NAME rtdebug
                                                                VERSION ${PROJECT_VERSION} 
                                                                SOVERSION ${PROJECT_VERSION_MAJOR})

  # define link libraries dependencies
  target_link_libraries(${CMAKE_PROJECT_NAME}-shared)

  install(TARGETS ${CMAKE_PROJECT_NAME}-shared
          ARCHIVE DESTINATION lib
          LIBRARY DESTINATION lib
          RUNTIME DESTINATION bin
          COMPONENT library
  )
endif()

install(FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/rtdebug.h
              ${CMAKE_CURRENT_SOURCE_DIR}/CRTDebug.h
              DESTINATION include/rtdebug
)
