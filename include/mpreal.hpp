#ifndef MPREAL_HPP
#define MPREAL_HPP

#include <mpfr.h>

#define DEFAULT_PRECISION 256

struct mpreal {
  mpfr_t r;

  mpreal() {
    mpfr_init2(r, DEFAULT_PRECISION);
  }

  ~mpreal() {
    mpfr_clear(r);
  }

  mpreal& operator+=(const mpreal& v);
  mpreal& operator-=(const mpreal& v);
  mpreal& operator*=(const mpreal& v);
  mpreal& operator/=(const mpreal& v);  
};

mpreal operator+(const mpreal& x, const mpreal& y);
mpreal operator-(const mpreal& x, const mpreal& y);
mpreal operator*(const mpreal& x, const mpreal& y);
mpreal operator/(const mpreal& x, const mpreal& y);

#endif
