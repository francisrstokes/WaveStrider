#include <assert.h>
#include <math.h>
#include "./ppm.hpp"

uint32_t clamp(uint32_t vMin, uint32_t vMax, double v) {
  if (v < vMin) return vMin;
  if (v > vMax) return vMax;
  return (uint32_t)v;
};

bool WaveStrider::PPM::write(std::string filename, uint32_t width, uint32_t height, std::vector<WaveStrider::vec3> data) {
  assert(data.size() == width * height);

  std::fstream file_out;
  file_out.open(filename, std::ios_base::out);
  if (!file_out.is_open()) {
    return false;
  }

  file_out << "P3\n" << width << " " << height << "\n255\n";

  for (vec3 color : data) {
    file_out << clamp(0, 255, color.x)
             << " "
             << clamp(0, 255, color.y)
             << " "
             << clamp(0, 255, color.z)
             << " ";
  }

  file_out.close();

  return true;
};