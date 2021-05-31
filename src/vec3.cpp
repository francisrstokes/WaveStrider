#include "vec3.hpp"
#include <math.h>

namespace WaveStrider {

vec3::vec3(double X, double Y, double Z) : x{X}, y{Y}, z{Z} {};
vec3::vec3(double n) : x{n}, y{n}, z{n} {};
vec3::vec3(const vec3& v) : x{v.x}, y{v.y}, z{v.z} {};

double vec3::length() {
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
};

vec3 vec3::normalize() {
  double l = length();
  return vec3(
    x / l,
    y / l,
    z / l
  );
};

vec3 vec3::operator+(vec3 const &b) {
  return vec3(this->x + b.x, this->y + b.y, this->z + b.z);
};

vec3 vec3::operator*(vec3 const &b) {
  return vec3(this->x * b.x, this->y * b.y, this->z * b.z);
};

vec3 vec3::operator*(double n) {
  return vec3(this->x * n, this->y * n, this->z * n);
};

vec3 vec3::operator*=(double n) {
  this->x *= n;
  this->y *= n;
  this->z *= n;
  return *this;
};

std::ostream& operator<< (std::ostream &out, const vec3 &v) {
  out << "vec3(" << v.x << "," << v.y << "," << v.z << ")";
  return out;
}

}
