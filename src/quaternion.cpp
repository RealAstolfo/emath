#include "quaternion.hpp"
#include "matrix4x4.hpp"

quaternion::operator matrix4x4() {
  const exfloat sx = x * x;
  const exfloat sy = y * y;
  const exfloat sz = z * z;
  const exfloat sw = w * z;
  const exfloat xy = x * y;
  const exfloat zw = z * w;
  const exfloat xz = x * z;
  const exfloat yw = y * w;
  const exfloat yz = y * z;
  const exfloat xw = x * w;
  const exfloat invsl = 1.0f / (sx + sy + sz + sw);
  const matrix4x4 ret = {(sx - sy - sz + sw) * invsl,
                         2.0f * (xy + zw) * invsl,
                         2.0f * (xz - yw) * invsl,
                         0.0f,
                         2.0f * (xy - zw) * invsl,
                         (-sx + sy - sz + sw) * invsl,
                         2.0f * (yz + xw) * invsl,
                         0.0f,
                         2.0f * (xz + yw) * invsl,
                         2.0f * (yz - xw) * invsl,
                         (-sx + sy - sz + sw) * invsl,
                         0.0f,
                         0.0f,
                         0.0f,
                         0.0f,
                         0.0f};
  return ret;
}

quaternion &quaternion::operator+=(const quaternion &q) {
  x += q.x;
  y += q.y;
  z += q.z;
  w += q.w;
  return *this;
}

quaternion &quaternion::operator*=(const quaternion &q) {
  x = x * q.w + y * q.z - z * q.y + w * q.x;
  y = -x * q.z + y * q.w + z * q.x + w * q.y;
  z = x * q.y - y * q.x + z * q.w + w * q.z;
  w = -x * q.x - y * q.y - z * q.z + w * q.w;
  return *this;
}

quaternion &quaternion::lookat(const vec3 &forward, const vec3 &up) {
  const vec3 right = cross(up, forward);
  const exfloat nw = std::sqrt(1.0f + right.x + up.y + forward.z) * 0.5f;
  const exfloat recip = 1.0f / (4.0f * w);
  x = (up.z - forward.y) * recip;
  y = (forward.x - right.z) * recip;
  z = (right.y - up.x) * recip;
  w = nw;
  return *this;
}

vec3 quaternion::up() {
  const vec3 ret = {
      2.0f * (x * y - w * z),
      1.0f - 2.0f * (x * x + z * z),
      2.0f * (y * z + w * z),
  };
  return ret;
}

vec3 quaternion::down() { return -up(); }

vec3 quaternion::left() {
  const vec3 ret = {
      1.0f - 2.0f * (y * y + z * z),
      2.0f * (x * y + w * z),
      2.0f * (x * z - w * y),
  };
  return ret;
}

vec3 quaternion::right() { return -left(); }

vec3 quaternion::forward() {
  const vec3 ret = {
      2.0f * (x * z + w * y),
      2.0f * (y * z + w * x),
      1.0f - 2.0f * (x * x + y * y),
  };
  return ret;
}

vec3 quaternion::backward() { return -forward(); }

quaternion operator+(const quaternion &q1, const quaternion &q2) {
  const quaternion ret = {q1.x + q2.x, q1.y + q2.y, q1.z + q2.z, q1.w + q2.w};
  return ret;
}

quaternion operator*(const quaternion &q1, const quaternion &q2) {
  const quaternion ret = {
      q1.x * q2.w + q1.y * q2.z - q1.z * q2.y + q1.w * q2.x,
      -q1.x * q2.z + q1.y * q2.w + q1.z * q2.x + q1.w * q2.y,
      q1.x * q2.y - q1.y * q2.x + q1.z * q2.w + q1.w * q2.z,
      -q1.x * q2.x - q1.y * q2.y - q1.z * q2.z + q1.w * q2.w};
  return ret;
}

/*
        WARNING: this function assumes its inputs are already normalized
*/
quaternion lookat(const vec3 &forward, const vec3 &up) {
  const vec3 right = cross(up, forward);
  const exfloat w = std::sqrt(1.0f + right.x + up.y + forward.z) * 0.5f;
  const exfloat recip = 1.0f / (4.0f * w);
  const quaternion ret = {(up.z - forward.y) * recip,
                          (forward.x - right.z) * recip,
                          (right.y - up.x) * recip, w};
  return ret;
}

/*
        This is an estimator function
        if the quaternions represent the same rotation, return == 0
        if the quaternions represent an opposing rotation, return == 1
*/
exfloat inner_product_rough(const quaternion &q1, const quaternion &q2) {
  const exfloat inner_product =
      q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
  return 1.0f - (inner_product * inner_product);
}

/*
        returns theta of the two quaternions
*/
exfloat inner_product_precise(const quaternion &q1, const quaternion &q2) {
  const float inner_product =
      q1.x * q2.x + q1.y * q2.y + q1.z * q2.z + q1.w * q2.w;
  return std::acos(2.0f * (inner_product * inner_product) - 1.0f);
}

quaternion conjugate(const quaternion &q) {
  const quaternion ret = {-q.x, -q.y, -q.z, q.w};
  return ret;
}
