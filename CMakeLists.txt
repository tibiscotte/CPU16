cmake_minimum_required(VERSION 3.16)

project(CPU16 LANGUAGES CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# SDL2
find_package(SDL2 REQUIRED)

# Dossiers d'inclusion
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Recherche automatique des fichiers sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    src/*.cpp
)

# Exécutable principal
add_executable(cpu16 ${SOURCES})

target_include_directories(cpu16 PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link SDL2
target_link_libraries(cpu16 PRIVATE
    ${SDL2_LIBRARIES}
)