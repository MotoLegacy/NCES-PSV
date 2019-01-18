cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

OPTION(DEFINE_DEBUG
  "Build the project using debugging code"
  OFF)
IF(DEFINE_DEBUG)
  MESSAGE("Adding Debug flag...")
  ADD_DEFINITIONS(-DDEFINE_DEBUG)
  #SET(CMAKE_BUILD_TYPE Debug)
  MESSAGE("Build type is " ${CMAKE_BUILD_TYPE})
ENDIF(DEFINE_DEBUG)


set(SHORT_NAME NCESPSV)
project(${SHORT_NAME})
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "NCESPSV")
set(VITA_TITLEID  "NCESPSV01")
set(VITA_VERSION  "02.50")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -std=gnu14 -Wall ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -Wall ")


include_directories(
  ../common
)

add_executable(${SHORT_NAME}.elf
../../src/main.cpp
../../src/game.cpp
../../src/graphics.cpp
../../src/inputHelper.cpp
../../src/collisionHelper.cpp
../../src/functions.cpp
../../src/nicCage.cpp
../../src/chicken.cpp
../../src/collide.cpp
../../src/celery.cpp
)

target_link_libraries(${SHORT_NAME}.elf


  debugnet
  vita2d
  soloud
  pthread
  ScePgf_stub
  ScePvf_stub
  SceGxm_stub
  SceCtrl_stub
  SceTouch_stub
  SceAppUtil_stub
  SceDisplay_stub
  SceLibKernel_stub
  SceSysmodule_stub
  ScePower_stub
  SceCommonDialog_stub
  SceRegistryMgr_stub
  SceHid_stub
  freetype
  png
  jpeg
  z
  m
  SceAudio_stub
)


vita_create_self(${SHORT_NAME}.self ${SHORT_NAME}.elf)

vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}

  FILE ../gfx/celery.png gfx/celery.png
  FILE ../gfx/chicken.png gfx/chicken.png
  FILE ../gfx/NicCageFace.png gfx/NicCageFace.png
  FILE ../gfx/NicCageFaceTranslucent.png gfx/NicCageFaceTranslucent.png

  FILE sce_sys/icon0.png sce_sys/icon0.png
  FILE sce_sys/pic0.png sce_sys/pic0.png
  FILE sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
  FILE sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
  FILE sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)