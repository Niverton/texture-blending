cmake_minimum_required(VERSION 3.10)

project("texture_blending")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(OUT blending)

set(SRC
  blending/main.cpp
  blending/viewer.cpp
  blending/quad.cpp
  blending/shader.cpp
  blending/shader_program.cpp
  blending/opengl.cpp
  )


add_executable(${OUT} ${SRC})

target_compile_features(${OUT} PRIVATE cxx_std_17)

find_package(SFML REQUIRED COMPONENTS system graphics window)
find_package(OpenGL REQUIRED COMPONENTS OpenGL)
find_package(GLEW REQUIRED)

target_link_libraries(${OUT} PRIVATE
  OpenGL::GL
  GLEW::GLEW)

if (TARGET sfml-system)
  target_link_libraries(${OUT} PRIVATE
    sfml-system sfml-graphics sfml-window)
else()
  target_link_libraries(${OUT} PRIVATE ${SFML_LIBRARIES})
  target_include_directories(${OUT} PRIVATE ${SFML_INCLUDE_DIR})
endif()
