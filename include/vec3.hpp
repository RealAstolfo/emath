#ifndef VEC3_HPP
#define VEC3_HPP

#include <algorithm>

#include "math.hpp"

typedef struct matrix4x4 matrix4x4;

typedef struct vec3 {
  exfloat x = 0, y = 0, z = 0;

  vec3 operator-();
  vec3 &operator+=(const vec3 &v);
  vec3 &operator-=(const vec3 &v);
  vec3 &operator*=(const exfloat &f);
  vec3 &normalize();
  vec3 &cross(const vec3 &v);
  exfloat dot(const vec3 &v);
  vec3 &max(const vec3 &v);
  vec3 &min(const vec3 &v);
} vec3;

vec3 operator+(const vec3 &v1, const vec3 &v2);
vec3 operator-(const vec3 &v1, const vec3 &v2);
vec3 operator*(const vec3 &v, const exfloat &f);
vec3 operator*(const vec3 &v, const matrix4x4 &m);
vec3 normalize(const vec3 &v);
vec3 cross(const vec3 &v1, const vec3 &v2);
exfloat dot(const vec3 &v1, const vec3 &v2);
vec3 max(const vec3 &v1, const vec3 &v2);
vec3 min(const vec3 &v1, const vec3 &v2);

const vec3 vec3_zero = {0.0f, 0.0f, 0.0f};
const vec3 vec3_one = {1.0f, 1.0f, 1.0f};

// default directionals
const vec3 vec3_up = {0.0f, 1.0f, 0.0f};
const vec3 vec3_down = {0.0f, -1.0f, 0.0f};
const vec3 vec3_forward = {0.0f, 0.0f, 1.0f};
const vec3 vec3_back = {0.0f, 0.0f, -1.0f};
const vec3 vec3_left = {-1.0f, 0.0f, 0.0f};
const vec3 vec3_right = {1.0f, 0.0f, 0.0f};

#endif
