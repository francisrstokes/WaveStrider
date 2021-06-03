#pragma once

#include "vec3.hpp"
#include "ray.hpp"

namespace WaveStrider {

struct SDFObject;

struct SDFResult {
  double distance;
  const SDFObject* obj;
  Ray* ray;
  vec3 position;

  SDFResult(double d, const SDFObject* o, Ray* r)
    : distance{d}, obj{o}, ray{r}, position{vec3(r->point)} {};

  SDFResult(double d, const SDFObject* o, vec3 pos)
    : distance{d}, obj{o}, ray{nullptr}, position{pos} {};

  SDFResult()
    : distance{std::numeric_limits<double>::infinity()},
      obj{nullptr},
      ray{nullptr},
      position {vec3()} {};
};

};
