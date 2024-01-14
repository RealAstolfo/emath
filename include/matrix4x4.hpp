#ifndef MATRIX4X4_HPP
#define MATRIX4X4_HPP

#include <cmath>
#include <stdlib.h>

#include "math.hpp"
#include "quaternion.hpp"
#include "vec2.hpp"
#include "vec3.hpp"

typedef struct matrix4x4 matrix4x4;

typedef struct matrix4x4 {
  exfloat m[16] = {
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
      0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
  };
  operator quaternion();
  exfloat &operator[](size_t index);
  const exfloat &operator[](size_t index) const;
  matrix4x4 &operator+=(const matrix4x4 &m);
  matrix4x4 &operator-=(const matrix4x4 &m);
  matrix4x4 &operator*=(const matrix4x4 &m);
  matrix4x4 &operator=(const quaternion &q);
  matrix4x4 &operator=(const vec2 &v);
  matrix4x4 &operator=(const vec3 &v);
  matrix4x4 &translate(const vec2 &v);
  matrix4x4 &translate(const vec3 &v);
  matrix4x4 &rotate(exfloat ax, exfloat ay, exfloat az);
  matrix4x4 &scale(const vec3 &v);
  matrix4x4 &lookat(const vec3 &pos, const vec3 &target, const vec3 &global_up);
} matrix4x4;

const matrix4x4 matrix4x4_identity = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
                                      0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                                      0.0f, 0.0f, 0.0f, 1.0f};

const matrix4x4 matrix4x4_zero = {
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
};

matrix4x4 operator+(const matrix4x4 &m1, const matrix4x4 &m2);
matrix4x4 operator-(const matrix4x4 &m1, const matrix4x4 &m2);
matrix4x4 operator*(const matrix4x4 &m1, const matrix4x4 &m2);
matrix4x4 transpose(const matrix4x4 &m);
matrix4x4 cofactor(const matrix4x4 &m);
matrix4x4 lookat(const vec3 &pos, const vec3 &target, const vec3 &global_up);
matrix4x4 projection(const exfloat &aspect_ratio, const exfloat &yfov,
                     const exfloat &zfar, const exfloat &znear);
matrix4x4 projection_inf(const exfloat &aspect_ratio, const exfloat &yfov,
                         const exfloat &znear);
matrix4x4 projection_orthographic(const exfloat &xmag, const exfloat &ymag,
                                  const exfloat &zfar, const exfloat &znear);
#endif
