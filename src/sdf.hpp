#pragma once

#include <functional>

#include "vec3.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "sdfResult.hpp"

namespace WaveStrider {

struct SDFObject {
  IMaterial* m;
  vec3 position;
  virtual SDFResult getDistanceResult(vec3 p) = 0;

  virtual ~SDFObject() {};
};

namespace SDF {
  SDFResult Union(SDFResult a, SDFResult b);
  SDFResult Intersection(SDFResult a, SDFResult b);
  SDFResult Difference(SDFResult a, SDFResult b);
}

};
