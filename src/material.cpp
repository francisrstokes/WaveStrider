#include <vector>
#include <cmath>
#include "material.hpp"

namespace WaveStrider {

Phong::Phong(){};
Phong::~Phong(){};

vec3 Phong::getColor(vec3 uv, vec3 p, vec3 normal, std::vector<ILight *> lights)
{
  vec3 col;
  // TODO: This should actually use the ray direction instead
  vec3 view = p.normalize() * -1.0;
  for (auto light : lights) {
    if (light->type == LightType::Directional) {
      DirectionalLight l = *(dynamic_cast<DirectionalLight *>(light));

      auto ldir = l.getDirection();
      auto nldir = ldir.normalize();
      auto d = (diffuseColor * ldir.dot(normal)).max(0) * diffuse;
      auto a = ambientColor * ambient;

      auto reflected = (normal - nldir) * 2.0 * normal.dot(nldir);
      auto specDot = std::max<double>(reflected.dot(view), 0.0);
      auto s = specularColor * pow(specDot, shininess);

      col += d + a + s;
    }
  }
  return col;
};

};// namespace WaveStrider
