#include "matrix4x4.hpp"

matrix4x4::operator quaternion() {
  const exfloat w = std::sqrt(1.0f + m[0] + m[5] + m[10]) / 2.0f;
  const exfloat w2 = 4.0f * w;
  const quaternion ret = {(m[6] - m[9]) / w2, (m[8] - m[2]) / w2,
                          (m[1] - m[4]) / w2, w};
  return ret;
}

exfloat &matrix4x4::operator[](size_t index) { return m[index]; }

const exfloat &matrix4x4::operator[](size_t index) const { return m[index]; }

matrix4x4 &matrix4x4::operator+=(const matrix4x4 &other) {
  for (size_t i = 0; i < sizeof(matrix4x4::m) / sizeof(matrix4x4::m[0]); i++)
    m[i] += other[i];
  return *this;
}

matrix4x4 &matrix4x4::operator-=(const matrix4x4 &other) {
  for (size_t i = 0; i < sizeof(matrix4x4::m) / sizeof(matrix4x4::m[0]); i++)
    m[i] -= other[i];
  return *this;
}

matrix4x4 &matrix4x4::operator*=(const matrix4x4 &other) {
  const size_t fc = sizeof(matrix4x4::m) / sizeof(matrix4x4::m[0]) / 4;
  for (size_t i = 0; i < fc; i++)
    for (size_t j = 0; j < fc; j++)
      for (size_t k = 0; k < fc; k++) {
        m[fc * i + j] += m[fc * i + k] * other[fc * k + j];
      }
  return *this;
}

matrix4x4 &matrix4x4::operator=(const quaternion &q) {
  const exfloat sx = q.x * q.x;
  const exfloat sy = q.y * q.y;
  const exfloat sz = q.z * q.z;
  const exfloat sw = q.w * q.z;
  const exfloat xy = q.x * q.y;
  const exfloat zw = q.z * q.w;
  const exfloat xz = q.x * q.z;
  const exfloat yw = q.y * q.w;
  const exfloat yz = q.y * q.z;
  const exfloat xw = q.x * q.w;
  const exfloat invsl = 1.0f / (sx + sy + sz + sw);
  m[0] = (sx - sy - sz + sw) * invsl;
  m[1] = 2.0f * (xy + zw) * invsl;
  m[2] = 2.0f * (xz - yw) * invsl;
  m[4] = 2.0f * (xy - zw) * invsl;
  m[5] = (-sx + sy - sz + sw) * invsl;
  m[6] = 2.0f * (yz + xw) * invsl;
  m[8] = 2.0f * (xz + yw) * invsl;
  m[9] = 2.0f * (yz - xw) * invsl;
  m[10] = (-sx + sy - sz + sw) * invsl;
  return *this;
}

matrix4x4 &matrix4x4::operator=(const vec2 &v) {
  m[12] = v.x;
  m[14] = v.y;
  return *this;
}

matrix4x4 &matrix4x4::operator=(const vec3 &v) {
  m[12] = v.x;
  m[13] = v.y;
  m[14] = v.z;
  return *this;
}

matrix4x4 &matrix4x4::translate(const vec2 &v) {
  m[12] += v.x;
  m[14] += v.y;
  return *this;
}

matrix4x4 &matrix4x4::translate(const vec3 &v) {
  m[12] += v.x;
  m[13] += v.y;
  m[14] += v.z;
  return *this;
}

matrix4x4 &matrix4x4::rotate(exfloat ax, exfloat ay, exfloat az) {
  const exfloat sx = std::sin(ax);
  const exfloat cx = std::cos(ax);
  const exfloat sy = std::sin(ay);
  const exfloat cy = std::cos(ay);
  const exfloat sz = std::sin(az);
  const exfloat cz = std::cos(az);
  m[0] = cy * cz;
  m[1] = -cy * sz;
  m[2] = sy;
  m[4] = cz * sx * sy + cx * sz;
  m[5] = cx * cz - sx * sy * sz;
  m[6] = -cy * sx;
  m[8] = -cx * cz * sy + sx * sz;
  m[9] = cz * sx + cx * sy * sz;
  m[10] = cx * cy;
  m[15] = 1.0f;
  return *this;
}

