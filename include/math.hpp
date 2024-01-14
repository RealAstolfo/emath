#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>
#include <limits>

using exfloat = std::float_t;

inline exfloat lerp_approx(const exfloat &v0, const exfloat &v1,
                           const exfloat &t) {
  return v0 + t * (v1 - v0);
}

inline exfloat lerpf(const exfloat &v0, const exfloat &v1, const exfloat &t) {
  return (1.0f - t) * v0 + t * v1;
}

template <typename T> inline T lerp(const T &v0, const T &v1, const T &t) {
  const T type_one =
      std::numeric_limits<T>::max() / std::numeric_limits<T>::max();
  return (type_one - t) * v0 + t * v1;
}

#endif
