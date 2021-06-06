#pragma once

#include "vec3.hpp"

namespace WaveStrider {

struct Ray
{

public:
  vec3 origin;
  vec3 direction;
  vec3 point;
  double distance;


  Ray(vec3 o, vec3 d) : origin{ o }, direction{ d }, point{ vec3(o) } {};

  Ray() : origin{ vec3() }, direction{ vec3() }, point{ vec3() } {};

  ~Ray(){};

  vec3 advance(double amount);
  void reset(vec3 direction);
};

}// namespace WaveStrider