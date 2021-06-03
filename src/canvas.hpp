#pragma once

#include <cstdint>
#include <vector>
#include "./vec3.hpp"

namespace WaveStrider {

struct Canvas {
  uint32_t width;
  uint32_t height;
  std::vector<vec3> data;

  Canvas(uint32_t w, uint32_t h);

  void put(uint32_t x, uint32_t y, const vec3 color);

  bool write(std::string filename);
};

};

