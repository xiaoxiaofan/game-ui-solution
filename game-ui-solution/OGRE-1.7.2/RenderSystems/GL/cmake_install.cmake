# Install script for directory: F:/ogre_src_v1-7-2/RenderSystems/GL

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
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Release/opt" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/Release/RenderSystem_GL.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Release" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/Release/RenderSystem_GL.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/RelWithDebInfo/opt" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/RelWithDebInfo/RenderSystem_GL.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/RelWithDebInfo" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/RelWithDebInfo/RenderSystem_GL.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/MinSizeRel/opt" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/MinSizeRel/RenderSystem_GL.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/MinSizeRel" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/MinSizeRel/RenderSystem_GL.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Debug/opt" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/Debug/RenderSystem_GL_d.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Debug" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/Debug/RenderSystem_GL_d.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/RenderSystems/GL" TYPE FILE FILES
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLATIFSInit.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLContext.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLDefaultHardwareBufferManager.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLFBOMultiRenderTarget.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLFBORenderTexture.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLFrameBufferObject.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLGpuNvparseProgram.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLGpuProgram.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLGpuProgramManager.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLHardwareBufferManager.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLHardwareIndexBuffer.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLHardwareOcclusionQuery.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLHardwarePixelBuffer.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLHardwareVertexBuffer.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLPBRenderTexture.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLPBuffer.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLPixelFormat.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLPlugin.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLPrerequisites.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLRenderSystem.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLRenderTexture.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLRenderToVertexBuffer.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLSupport.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLTexture.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreGLTextureManager.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/RenderSystems/GL" TYPE FILE FILES
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreWin32Context.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreWin32GLSupport.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreWin32Prerequisites.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreWin32RenderTexture.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/include/OgreWin32Window.h"
    "F:/ogre_src_v1-7-2/RenderSystems/GL/src/win32/OgreGLUtil.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/RenderSystems/GL" TYPE DIRECTORY FILES "F:/ogre_src_v1-7-2/RenderSystems/GL/include/GL")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/RenderSystems/GL" TYPE DIRECTORY FILES "F:/ogre_src_v1-7-2/RenderSystems/GL/src/GLSL/include/")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

