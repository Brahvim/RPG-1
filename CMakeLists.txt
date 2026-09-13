cmake_minimum_required(VERSION 3.31.6)
project(Rpg1)

set(CMAKE_EXPORT_COMPILE_COMMANDS true)
include_directories("./src/sss/")
include_directories("./include")

add_subdirectory("./src/sml")
add_subdirectory("./src/sss")

file(GLOB SRC_MAIN "./src/**.c")
find_package(glfw3 REQUIRED)

set(CMAKE_C_STANDARD 23)

add_executable(
  Rpg1 #
  ${SRC_MAIN} #
)
set_target_properties(
  Rpg1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR} #
)
target_link_libraries(
  Rpg1 #
  PRIVATE #
          glfw #
          Sml #
          Sss #
          m #
)
target_link_libraries(
  Rpg1 #
  PRIVATE #
          glfw #
          Sml #
          m #
)
