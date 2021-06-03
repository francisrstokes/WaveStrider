#pragma once

#include "vec3.hpp"

namespace WaveStrider {

struct IMaterial {
  virtual vec3 getColor() = 0;
  virtual ~IMaterial() {};
};

};
