cmake_minimum_required(VERSION 3.25.1)
project(RpgGame1)

find_package(glfw3 REQUIRED)
find_package(OpenAL REQUIRED)
# find_package(OpenGL REQUIRED)

include_directories("include")
add_executable(
  RpgGame1
  "stb/stb_vorbis.c" #
  "stb/stb_image.c" #
  "glad.c" #
  #
  "window1.c" #
  "main.c" #
)
target_link_libraries(
  RpgGame1 #
  m #
  # OpenGL::GL
  OpenAL::OpenAL #
  /usr/lib/x86_64-linux-gnu/libglfw.so #
)
