cmake_minimum_required(VERSION 3.5)
project(list_logo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -DGLM_FORCE_RADIANS")

set(SOURCE_FILES source/main.cpp source/tdogl/Bitmap.cpp source/tdogl/Bitmap.h source/tdogl/Camera.cpp source/tdogl/Camera.h source/tdogl/Program.cpp source/tdogl/Program.h source/tdogl/Shader.cpp source/tdogl/Shader.h source/tdogl/Texture.cpp source/tdogl/Texture.h common/platform.hpp common/platform_linux.cpp thirdparty/std_image/stb_image.h source/tdogl/Bitmap.cpp source/tdogl/Bitmap.h source/tdogl/Model.h  source/tdogl/render.h source/tdogl/logo.cpp source/tdogl/logo.h source/tdogl/List_logo.cpp source/tdogl/List_logo.h source/tdogl/ultility.h)

include_directories (thirdparty/std_image)
include_directories (common)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/kienlb/ClionProjects/list_logo/")

add_executable(list_logo ${SOURCE_FILES})

target_link_libraries(list_logo GL GLU GLEW glfw)


