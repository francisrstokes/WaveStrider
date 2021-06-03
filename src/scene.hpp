#pragma once

#include "sdfResult.hpp"
#include "ray.hpp"

namespace WaveStrider {

struct Scene {
  virtual ~Scene() {};
  virtual SDFResult getDistanceResult(Ray* ray) = 0;
  virtual SDFResult getDistanceResult(vec3 p) = 0;
};

}
