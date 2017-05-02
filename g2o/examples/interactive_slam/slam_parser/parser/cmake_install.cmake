# Install script for directory: /home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/interactive_slam/slam_parser/parser

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libg2o_parser.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/home/rodrigocoelho/Área de Trabalho/g2o-master/lib/libg2o_parser.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libg2o_parser.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/slam_parser/parser/FlexLexer.h;/usr/local/include/slam_parser/parser/scanner.h;/usr/local/include/slam_parser/parser/bison_parser.h;/usr/local/include/slam_parser/parser/slam_context.h;/usr/local/include/slam_parser/parser/driver.h;/usr/local/include/slam_parser/parser/commands.h;/usr/local/include/slam_parser/parser/location.hh;/usr/local/include/slam_parser/parser/stack.hh;/usr/local/include/slam_parser/parser/position.hh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/usr/local/include/slam_parser/parser" TYPE FILE FILES
    "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/interactive_slam/slam_parser/parser/FlexLexer.h"
    "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/interactive_slam/slam_parser/parser/scanner.h"
    "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/interactive_slam/slam_parser/parser/bison_parser.h"
    "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/interactive_slam/slam_parser/parser/slam_context.h"
    "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/interactive_slam/slam_parser/parser/driver.h"
    "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/interactive_slam/slam_parser/parser/commands.h"
    "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/interactive_slam/slam_parser/parser/location.hh"
    "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/interactive_slam/slam_parser/parser/stack.hh"
    "/home/rodrigocoelho/Área de Trabalho/g2o-master/g2o/examples/interactive_slam/slam_parser/parser/position.hh"
    )
endif()

