#include <iostream>
#include <vector>
#include "ppm.hpp"
#include "vec3.hpp"

int main() {
  std::vector<WaveStrider::vec3> data;

  for (int y = 0; y < 255; y++) {
    for (int x = 0; x < 255; x++) {
      auto c = WaveStrider::vec3{(double)x, (double)y, (double)(x ^ y)};
      data.push_back(c);
    }
  }

  WaveStrider::PPM::write(
    "test.ppm",
    255, 255,
    data
  );

  return 0;
}
