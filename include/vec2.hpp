#ifndef VEC2_HPP
#define VEC2_HPP

#include "math.hpp"

typedef struct vec2 {
  exfloat x = 0.0f, y = 0.0f;

  vec2 &operator+=(const vec2 &v);
  vec2 &operator-=(const vec2 &v);
  vec2 &operator*=(const exfloat &f);
  float magnitude();
  vec2 &normalize();
  exfloat dot(vec2 &v);
} vec2;

vec2 operator+(const vec2 &v1, const vec2 &v2);
vec2 operator-(const vec2 &v1, const vec2 &v2);
vec2 operator*(const vec2 &v, const exfloat &f);
vec2 normalize(const vec2 &v);
exfloat dot(const vec2 &v1, const vec2 &v2);

const vec2 vec2_zero = {0.0f, 0.0f};
const vec2 vec2_one = {1.0f, 1.0f};

#endif
