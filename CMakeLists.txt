cmake_minimum_required(VERSION 3.31.6)
project(Rpg1)

set(CMAKE_C_FLAGS
    "${CMAKE_C_FLAGS}\
	-O0\
	-g\
	")
set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

file(GLOB SRC_LIST "./src/List/*.c")
file(GLOB SRC_MAIN "./src/*.c")

include_directories("./include")
find_package(glfw3 REQUIRED)
subdirs("tests/List")

add_executable(
  Rpg1 #
  ${SRC_LIST} #
  ${SRC_MAIN} #
)

set_target_properties(Rpg1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                                      ${CMAKE_SOURCE_DIR})

target_link_libraries(
  Rpg1 #
  m #
  glfw #
  ${CMAKE_SOURCE_DIR}/libs/libSimpleMathLibrary.so #
)
