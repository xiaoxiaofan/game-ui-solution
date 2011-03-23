# Install script for directory: F:/ogre_src_v1-7-2/OgreMain

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
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Release" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/Release/OgreMain.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Release" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/Release/OgreMain.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/RelWithDebInfo" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/RelWithDebInfo/OgreMain.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/RelWithDebInfo" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/RelWithDebInfo/OgreMain.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/MinSizeRel" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/MinSizeRel/OgreMain.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/MinSizeRel" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/MinSizeRel/OgreMain.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Debug" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/ogre_src_v1-7-2/lib/Debug/OgreMain_d.lib")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  IF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin/Debug" TYPE SHARED_LIBRARY FILES "F:/ogre_src_v1-7-2/bin/Debug/OgreMain_d.dll")
  ENDIF("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE" TYPE FILE FILES
    "F:/ogre_src_v1-7-2/OgreMain/include/asm_math.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/Ogre.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreAlignedAllocator.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreAnimable.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreAnimation.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreAnimationState.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreAnimationTrack.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreAny.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreArchive.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreArchiveFactory.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreArchiveManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreAtomicWrappers.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreAutoParamDataSource.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreAxisAlignedBox.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreBillboard.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreBillboardChain.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreBillboardParticleRenderer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreBillboardSet.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreBitwise.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreBlendMode.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreBone.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreBorderPanelOverlayElement.h"
    "F:/ogre_src_v1-7-2/include/OgreBuildSettings.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCamera.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCodec.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreColourValue.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCommon.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCompositionPass.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCompositionTargetPass.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCompositionTechnique.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCompositor.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCompositorChain.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCompositorLogic.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCompositorInstance.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCompositorManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreConfig.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreConfigDialog.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreConfigFile.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreConfigOptionMap.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreController.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreControllerManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreConvexBody.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreCustomCompositionPass.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreDataStream.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreDefaultHardwareBufferManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreDistanceLodStrategy.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreDynLib.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreDynLibManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreEdgeListBuilder.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreEntity.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreErrorDialog.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreException.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreExternalTextureSource.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreExternalTextureSourceManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreFactoryObj.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreFileSystem.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreFont.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreFontManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreFrameListener.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreFrustum.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreGpuProgram.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreGpuProgramManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreGpuProgramParams.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreGpuProgramUsage.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreHardwareBuffer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreHardwareBufferManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreHardwareIndexBuffer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreHardwareOcclusionQuery.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreHardwarePixelBuffer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreHardwareVertexBuffer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreHeaderPrefix.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreHeaderSuffix.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreHighLevelGpuProgram.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreHighLevelGpuProgramManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreImage.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreImageCodec.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreInstancedGeometry.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreIteratorRange.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreIteratorWrapper.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreIteratorWrappers.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreKeyFrame.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreLight.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreLodListener.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreLodStrategy.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreLodStrategyManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreLog.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreLogManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreManualObject.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMaterial.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMaterialManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMaterialSerializer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMath.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMatrix3.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMatrix4.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMemoryAllocatedObject.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMemoryAllocatorConfig.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMemoryNedAlloc.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMemoryNedPooling.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMemoryStdAlloc.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMemorySTLAllocator.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMemoryTracker.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMesh.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMeshFileFormat.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMeshManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMeshSerializer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMeshSerializerImpl.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMovableObject.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreMovablePlane.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreNode.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreNumerics.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreOptimisedUtil.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreOverlay.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreOverlayContainer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreOverlayElement.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreOverlayElementCommands.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreOverlayElementFactory.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreOverlayManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePanelOverlayElement.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticle.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticleAffector.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticleAffectorFactory.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticleEmitter.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticleEmitterCommands.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticleEmitterFactory.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticleIterator.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticleScriptCompiler.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticleSystem.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticleSystemManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreParticleSystemRenderer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePass.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePatchMesh.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePatchSurface.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePixelCountLodStrategy.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePixelFormat.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePlane.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePlaneBoundedVolume.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePlatform.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePlatformInformation.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePlugin.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePolygon.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePose.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePredefinedControllers.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePrefabFactory.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgrePrerequisites.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreProfiler.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreProgressiveMesh.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreQuaternion.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRadixSort.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRay.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRectangle.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRectangle2D.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderable.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderObjectListener.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderOperation.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderQueue.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderQueueInvocation.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderQueueListener.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderQueueSortingGrouping.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderSystem.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderSystemCapabilities.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderSystemCapabilitiesManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderSystemCapabilitiesSerializer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderTarget.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderTargetListener.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderTexture.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderToVertexBuffer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRenderWindow.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreResource.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreResourceBackgroundQueue.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreResourceGroupManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreResourceManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRibbonTrail.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRoot.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreRotationalSpline.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSceneManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSceneManagerEnumerator.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSceneNode.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSceneQuery.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreScriptCompiler.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreScriptLexer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreScriptLoader.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreScriptParser.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreScriptTranslator.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSearchOps.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSerializer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreShadowCameraSetup.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreShadowCameraSetupFocused.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreShadowCameraSetupLiSPSM.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreShadowCameraSetupPlaneOptimal.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreShadowCameraSetupPSSM.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreShadowCaster.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreShadowTextureManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreShadowVolumeExtrudeProgram.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSharedPtr.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSimpleRenderable.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSimpleSpline.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSingleton.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSkeleton.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSkeletonFileFormat.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSkeletonInstance.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSkeletonManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSkeletonSerializer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSphere.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSpotShadowFadePng.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreStableHeaders.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreStaticFaceGroup.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreStaticGeometry.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreStdHeaders.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreStreamSerialiser.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreString.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreStringConverter.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreStringInterface.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreStringVector.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSubEntity.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreSubMesh.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreTagPoint.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreTangentSpaceCalc.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreTechnique.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreTextAreaOverlayElement.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreTexture.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreTextureManager.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreTextureUnitState.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreTimer.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreUnifiedHighLevelGpuProgram.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreUserObjectBindings.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreUTFString.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreVector2.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreVector3.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreVector4.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreVertexBoneAssignment.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreVertexIndexData.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreViewport.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreWindowEventUtilities.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreWireBoundingBox.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreWorkQueue.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreFreeImageCodec.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreDDSCodec.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/OgreZip.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/WIN32" TYPE FILE FILES
    "F:/ogre_src_v1-7-2/OgreMain/include/WIN32/OgreConfigDialogImp.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/WIN32/OgreErrorDialogImp.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/WIN32/OgreTimerImp.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/WIN32/OgreMinGWSupport.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/OGRE/Threading" TYPE FILE FILES
    "F:/ogre_src_v1-7-2/OgreMain/include/Threading/OgreThreadDefines.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/Threading/OgreThreadHeaders.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/Threading/OgreDefaultWorkQueue.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/Threading/OgreThreadDefinesBoost.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/Threading/OgreThreadHeadersBoost.h"
    "F:/ogre_src_v1-7-2/OgreMain/include/Threading/OgreDefaultWorkQueueStandard.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

