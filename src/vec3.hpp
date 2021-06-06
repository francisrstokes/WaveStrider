#pragma once
#include <iostream>

namespace WaveStrider {

struct vec3
{
  double x;
  double y;
  double z;

  // Constructors
  vec3(double X, double Y, double Z);
  vec3(double n);
  vec3();
  vec3(const vec3 &v);

  // Methods
  vec3 normalize();
  vec3 max(double n);
  vec3 min(double n);
  vec3 clamp(double minVal, double maxVal);
  double dot(vec3 const &b);
  double length();

  // Operators
  vec3 operator+(vec3 const &b);
  vec3 operator+=(vec3 const &b);
  vec3 operator-(vec3 const &b);
  vec3 operator-=(vec3 const &b);
  vec3 operator*(vec3 const &b);
  vec3 operator*(double n);
  vec3 operator*=(double n);
  vec3 operator/(vec3 const &b);
  vec3 operator/(double n);
  vec3 operator/=(double n);
  // TODO:  -,/, +=,-=,/=
  // Would ~ for normalize be awful? Probably

  // Debugging
  friend std::ostream &operator<<(std::ostream &out, const vec3 &v);
};

}// namespace WaveStrider
