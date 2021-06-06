#include "./canvas.hpp"
#include "./ppm.hpp"
#include <iostream>

namespace WaveStrider {

Canvas::Canvas(uint32_t w, uint32_t h) : width{ w }, height{ h }
{
  data = std::vector<vec3>(w * h);
};

void Canvas::put(uint32_t x, uint32_t y, vec3 color)
{
  data[y * width + x] = color;
};

bool Canvas::write(std::string filename)
{
  return PPM::write(filename, width, height, data);
};

};// namespace WaveStrider
