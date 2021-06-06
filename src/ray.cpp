#include "ray.hpp"

namespace WaveStrider {

vec3 Ray::advance(double amount)
{
  distance += amount;
  point = origin + (direction * distance);
  return point;
};

void Ray::reset(vec3 dir)
{
  direction = dir;
  distance = 0;
  point = origin;
};

}// namespace WaveStrider