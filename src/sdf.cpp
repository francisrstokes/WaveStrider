#include "sdf.hpp"

namespace WaveStrider {

// SDFUnion::SDFUnion(SDFObject* A, SDFObject* B) : a{A}, b{B} {};
// SDFResult SDFUnion::distance(vec3 rayOrigin, vec3 rayDirection, vec3 p) {
//   auto resultA = a->distance(rayOrigin, rayDirection, p);
//   auto resultB = b->distance(rayOrigin, rayDirection, p);

//   if (resultA.distance < resultB.distance) {
//     return resultA;
//   }
//   return resultB;
// };

namespace SDF {

  SDFResult Union(SDFResult a, SDFResult b)
  {
    return (a.distance < b.distance) ? a : b;
  };

  SDFResult Intersection(SDFResult a, SDFResult b)
  {
    return (a.distance > b.distance) ? a : b;
  };

  SDFResult Difference(SDFResult a, SDFResult b)
  {
    return (-a.distance > b.distance) ? a : b;
  };

}// namespace SDF

};// namespace WaveStrider
