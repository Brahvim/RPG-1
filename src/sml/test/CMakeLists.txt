cmake_minimum_required(VERSION 3.15)

macro(Test p_binary p_file)
  add_executable(${p_binary} ${p_file})
  target_link_libraries(${p_binary} PRIVATE Sml)
endmacro()

file(GLOB SRC_SML_TEST "./test/**.c")

test(SmlTestVec2 "vec2.c")
test(SmlTestVec3 "vec3.c")
test(SmlTestQuat "quat.c")
test(SmlTestMat22 "mat22.c")
test(SmlTestMat33 "mat33.c")
test(SmlTestMat44 "mat44.c")
test(SmlTestGeneric "generic.c")