matrix4x4 &matrix4x4::scale(const vec3 &v) {
  m[0] = v.x;
  m[5] = v.y;
  m[10] = v.z;
  m[15] = 1.0f;
  return *this;
}

matrix4x4 &matrix4x4::lookat(const vec3 &pos, const vec3 &target,
                             const vec3 &global_up) {
  const vec3 forward = (target - pos).normalize();
  const vec3 side = cross(forward, global_up).normalize();
  const vec3 up = cross(side, forward);
  m[0] = side.x;
  m[1] = up.x;
  m[2] = -forward.x;
  m[3] = 0.0f;
  m[4] = side.y;
  m[5] = up.y;
  m[6] = -forward.y;
  m[7] = 0.0f;
  m[8] = side.z;
  m[9] = up.z;
  m[10] = -forward.z;
  m[11] = 0.0f;
  m[12] = -dot(side, pos);
  m[13] = -dot(up, pos);
  m[14] = dot(forward, pos);
  m[15] = 1.0f;
  return *this;
};

matrix4x4 operator+(const matrix4x4 &m1, const matrix4x4 &m2) {
  matrix4x4 ret = matrix4x4_zero;
  for (size_t i = 0; i < sizeof(matrix4x4::m) / sizeof(matrix4x4::m[0]); i++)
    ret[i] = m1[i] + m2[i];
  return ret;
}

matrix4x4 operator-(const matrix4x4 &m1, const matrix4x4 &m2) {
  matrix4x4 ret = matrix4x4_zero;
  for (size_t i = 0; i < sizeof(matrix4x4::m) / sizeof(matrix4x4::m[0]); i++)
    ret[i] = m1[i] - m2[i];
  return ret;
}

matrix4x4 operator*(const matrix4x4 &m1, const matrix4x4 &m2) {
  matrix4x4 ret = matrix4x4_zero;
  const size_t fc = sizeof(matrix4x4::m) / sizeof(matrix4x4::m[0]) / 4;
  for (size_t i = 0; i < fc; i++)
    for (size_t j = 0; j < fc; j++)
      for (size_t k = 0; k < fc; k++)
        ret[fc * i + j] += m1[fc * i + k] * m2[fc * k + j];
  return ret;
}

matrix4x4 transpose(const matrix4x4 &m) {
  const matrix4x4 ret = {
      m[0], m[4], m[8],  m[12], m[1], m[5], m[9],  m[13],
      m[2], m[6], m[10], m[14], m[3], m[7], m[11], m[15],
  };
  return ret;
}

