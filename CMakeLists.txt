cmake_minimum_required(VERSION 3.25.1)
project(Rpg1)

# -march=native\
set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS}\
	-O3\
	-ffast-math\
	-funroll-loops\
	-ftree-vectorize\
	-fopt-info-vec-optimized\
	")

find_package(glfw3 REQUIRED)
find_package(OpenAL REQUIRED)

include_directories("include")
add_executable(
  Rpg1
  "stb/stb_vorbis.c" #
  "stb/stb_image.c" #
  "glad.c" #
  # My own:
  "graphics.c" #
  "window1.c" #
  "quads.c" #
  "main.c" #
)
target_link_libraries(
  Rpg1 #
  m #
  # OpenGL::GL
  OpenAL::OpenAL #
  /usr/lib/x86_64-linux-gnu/libglfw.so #
  # My own:
  ${CMAKE_SOURCE_DIR}/libs/libSimpleMathLibrary.so #
)
