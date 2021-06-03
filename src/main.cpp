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

namespace WaveStrider {

struct BasicMaterial : IMaterial {
  vec3 color;

  BasicMaterial() : color{255.0, 0.0, 0.0} {};
  BasicMaterial(double r, double g, double b) : color{r, g, b} {};

  vec3 getColor() {
    return color;
  };

  ~BasicMaterial() {};
};

struct Sphere : SDFObject {
  double r;

  Sphere(vec3 pos, double radius) : r{radius} {
    m = new BasicMaterial(0.0, 0.5, 0.7);
    position = pos;
  };

  ~Sphere() {
    delete m;
  }

  SDFResult getDistanceResult(Ray* ray) {
    double dist = (ray->point - position).length() - r;
    return SDFResult(dist, this, ray);
  }

  SDFResult getDistanceResult(vec3 p) {
    double dist = (p - position).length() - r;
    return SDFResult(dist, this, p);
  }

};

struct Plane : SDFObject {
  Plane(vec3 pos) {
    m = new BasicMaterial(0.0, 1.0, 0.0);
    position = pos;
  };

  ~Plane() {
    delete m;
  }

  SDFResult getDistanceResult(Ray* ray) {
    return SDFResult((ray->point.y + position.y), this, ray);
  }

  SDFResult getDistanceResult(vec3 p) {
    return SDFResult((p.y + position.y), this, p);
  }

};

struct MainScene : Scene {

  Sphere s;
  Plane p;

  MainScene() : s{vec3(0.0, 0.0, 8.0), 0.5}, p{vec3(0.0, 4.0, 0.0)} {};
  ~MainScene() {};

  SDFResult getDistanceResult(Ray* ray) {
    return SDF::Union(s.getDistanceResult(ray), p.getDistanceResult(ray));
  };

  SDFResult getDistanceResult(vec3 point) {
    return SDF::Union(s.getDistanceResult(point), p.getDistanceResult(point));
  };
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
    result = scene->getDistanceResult(ray);
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
  uint32_t w = 800;
  uint32_t h = 500;
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
        vec3 sunPos{-1.0, 2.0, 6.5};
        vec3 sunColor = vec3(255.0, 225.0, 235.0) / 255.0;
        double sunIntensity = 0.1;

        vec3 normal = getNormal(&scene, result);
        vec3 l = sunPos - result.position;
        double diffuse = std::clamp<double>(l.dot(normal), 0.0, 1.0);

        col = (result.obj->m->getColor() * diffuse) + (sunColor * sunIntensity);
      }

      canvas.put(x, y, col);
    }
  }

  canvas.write("test.ppm");

  return 0;
}

// Ray class
// -> vec3 Origin
// -> vec3 Direction
// -> advance function
// -> maybe reflect function?

// Marcher class
// -> camera description (class?)
// -> Scene description
// -> march method

// Scene Description Class
// -> getSDFResult function
// -> made up of SDFObjects and light sources
// -> Returns an SDFResult

// SDFResult
// -> Plain object with a reference to the SDFObject and the actual distance
// -> Could even think about doing the normal at this point

// SDFObject
// -> base class with a distance function + material
// -> Includes operations for union, intersection, and difference (plus the smooth versions of each)

// Material
// -> Base class with a getColor function
// -> getColor, based on the SDFResult and light information, will return a color
// -> Extending the class, we can easily add support for other inputs