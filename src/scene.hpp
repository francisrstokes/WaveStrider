#pragma once

#include <vector>
#include "sdfResult.hpp"
#include "ray.hpp"
#include "light.hpp"

namespace WaveStrider {

struct Scene
{
  virtual ~Scene(){};
  virtual SDFResult getDistanceResult(vec3 p) = 0;
  virtual std::vector<ILight *> getLights() = 0;
};

}// namespace WaveStrider
