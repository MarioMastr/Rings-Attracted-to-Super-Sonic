cmake_minimum_required(VERSION 3.7)

project(Rings Attracted to Super Sonic)
set(MOD_NAME Rings Attracted to Super Sonic CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "Rings Attracted to Super Sonic" CACHE STRING "The name of the built library")

add_library(Rings Attracted to Super Sonic SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Player.c
)

target_include_directories(Rings Attracted to Super Sonic PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(Rings Attracted to Super Sonic PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)