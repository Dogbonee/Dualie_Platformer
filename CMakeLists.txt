cmake_minimum_required(VERSION 3.28)
project(Dualie_Platformer)
set(CMAKE_CXX_STANDARD 17)
find_package(Dualie REQUIRED)

add_executable(${PROJECT_NAME} main.cpp
        src/Game.cpp
        include/Game.h
        src/Scene.cpp
        include/Scene.h
        src/PlatformerScene.cpp
        include/PlatformerScene.h
        src/Player.cpp
        include/Player.h
        include/Settings.h
)
include_directories(include)
target_link_libraries(${PROJECT_NAME} ${DUALIE_LIBRARY})
target_compile_options(${PROJECT_NAME} PRIVATE
        -g -O2 -Wall
)
ctr_generate_smdh(${PROJECT_NAME}.smdh
        NAME "${PROJECT_NAME}"
        DESCRIPTION "v1.0.0"
        AUTHOR "Dogbonee"
)
ctr_create_3dsx(${PROJECT_NAME}
        SMDH ${PROJECT_NAME}.smdh
        ROMFS romfs
)