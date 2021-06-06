#include <assert.h>
#include <math.h>
#include <string.h>
#include "./ppm.hpp"

uint8_t clamp(uint8_t vMin, uint8_t vMax, double v)
{
  if (v < vMin) return vMin;
  if (v > vMax) return vMax;
  return (uint8_t)(round(v));
};

bool WaveStrider::PPM::write(std::string filename, uint32_t width, uint32_t height, std::vector<WaveStrider::vec3> data)
{
  assert(data.size() == width * height);

  std::ofstream f(filename, std::ofstream::binary);
  if (!f.is_open()) {
    return false;
  }

  f.write("P6\n", 3);
  f.write(std::to_string(width).c_str(), std::to_string(width).length());
  f.write(" ", 1);
  f.write(std::to_string(height).c_str(), std::to_string(height).length());
  f.write("\n255\n", 5);

  char tmp;
  for (vec3 color : data) {
    tmp = clamp(0, 255, color.x * 255.0);
    f.write(&tmp, 1);
    tmp = clamp(0, 255, color.y * 255.0);
    f.write(&tmp, 1);
    tmp = clamp(0, 255, color.z * 255.0);
    f.write(&tmp, 1);
  }

  f.close();

  return true;
};