matrix4x4 cofactor(const matrix4x4 &m) {
  const exfloat xx = m[0];
  const exfloat xy = m[1];
  const exfloat xz = m[2];
  const exfloat xw = m[3];
  const exfloat yx = m[4];
  const exfloat yy = m[5];
  const exfloat yz = m[6];
  const exfloat yw = m[7];
  const exfloat zx = m[8];
  const exfloat zy = m[9];
  const exfloat zz = m[10];
  const exfloat zw = m[11];
  const exfloat wx = m[12];
  const exfloat wy = m[13];
  const exfloat wz = m[14];
  const exfloat ww = m[15];
  const matrix4x4 ret = {
      +(yy * (zz * ww - wz * zw) - yz * (zy * ww - wy * zw) +
        yw * (zy * wz - wy * zz)),
      -(yx * (zz * ww - wz * zw) - yz * (zx * ww - wx * zw) +
        yw * (zx * wz - wx * zz)),
      +(yx * (zy * ww - wy * zw) - yy * (zx * ww - wx * zw) +
        yw * (zx * wy - wx * zy)),
      -(yx * (zy * wz - wy * zz) - yy * (zx * wz - wx * zz) +
        yz * (zx * wy - wx * zy)),
      -(xy * (zz * ww - wz * zw) - xz * (zy * ww - wy * zw) +
        xw * (zy * wz - wy * zz)),
      +(xx * (zz * ww - wz * zw) - xz * (zx * ww - wx * zw) +
        xw * (zx * wz - wx * zz)),
      -(xx * (zy * ww - wy * zw) - xy * (zx * ww - wx * zw) +
        xw * (zx * wy - wx * zy)),
      +(xx * (zy * wz - wy * zz) - xy * (zx * wz - wx * zz) +
        xz * (zx * wy - wx * zy)),
      +(xy * (yz * ww - wz * yw) - xz * (yy * ww - wy * yw) +
        xw * (yy * wz - wy * yz)),
      -(xx * (yz * ww - wz * yw) - xz * (yx * ww - wx * yw) +
        xw * (yx * wz - wx * yz)),
      +(xx * (yy * ww - wy * yw) - xy * (yx * ww - wx * yw) +
        xw * (yx * wy - wx * yy)),
      -(xx * (yy * wz - wy * yz) - xy * (yx * wz - wx * yz) +
        xz * (yx * wy - wx * yy)),
      -(xy * (yz * zw - zz * yw) - xz * (yy * zw - zy * yw) +
        xw * (yy * zz - zy * yz)),
      +(xx * (yz * zw - zz * yw) - xz * (yx * zw - zx * yw) +
        xw * (yx * zz - zx * yz)),
      -(xx * (yy * zw - zy * yw) - xy * (yx * zw - zx * yw) +
        xw * (yx * zy - zx * yy)),
      +(xx * (yy * zz - zy * yz) - xy * (yx * zz - zx * yz) +
        xz * (yx * zy - zx * yy)),
  };
  return ret;
}

matrix4x4 lookat(const vec3 &pos, const vec3 &target, const vec3 &global_up) {
  const vec3 forward = (target - pos).normalize();
  const vec3 side = cross(forward, global_up).normalize();
  const vec3 up = cross(side, forward);
  const matrix4x4 ret = {
      side.x,          up.x,          -forward.x,        0.0f,
      side.y,          up.y,          -forward.y,        0.0f,
      side.z,          up.z,          -forward.z,        0.0f,
      -dot(side, pos), -dot(up, pos), dot(forward, pos), 1.0f};
  return ret;
}

matrix4x4 projection(const exfloat &aspect_ratio, const exfloat &yfov,
                     const exfloat &zfar, const exfloat &znear) {
  const exfloat a = std::tan(0.5f * yfov);
  const exfloat nf = znear - zfar;
  const matrix4x4 ret = {
      1.0f / (aspect_ratio * a),
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      1.0f / a,
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      (zfar + znear) / nf,
      (2.0f * zfar * znear) / nf,
      0.0f,
      0.0f,
      -1.0f,
      0.0f,
  };
  return ret;
}

matrix4x4 projection_inf(const exfloat &aspect_ratio, const exfloat &yfov,
                         const exfloat &znear) {
  const exfloat a = std::tan(0.5f * yfov);
  const matrix4x4 ret = {
      1.0f / (aspect_ratio * a),
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      1.0f / a,
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      -1.0f,
      -2.0f * znear,
      0.0f,
      0.0f,
      -1.0f,
      0.0f,
  };
  return ret;
}

matrix4x4 projection_orthographic(const exfloat &xmag, const exfloat &ymag,
                                  const exfloat &zfar, const exfloat &znear) {
  const exfloat nf = znear - zfar;
  const exfloat fn = znear + zfar;
  const matrix4x4 ret = {
      1.0f / xmag, 0.0f, 0.0f,      0.0f,    0.0f, 1.0f / ymag, 0.0f, 0.0f,
      0.0f,        0.0f, 2.0f / nf, fn / nf, 0.0f, 0.0f,        0.0f, 1.0f,
  };
  return ret;
}
