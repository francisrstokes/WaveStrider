#include <iostream>
#include <vector>
#include <cmath>

#include "ray.hpp"
#include "ppm.hpp"
#include "vec3.hpp"
#include "canvas.hpp"
#include "sdf.hpp"
#include "sdfResult.hpp"
#include "material.hpp"
#include "scene.hpp"
#include "light.hpp"

namespace WaveStrider {

struct Sphere : SDFObject {
  double r;

  Sphere(vec3 pos, double radius) : r{radius} {
    m = new Phong();
    auto phong = (Phong*)(m);
    phong->diffuse = 0.6;
    phong->ambient = 0.1;
    phong->ambientColor = vec3(0.0, 0.0, 0.8);

    position = pos;
  };

  ~Sphere() {
    delete m;
  }

  SDFResult getDistanceResult(vec3 p) {
    double dist = (p - position).length() - r;
    return SDFResult(dist, this, p);
  }

};

struct Plane : SDFObject {
  Plane(vec3 pos) {
    m = new Phong();
    auto phong = (Phong*)(m);
    phong->diffuse = 0.7;
    phong->ambient = 0.1;
    phong->specular = 0.3;
    phong->diffuseColor = vec3(0.08, 0.7, 0.23);
    phong->ambientColor = vec3(0.0, 0.0, 0.8);

    position = pos;
  };

  ~Plane() {
    delete m;
  }

  SDFResult getDistanceResult(vec3 p) {
    return SDFResult((p.y + position.y + sin(p.x * 1.0)), this, p);
  }

};

struct MainScene : Scene {

  Sphere s;
  Plane p;
  std::vector<ILight*> lights;

  DirectionalLight dl = DirectionalLight(
    vec3(1.0, 0.0, 0.0),
    0.1,
    vec3(0.2, 0.4, 0.0).normalize()
  );

  MainScene() :
    s{vec3(-1.0, 0.0, 8.0), 1.0},
    p{vec3(0.0, 4.0, 0.0)},
    lights{}
  {
    lights.push_back(&dl);
  };
  ~MainScene() {};

  SDFResult getDistanceResult(vec3 point) {
    return SDF::Union(s.getDistanceResult(point), p.getDistanceResult(point));
  };

  std::vector<ILight*> getLights() { return lights; };
};

};

using namespace WaveStrider;

constexpr double MAX_DIST = 100.0;
constexpr double EPSILON = 0.01;
constexpr int MAX_STEPS = 100;

SDFResult rayMarch(Scene* scene, Ray* ray) {
  SDFResult result;
  result.distance = 0;
  int i = 0;

  for (i = 0; i < MAX_STEPS; i++) {
    result = scene->getDistanceResult(ray->point);
    ray->advance(result.distance);
    if (ray->distance < EPSILON || ray->distance > MAX_DIST) {
      break;
    }
  }

  result.distance = ray->distance;
  return result;
};

vec3 getNormal(Scene* scene, SDFResult res) {
  double d = scene->getDistanceResult(res.position).distance;
  double e = 0.01;

  auto n = vec3(d) - vec3(
    scene->getDistanceResult(res.position - vec3(e, 0, 0)).distance,
    scene->getDistanceResult(res.position - vec3(0, e, 0)).distance,
    scene->getDistanceResult(res.position - vec3(0, 0, e)).distance
  );

  return n.normalize();
};

int main() {
  uint32_t w = 1280;
  uint32_t h = 720;
  auto dim = vec3(w, h, 1);

  auto canvas = Canvas(w, h);

  vec3 origin;
  Ray ray = Ray(origin, vec3());
  MainScene scene;

  for (uint32_t y = 0; y < h; y++) {
    for (uint32_t x = 0; x < w; x++) {
      auto fragCoord = vec3(-(double)w/2.0 + (double)x, -(double)h/2.0 + (double)h - (double)y, 0.0);
      auto uv = fragCoord / vec3((double)h);

      ray.reset(vec3(uv.x, uv.y, 1.0).normalize());
      auto result = rayMarch(&scene, &ray);

      double t = 0.5 * (ray.direction.y + 1.0);
      vec3 col = vec3(1.0) * (1.0 - t) + vec3(0.5, 0.7, 1.0) * t;

      if (result.distance <= MAX_DIST) {
        col = result.obj->m->getColor(
          uv,
          result.position,
          getNormal(&scene, result),
          scene.getLights()
        );
      }

      canvas.put(x, y, col);
    }
  }

  canvas.write("test.ppm");

  return 0;
}
