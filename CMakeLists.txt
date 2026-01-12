cmake_minimum_required(VERSION 3.10)

project(OpenGL LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# src altındaki tüm .cpp ve .c dosyalarını topla
file(GLOB_RECURSE SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/core/*.cpp
    ${CMAKE_SOURCE_DIR}/src/util/*.cpp
    ${CMAKE_SOURCE_DIR}/src/third_party/*.cpp
    ${CMAKE_SOURCE_DIR}/src/graphics/*.cpp
    ${CMAKE_SOURCE_DIR}/src/*.c
)

add_executable(OpenGL ${SOURCE_FILES})

# src ve alt klasörlerini include et
target_include_directories(OpenGL PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/core
    ${CMAKE_SOURCE_DIR}/src/graphics
    ${CMAKE_SOURCE_DIR}/src/third_party
    ${CMAKE_SOURCE_DIR}/src/util
)

# Lib dizini
target_link_directories(OpenGL PRIVATE
    ${CMAKE_SOURCE_DIR}/lib
)

# Link
target_link_libraries(OpenGL
    glfw3
    opengl32
)

# Output bin/
set_target_properties(OpenGL PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)
