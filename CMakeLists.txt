cmake_minimum_required(VERSION 3.25.1)
project(Rpg1)

find_package(glfw3 REQUIRED)
find_package(OpenAL REQUIRED)

include_directories("include")
file(GLOB SOURCES *.c stb/*.c tests/list/difficult.c)

list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/quads.c")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
add_executable(Rpg1 ${SOURCES} ${HEADERS})

target_link_libraries(
  Rpg1 #
  m # GCC libm for `math.h`.
  OpenAL::OpenAL # OpenAL, because why not?!
  /usr/lib/x86_64-linux-gnu/libglfw.so.3 # GLFW 3 for its stuff...
  ${CMAKE_SOURCE_DIR}/libs/libSimpleMathLibrary.so # SML, my Math library!
)
