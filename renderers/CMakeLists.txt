add_library(Renderers console_renderer.cpp)

target_include_directories(Renderers
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)
