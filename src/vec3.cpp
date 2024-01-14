#include "vec3.hpp"
#include "matrix4x4.hpp"

vec3 vec3::operator-() {
  const vec3 ret = {
      -x,
      -y,
      -z,
  };
  return ret;
}

vec3 &vec3::operator+=(const vec3 &v) {
  x += v.x;
  y += v.y;
  z += v.z;
  return *this;
}

vec3 &vec3::operator-=(const vec3 &v) {
  x -= v.x;
  y -= v.y;
  z -= v.y;
  return *this;
}

vec3 &vec3::operator*=(const float &f) {
  x *= f;
  y *= f;
  z *= f;
  return *this;
}

vec3 &vec3::normalize() {
  const exfloat l = std::sqrt(x * x + y * y + z * z);
  x /= l;
  y /= l;
  z /= l;
  return *this;
}

vec3 &vec3::cross(const vec3 &v) {
  x = y * v.z - z * v.y;
  y = z * v.x - x * v.z;
  z = x * v.y - y * v.x;
  return *this;
}

exfloat vec3::dot(const vec3 &v) { return x * v.x + y * v.y + z * v.z; }

vec3 &vec3::max(const vec3 &v) {
  x = std::max(x, v.x);
  y = std::max(y, v.y);
  z = std::max(z, v.z);
  return *this;
}

vec3 &vec3::min(const vec3 &v) {
  x = std::min(x, v.x);
  y = std::min(y, v.y);
  z = std::min(z, v.z);
  return *this;
}

vec3 operator+(const vec3 &v1, const vec3 &v2) {
  const vec3 ret = {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
  return ret;
}

vec3 operator-(const vec3 &v1, const vec3 &v2) {
  const vec3 ret = {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
  return ret;
}

vec3 operator*(const vec3 &v, const float &f) {
  const vec3 ret = {v.x * f, v.y * f, v.z * f};
  return ret;
}

vec3 operator*(const vec3 &v, const matrix4x4 &m) {
  const vec3 ret = {.x = v.x * m.m[0] + v.y * m.m[4] + v.z * m.m[8] + m.m[12],
                    .y = v.x * m.m[1] + v.y * m.m[5] + v.z * m.m[9] + m.m[13],
                    .z = v.x * m.m[2] + v.y * m.m[6] + v.z * m.m[10] + m.m[14]};
  return ret;
}

vec3 normalize(const vec3 &v) {
  const exfloat l = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
  const vec3 ret = {v.x / l, v.y / l, v.z / l};
  return ret;
}

vec3 cross(const vec3 &v1, const vec3 &v2) {
  const vec3 ret = {
      v1.y * v2.z - v1.z * v2.y,
      v1.z * v2.x - v1.x * v2.z,
      v1.x * v2.y - v1.y * v2.x,
  };
  return ret;
}

exfloat dot(const vec3 &v1, const vec3 &v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 max(const vec3 &v1, const vec3 &v2) {
  const vec3 ret = {
      std::max(v1.x, v2.x),
      std::max(v1.y, v2.y),
      std::max(v1.z, v2.z),
  };
  return ret;
}

vec3 min(const vec3 &v1, const vec3 &v2) {
  const vec3 ret = {
      std::min(v1.x, v2.x),
      std::min(v1.y, v2.y),
      std::min(v1.z, v2.z),
  };
  return ret;
}
