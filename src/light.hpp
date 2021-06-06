#pragma once

#include "vec3.hpp"

namespace WaveStrider {

enum class LightType {
  Directional
};

struct ILight
{
  LightType type;
  vec3 color;
  double intensity;
  virtual vec3 getDirection() = 0;
  virtual ~ILight(){};

protected:
  ILight(LightType t, vec3 c, double i) : type{ t }, color{ c }, intensity{ i } {};
};

struct DirectionalLight : ILight
{
public:
  DirectionalLight(vec3 c, double i, vec3 dir) : ILight(LightType::Directional, c, i),
                                                 direction{ dir } {};

  vec3 getDirection() { return direction; }

private:
  vec3 direction;
};

};// namespace WaveStrider
