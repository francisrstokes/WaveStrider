add_executable(WaveStrider
  main.cpp
  ppm.cpp
  canvas.cpp
  sdf.cpp
  ray.cpp
  vec3.cpp)

target_link_libraries(
  WaveStrider
  PRIVATE project_options
          project_warnings)
