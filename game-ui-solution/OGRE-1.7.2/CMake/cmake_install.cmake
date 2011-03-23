# Install script for directory: F:/ogre_src_v1-7-2/CMake

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "F:/ogre_src_v1-7-2/sdk")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/CMake" TYPE FILE FILES
    "F:/ogre_src_v1-7-2/CMake/Packages/FindOIS.cmake"
    "F:/ogre_src_v1-7-2/CMake/Packages/FindOGRE.cmake"
    "F:/ogre_src_v1-7-2/CMake/Utils/FindPkgMacros.cmake"
    "F:/ogre_src_v1-7-2/CMake/Utils/MacroLogFeature.cmake"
    "F:/ogre_src_v1-7-2/CMake/Utils/PreprocessorUtils.cmake"
    "F:/ogre_src_v1-7-2/CMake/Utils/OgreConfigTargets.cmake"
    "F:/ogre_src_v1-7-2/CMake/Utils/OgreGetVersion.cmake"
    "F:/ogre_src_v1-7-2/CMake/Utils/OgreFindFrameworks.cmake"
    "F:/ogre_src_v1-7-2/CMake/Templates/VisualStudioUserFile.vcproj.user.in"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

