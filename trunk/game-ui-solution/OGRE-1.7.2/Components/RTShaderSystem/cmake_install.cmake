# Install script for directory: F:/ogre_src_v1-7-2/Components/RTShaderSystem

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
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Release" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/Release/OgreRTShaderSystem.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Release" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/Release/OgreRTShaderSystem.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/RelWithDebInfo" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/RelWithDebInfo/OgreRTShaderSystem.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/RelWithDebInfo" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/RelWithDebInfo/OgreRTShaderSystem.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/MinSizeRel" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/MinSizeRel/OgreRTShaderSystem.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/MinSizeRel" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/MinSizeRel/OgreRTShaderSystem.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Debug" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/Debug/OgreRTShaderSystem_d.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Debug" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/Debug/OgreRTShaderSystem_d.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/RTShaderSystem" TYPE FILE FILES
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreRTShaderSystem.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderPrerequisites.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderFFPColour.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderFFPFog.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderFFPLighting.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderFFPRenderState.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderFFPRenderStateBuilder.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderFFPTexturing.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderFFPTransform.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderFunction.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderFunctionAtom.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderGenerator.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderParameter.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderProgram.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderProgramManager.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderProgramSet.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderProgramWriter.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderRenderState.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderSubRenderState.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderExNormalMapLighting.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderExPerPixelLighting.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderExIntegratedPSSM3.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderScriptTranslator.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderMaterialSerializerListener.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderProgramProcessor.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderCGProgramProcessor.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderCGProgramWriter.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderGLSLProgramProcessor.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderGLSLProgramWriter.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderProgramWriterManager.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderHLSLProgramProcessor.h"
    "F:/ogre_src_v1-7-2/Components/RTShaderSystem/include/OgreShaderHLSLProgramWriter.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

