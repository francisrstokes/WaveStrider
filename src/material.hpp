#pragma once

#include "light.hpp"
#include "vec3.hpp"

namespace WaveStrider {

struct IMaterial
{
  virtual vec3 getColor(vec3 uv, vec3 p, vec3 normal, std::vector<ILight *> lights) = 0;
  virtual ~IMaterial(){};
};

struct Phong : IMaterial
{

  Phong();
  ~Phong();

  vec3 ambientColor = vec3(0.5, 0.05, 0.1);
  vec3 diffuseColor = vec3(0.8, 0.0, 0.0);
  vec3 specularColor = vec3(1.0);

  double ambient = 0.1;
  double diffuse = 0.8;
  double specular = 0.7;
  double shininess = 10.0;

  vec3 getColor(vec3 uv, vec3 p, vec3 normal, std::vector<ILight *> lights);
};

};// namespace WaveStrider
