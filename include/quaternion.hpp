#ifndef QUATERNION_HPP
#define QUATERNION_HPP

#include "math.hpp"
#include "vec3.hpp"

typedef struct matrix4x4 matrix4x4;

/*
    forward vector:
    x = 2 * (x*z + w*y)
    y = 2 * (y*z - w*x)
    z = 1 - 2 * (x*x + y*y)

    up vector
    x = 2 * (x*y - w*z)
    y = 1 - 2 * (x*x + z*z)
    z = 2 * (y*z + w*x)

    left vector
    x = 1 - 2 * (y*y + z*z)
    y = 2 * (x*y + w*z)
    z = 2 * (x*z - w*y)
*/

typedef struct quaternion {
  exfloat x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;

  operator matrix4x4();
  quaternion &operator+=(const quaternion &q);
  quaternion &operator*=(const quaternion &q);
  quaternion &lookat(const vec3 &forward, const vec3 &up);
  vec3 up();
  vec3 down();
  vec3 left();
  vec3 right();
  vec3 forward();
  vec3 backward();
} quaternion;

const quaternion quaternion_identity = {0.0f, 0.0f, 0.0f, 1.0f};

quaternion operator+(const quaternion &q1, const quaternion &q2);
quaternion operator*(const quaternion &q1, const quaternion &q2);
quaternion lookat(const vec3 &forward, const vec3 &up);
exfloat inner_product_rough(const quaternion &q1, const quaternion &q2);
exfloat inner_product_precise(const quaternion &q1, const quaternion &q2);
quaternion conjugate(const quaternion &q);

#endif
