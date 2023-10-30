cmake_minimum_required(VERSION 3.7)

project(RingsAttractedToSuperSonic)
set(MOD_NAME RingsAttractedToSuperSonic CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "RingsAttractedToSuperSonic" CACHE STRING "The name of the built library")

add_library(RingsAttractedToSuperSonic SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Ring.c
)

target_include_directories(RingsAttractedToSuperSonic PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(RingsAttractedToSuperSonic PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})
set_target_properties(RingsAttractedToSuperSonic PROPERTIES PREFIX "")

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)