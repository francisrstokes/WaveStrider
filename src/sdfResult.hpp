#pragma once

#include "vec3.hpp"
#include "ray.hpp"

namespace WaveStrider {

struct SDFObject;

struct SDFResult {
  double distance;
  const SDFObject* obj;
  vec3 position;

  SDFResult(double d, const SDFObject* o, vec3 pos)
    : distance{d}, obj{o}, position{pos} {};

  SDFResult()
    : distance{std::numeric_limits<double>::infinity()},
      obj{nullptr},
      position {vec3()} {};
};

};
