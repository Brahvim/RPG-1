cmake_minimum_required(VERSION 3.15)

add_library(
  Sml #
  OBJECT #
  "vec2.c" #
  "vec3.c" #
  "quat.c" #
  "mat44.c" #
  "mat33.c" #
  "mat22.c" #
  "generic.c" #
)
target_link_libraries(
  Sml #
  m # GCC math library (`math.h`!).
)
target_compile_options(
  Sml #
  PRIVATE #
          "-O3" #
          "-Wall" #
          "-ffast-math" #
          "-march=native" #
          "-funroll-loops" #
          "-ftree-vectorize" #
          "-Wno-missing-braces" #
          "-Wno-unknown-pragmas" #
          # "-msve-vector-bits=256" # Worked on Termux! #
          # "-fopt-info-vec-optimized" # Optimizations logs. #
          "-mprefer-vector-width=256" #
          "-funsafe-math-optimizations" #
          #
)
subdirs("./test")
