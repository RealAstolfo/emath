#include "vec2.hpp"

vec2 &vec2::operator+=(const vec2 &v) {
  x += v.x;
  y += v.y;
  return *this;
}

vec2 &vec2::operator-=(const vec2 &v) {
  x -= v.x;
  y -= v.y;
  return *this;
}

vec2 &vec2::operator*=(const float &f) {
  x *= f;
  y *= f;
  return *this;
}

float vec2::magnitude() {
  const exfloat ret = std::sqrt(x * x + y * y);
  return ret;
}

vec2 &vec2::normalize() {
  const exfloat l = magnitude();
  x /= l;
  y /= l;
  return *this;
}

exfloat vec2::dot(vec2 &v) { return x * v.x + y * v.y; }

vec2 operator+(const vec2 &v1, const vec2 &v2) {
  const vec2 ret = {
      v1.x + v2.x,
      v1.y + v2.y,
  };
  return ret;
}

vec2 operator-(const vec2 &v1, const vec2 &v2) {
  const vec2 ret = {
      v1.x - v2.x,
      v1.y - v2.y,
  };
  return ret;
}

vec2 operator*(const vec2 &v, const float &f) {
  const vec2 ret = {
      v.x * f,
      v.y * f,
  };
  return ret;
}

vec2 normalize(const vec2 &v) {
  const exfloat l = std::sqrt(v.x * v.x + v.y * v.y);
  const vec2 ret = {v.x / l, v.y / l};
  return ret;
}

exfloat dot(const vec2 &v1, const vec2 &v2) {
  return v1.x * v2.x + v1.y * v2.y;
}
