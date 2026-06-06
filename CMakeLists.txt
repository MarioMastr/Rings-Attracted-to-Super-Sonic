cmake_minimum_required(VERSION 3.10)

project(RingsAttractedToSuperSonic)

set(MOD_NAME RingsAttractedToSuperSonic CACHE STRING "The mod directory to look into")
set(OUTPUT_NAME "RingsAttractedToSuperSonic" CACHE STRING "The name of the built library")

set(RETRO_REVISION 2 CACHE STRING "What revision to compile for. Defaults to Origins = 3")
set(RETRO_MOD_LOADER_VER 3 CACHE STRING "Sets the mod loader version. Defaults to latest")
set(GAME_VERSION 6 CACHE STRING "The game version to use. Defaults to 6 == Last Steam release")

option(MANIA_FIRST_RELEASE "Whether or not to build Mania's first release. Defaults to false" OFF)
if(MANIA_FIRST_RELEASE)
    set(MANIA_PREPLUS ON)
    set(RETRO_REVISION 1)
    set(GAME_VERSION 0)
else()
    option(MANIA_PREPLUS "Whether or not to build Mania pre-plus. Defaults to false" OFF)
    if(MANIA_PREPLUS)
        set(RETRO_REVISION 1)
        set(GAME_VERSION 3)
    endif()
endif()

option(MOD_INCLUDE_EDITOR "Whether or not to include editor functions. Defaults to true" ON)
option(MOD_INCREMENTAL_BUILD "Whether or not to build all objects separately (for quicker dev-->build iterations). Defaults to false." OFF)

find_path(GAMEAPI
  NAMES
    C
    CPP
  PATHS
    .
    ..
  PATH_SUFFIXES
    GameAPI
    RSDKv5-GameAPI
  NO_DEFAULT_PATH
  NO_CMAKE_FIND_ROOT_PATH
)

if(GAMEAPI)
  message(STATUS "Found GameAPI for ${MOD_NAME}: ${GAMEAPI}")
else()
  message(FATAL_ERROR "GameAPI not found for ${MOD_NAME}. Clone it in the mod's folder.")
endif()

if(MOD_INCREMENTAL_BUILD)
    include(cmake/Objects.cmake)
    set(MOD_SOURCES
        ${GAMEAPI}/C/GameAPI/Game.c
        src/dllmain.c
        ${GENERATED_SOURCES}
    )
else()
    set(MOD_SOURCES
        ${GAMEAPI}/C/GameAPI/Game.c
        src/dllmain.c
        src/Objects/All.c
    )
endif()

add_library(${PROJECT_NAME} SHARED ${MOD_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    src/
    src/Objects/
    ${GAMEAPI}/C/GameAPI/
)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

if(ANDROID)
    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "lib")
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
	RETRO_REVISION=${RETRO_REVISION}
	RETRO_USE_MOD_LOADER=1
	RETRO_MOD_LOADER_VER=${RETRO_MOD_LOADER_VER}
	RETRO_INCLUDE_EDITOR=$<BOOL:${MOD_INCLUDE_EDITOR}>
	MANIA_PREPLUS=$<BOOL:${MANIA_PREPLUS}>
	MANIA_FIRST_RELEASE=$<BOOL:${MANIA_FIRST_RELEASE}>
	GAME_VERSION=${GAME_VERSION}
	GAME_TYPE=1
)
    
unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)
