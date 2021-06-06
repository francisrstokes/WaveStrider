#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include "vec3.hpp"

namespace WaveStrider {
namespace PPM {

  bool write(std::string filename, uint32_t width, uint32_t height, std::vector<vec3> data);

}
}// namespace WaveStrider
