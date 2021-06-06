#include "vec3.hpp"
#include <math.h>

namespace WaveStrider {

vec3::vec3(double X, double Y, double Z) : x{ X }, y{ Y }, z{ Z } {};
vec3::vec3(double n) : x{ n }, y{ n }, z{ n } {};
vec3::vec3() : x{ 0 }, y{ 0 }, z{ 0 } {};
vec3::vec3(const vec3 &v) : x{ v.x }, y{ v.y }, z{ v.z } {};

double vec3::length()
{
  return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
};

vec3 vec3::clamp(double minVal, double maxVal)
{
  return vec3(
    x < minVal ? minVal : x > maxVal ? maxVal
                                     : x,
    y < minVal ? minVal : y > maxVal ? maxVal
                                     : y,
    z < minVal ? minVal : z > maxVal ? maxVal
                                     : z);
};

double vec3::dot(vec3 const &b)
{
  return x * b.x + y * b.y + z * b.z;
};

vec3 vec3::normalize()
{
  double l = length();
  if (l == 0) return vec3(x, y, z);
  return vec3(
    x / l,
    y / l,
    z / l);
};

vec3 vec3::max(double n)
{
  return vec3(
    x > n ? x : n,
    y > n ? y : n,
    z > n ? z : n);
};

vec3 vec3::min(double n)
{
  return vec3(
    x < n ? x : n,
    y < n ? y : n,
    z < n ? z : n);
};

vec3 vec3::operator+(const vec3 &b)
{
  return vec3(this->x + b.x, this->y + b.y, this->z + b.z);
};

vec3 vec3::operator-(const vec3 &b)
{
  return vec3(this->x - b.x, this->y - b.y, this->z - b.z);
};

vec3 vec3::operator*(const vec3 &b)
{
  return vec3(this->x * b.x, this->y * b.y, this->z * b.z);
};

vec3 vec3::operator*(double n)
{
  return vec3(this->x * n, this->y * n, this->z * n);
};

vec3 vec3::operator*=(double n)
{
  this->x *= n;
  this->y *= n;
  this->z *= n;
  return *this;
};

vec3 vec3::operator/(const vec3 &b)
{
  return vec3(this->x / b.x, this->y / b.y, this->z / b.z);
};

vec3 vec3::operator/(double n)
{
  return vec3(this->x / n, this->y / n, this->z / n);
};

vec3 vec3::operator/=(double n)
{
  this->x /= n;
  this->y /= n;
  this->z /= n;
  return *this;
};

vec3 vec3::operator+=(vec3 const &b)
{
  this->x += b.x;
  this->y += b.y;
  this->z += b.z;
  return *this;
};

vec3 vec3::operator-=(vec3 const &b)
{
  this->x -= b.x;
  this->y -= b.y;
  this->z -= b.z;
  return *this;
};

std::ostream &operator<<(std::ostream &out, const vec3 &v)
{
  out << "vec3(" << v.x << "," << v.y << "," << v.z << ")";
  return out;
}

}// namespace WaveStrider
