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
  virtual SDFResult getDistanceResult(Ray* ray) = 0;
  virtual SDFResult getDistanceResult(vec3 p) = 0;

  virtual ~SDFObject() {};
};

// struct SDFOperation : SDFObject {

// public:
//   SDFOperation(std::function<SDFResult(vec3, vec3, vec3)> distFn) : distanceFn{distFn} {};
//   SDFResult distance(vec3 rayOrigin, vec3 rayDirection, vec3 p) {
//     return distanceFn(rayOrigin, rayDirection, p);
//   };

//   ~SDFOperation() {};

// private:
//   std::function<SDFResult(vec3, vec3, vec3)> distanceFn;
// };

// struct SDFUnion : SDFObject {
//   SDFUnion(SDFObject* A, SDFObject* B);
//   SDFResult distance(vec3 rayOrigin, vec3 rayDirection, vec3 p);

// private:
//   SDFObject* a;
//   SDFObject* b;
// };

namespace SDF {
  SDFResult Union(SDFResult a, SDFResult b);
  SDFResult Intersection(SDFResult a, SDFResult b);
  SDFResult Difference(SDFResult a, SDFResult b);
}

};
