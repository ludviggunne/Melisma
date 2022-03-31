
project(Melisma)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME}

  src/application.cpp
  src/window.cpp

  src/input/input.cpp

  src/layer/layer.cpp
  src/layer/layer_stack.cpp

  src/rendering/camera.cpp
  src/rendering/glcall.cpp
  src/rendering/glcall.h
  src/rendering/index_buffer.cpp
  src/rendering/renderer2D.cpp
  src/rendering/shader_program.cpp
  src/rendering/texture.cpp
  src/rendering/vertex_array_object.cpp
  src/rendering/vertex_buffer_layout.cpp
  src/rendering/vertex_buffer.cpp

  dependencies/glad/src/glad.c
  dependencies/stbi/stb_impl.cpp

)

target_include_directories(${PROJECT_NAME}

PUBLIC
  include
  dependencies/glm

PRIVATE
  dependencies/glad/include
  dependencies/stbi/include
  dependencies/glfw/include

)

add_subdirectory(dependencies/glfw)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw)