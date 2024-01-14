#include "math.hpp"
#include "matrix4x4.hpp"
#include "quaternion.hpp"

#include <benchmark/benchmark.h>
#include <cstdint>
#include <cstdio>
#include <random>

std::random_device seed;
std::mt19937 gen(seed());

void bm_exfloat_lerp_approx(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const float &v1 = *(float *)state.range(0);
    const float &v2 = *(float *)state.range(1);
    const float &v3 = *(float *)state.range(2);
    benchmark::DoNotOptimize(lerp_approx(v1, v2, v3));
  }
}

void bm_exfloat_lerpf(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const float &v1 = *(float *)state.range(0);
    const float &v2 = *(float *)state.range(1);
    const float &v3 = *(float *)state.range(2);
    benchmark::DoNotOptimize(lerpf(v1, v2, v3));
  }
}

void bm_float_args(benchmark::internal::Benchmark *b) {
  std::uniform_real_distribution<float> rand(0, 10000);

  float *x = new float[256];
  float *y = new float[256];
  float *z = new float[256];

  for (int i = 0; i < 256; i++) {
    x[i] = rand(gen);
    y[i] = rand(gen);
    z[i] = rand(gen);
  }

  b->Args({(intptr_t)x, (intptr_t)y, (intptr_t)z});
  delete[] x;
  delete[] y;
  delete[] z;
}

BENCHMARK(bm_exfloat_lerp_approx)->Apply(bm_float_args);
BENCHMARK(bm_exfloat_lerpf)->Apply(bm_float_args);

void bm_vec2_add(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const vec2 &v1 = *(vec2 *)state.range(0);
    const vec2 &v2 = *(vec2 *)state.range(1);
    benchmark::DoNotOptimize(v1 + v2);
  }
}

void bm_vec2_sub(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const vec2 &v1 = *(vec2 *)state.range(0);
    const vec2 &v2 = *(vec2 *)state.range(1);
    benchmark::DoNotOptimize(v1 - v2);
  }
}

void bm_vec2_mul(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const vec2 &v1 = *(vec2 *)state.range(0);
    const vec2 &v2 = *(vec2 *)state.range(1);
    benchmark::DoNotOptimize(v1 * v2.x);
  }
}

void bm_vec2_normalize(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const vec2 &v1 = *(vec2 *)state.range(0);
    benchmark::DoNotOptimize(normalize(v1));
  }
}

void bm_vec2_dot(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const vec2 &v1 = *(vec2 *)state.range(0);
    const vec2 &v2 = *(vec2 *)state.range(1);
    benchmark::DoNotOptimize(dot(v1, v2));
  }
}

void bm_vec2_args(benchmark::internal::Benchmark *b) {
  std::uniform_real_distribution<float> rand(0, 10000);

  vec2 *x = new vec2[256];
  vec2 *y = new vec2[256];

  for (int i = 0; i < 256; i++) {
    x[i].x = rand(gen);
    x[i].y = rand(gen);
    y[i].x = rand(gen);
    y[i].y = rand(gen);
  }

  b->Args({(intptr_t)x, (intptr_t)y});
  delete[] x;
  delete[] y;
}

// Register the function as a benchmark
BENCHMARK(bm_vec2_add)->Apply(bm_vec2_args);
BENCHMARK(bm_vec2_sub)->Apply(bm_vec2_args);
BENCHMARK(bm_vec2_mul)->Apply(bm_vec2_args);
BENCHMARK(bm_vec2_normalize)->Apply(bm_vec2_args);
BENCHMARK(bm_vec2_dot)->Apply(bm_vec2_args);

void bm_vec3_add(benchmark::State &state) {
  // Perform setup here
  vec3 r;
  benchmark::DoNotOptimize(r);
  while (state.KeepRunning()) {
    // This code gets timed
    const vec3 &v1 = *(vec3 *)state.range(0);
    const vec3 &v2 = *(vec3 *)state.range(1);
    benchmark::DoNotOptimize(v1 + v2);
  }
}

void bm_vec3_sub(benchmark::State &state) {
  // Perform setup here
  vec3 r;
  benchmark::DoNotOptimize(r);
  while (state.KeepRunning()) {
    // This code gets timed
    const vec3 &v1 = *(vec3 *)state.range(0);
    const vec3 &v2 = *(vec3 *)state.range(1);
    benchmark::DoNotOptimize(v1 - v2);
  }
}

void bm_vec3_mul(benchmark::State &state) {
  // Perform setup here
  vec3 r;
  benchmark::DoNotOptimize(r);
  while (state.KeepRunning()) {
    // This code gets timed
    const vec3 &v1 = *(vec3 *)state.range(0);
    const vec3 &v2 = *(vec3 *)state.range(1);
    benchmark::DoNotOptimize(v1 * v2.x);
  }
}

void bm_vec3_normalize(benchmark::State &state) {
  // Perform setup here
  vec3 r;
  benchmark::DoNotOptimize(r);
  while (state.KeepRunning()) {
    // This code gets timed
    const vec3 &v1 = *(vec3 *)state.range(0);
    benchmark::DoNotOptimize(normalize(v1));
  }
}

void bm_vec3_cross(benchmark::State &state) {
  // Perform setup here
  vec3 r;
  benchmark::DoNotOptimize(r);
  while (state.KeepRunning()) {
    // This code gets timed
    const vec3 &v1 = *(vec3 *)state.range(0);
    const vec3 &v2 = *(vec3 *)state.range(1);
    benchmark::DoNotOptimize(cross(v1, v2));
  }
}

void bm_vec3_dot(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const vec3 &v1 = *(vec3 *)state.range(0);
    const vec3 &v2 = *(vec3 *)state.range(1);
    benchmark::DoNotOptimize(dot(v1, v2));
  }
}

void bm_vec3_max(benchmark::State &state) {
  // Perform setup here
  vec3 r;
  benchmark::DoNotOptimize(r);
  while (state.KeepRunning()) {
    // This code gets timed
    const vec3 &v1 = *(vec3 *)state.range(0);
    const vec3 &v2 = *(vec3 *)state.range(1);
    benchmark::DoNotOptimize(max(v1, v2));
  }
}

void bm_vec3_min(benchmark::State &state) {
  // Perform setup here
  vec3 r;
  benchmark::DoNotOptimize(r);
  while (state.KeepRunning()) {
    // This code gets timed
    const vec3 &v1 = *(vec3 *)state.range(0);
    const vec3 &v2 = *(vec3 *)state.range(1);
    benchmark::DoNotOptimize(min(v1, v2));
  }
}

void bm_vec3_args(benchmark::internal::Benchmark *b) {
  std::uniform_real_distribution<float> rand(0, 10000);

  vec3 *x = new vec3[256];
  vec3 *y = new vec3[256];

  for (int i = 0; i < 256; i++) {
    x[i].x = rand(gen);
    x[i].y = rand(gen);
    x[i].z = rand(gen);
    y[i].x = rand(gen);
    y[i].y = rand(gen);
    y[i].z = rand(gen);
  }

  b->Args({(intptr_t)x, (intptr_t)y});
}

// Register the function as a benchmark
BENCHMARK(bm_vec3_add)->Apply(bm_vec3_args);
BENCHMARK(bm_vec3_sub)->Apply(bm_vec3_args);
BENCHMARK(bm_vec3_mul)->Apply(bm_vec3_args);
BENCHMARK(bm_vec3_normalize)->Apply(bm_vec3_args);
BENCHMARK(bm_vec3_cross)->Apply(bm_vec3_args);
BENCHMARK(bm_vec3_dot)->Apply(bm_vec3_args);
BENCHMARK(bm_vec3_max)->Apply(bm_vec3_args);
BENCHMARK(bm_vec3_min)->Apply(bm_vec3_args);

void bm_quat_add(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const quaternion &v1 = *(quaternion *)state.range(0);
    const quaternion &v2 = *(quaternion *)state.range(1);
    benchmark::DoNotOptimize(v1 + v2);
  }
}

void bm_quat_mul(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const quaternion &v1 = *(quaternion *)state.range(0);
    const quaternion &v2 = *(quaternion *)state.range(1);
    benchmark::DoNotOptimize(v1 * v2);
  }
}

void bm_quat_lookat(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const quaternion &v1 = *(quaternion *)state.range(0);
    const quaternion &v2 = *(quaternion *)state.range(1);
    const vec3 x = {v1.x, v1.y, v1.z};
    const vec3 y = {v2.x, v2.y, v2.z};
    benchmark::DoNotOptimize(lookat(x, y));
  }
}

void bm_quat_inner_product_rough(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const quaternion &v1 = *(quaternion *)state.range(0);
    const quaternion &v2 = *(quaternion *)state.range(1);
    benchmark::DoNotOptimize(inner_product_rough(v1, v2));
  }
}

void bm_quat_inner_product_precise(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const quaternion &v1 = *(quaternion *)state.range(0);
    const quaternion &v2 = *(quaternion *)state.range(1);
    benchmark::DoNotOptimize(inner_product_precise(v1, v2));
  }
}

void bm_quat_conjugate(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const quaternion &v1 = *(quaternion *)state.range(0);
    benchmark::DoNotOptimize(conjugate(v1));
  }
}

void bm_quat_args(benchmark::internal::Benchmark *b) {
  std::uniform_real_distribution<float> rand(0, 10000);

  quaternion *x = new quaternion[256];
  quaternion *y = new quaternion[256];

  for (int i = 0; i < 256; i++) {
    x[i].x = rand(gen);
    x[i].y = rand(gen);
    x[i].z = rand(gen);
    x[i].w = rand(gen);
    y[i].x = rand(gen);
    y[i].y = rand(gen);
    y[i].z = rand(gen);
    y[i].w = rand(gen);
  }

  b->Args({(intptr_t)x, (intptr_t)y});
}

// Register the function as a benchmark
BENCHMARK(bm_quat_add)->Apply(bm_quat_args);
BENCHMARK(bm_quat_mul)->Apply(bm_quat_args);
BENCHMARK(bm_quat_lookat)->Apply(bm_quat_args);
BENCHMARK(bm_quat_inner_product_rough)->Apply(bm_quat_args);
BENCHMARK(bm_quat_inner_product_precise)->Apply(bm_quat_args);
BENCHMARK(bm_quat_conjugate)->Apply(bm_quat_args);

void bm_matrix4x4_add(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const matrix4x4 &v1 = *(matrix4x4 *)state.range(0);
    const matrix4x4 &v2 = *(matrix4x4 *)state.range(1);
    benchmark::DoNotOptimize(v1 + v2);
  }
}

void bm_matrix4x4_sub(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const matrix4x4 &v1 = *(matrix4x4 *)state.range(0);
    const matrix4x4 &v2 = *(matrix4x4 *)state.range(1);
    benchmark::DoNotOptimize(v1 - v2);
  }
}

void bm_matrix4x4_mul(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const matrix4x4 &v1 = *(matrix4x4 *)state.range(0);
    const matrix4x4 &v2 = *(matrix4x4 *)state.range(1);
    benchmark::DoNotOptimize(v1 * v2);
  }
}

void bm_matrix4x4_transpose(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const matrix4x4 &v1 = *(matrix4x4 *)state.range(0);
    benchmark::DoNotOptimize(transpose(v1));
  }
}

void bm_matrix4x4_cofactor(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const matrix4x4 &v1 = *(matrix4x4 *)state.range(0);
    benchmark::DoNotOptimize(cofactor(v1));
  }
}

void bm_matrix4x4_lookat(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const matrix4x4 &v1 = *(matrix4x4 *)state.range(0);
    const vec3 pos = {v1.m[0], v1.m[1], v1.m[2]};
    const vec3 target = {v1.m[3], v1.m[4], v1.m[5]};
    const vec3 up = {v1.m[6], v1.m[7], v1.m[8]};

    benchmark::DoNotOptimize(lookat(pos, target, up));
  }
}

void bm_matrix4x4_projection(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const matrix4x4 &v1 = *(matrix4x4 *)state.range(0);
    benchmark::DoNotOptimize(projection(v1.m[0], v1.m[1], v1.m[2], v1.m[3]));
  }
}

void bm_matrix4x4_projection_inf(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const matrix4x4 &v1 = *(matrix4x4 *)state.range(0);
    benchmark::DoNotOptimize(projection_inf(v1.m[0], v1.m[1], v1.m[2]));
  }
}

void bm_matrix4x4_projection_orthographic(benchmark::State &state) {
  while (state.KeepRunning()) {
    // This code gets timed
    const matrix4x4 &v1 = *(matrix4x4 *)state.range(0);
    benchmark::DoNotOptimize(
        projection_orthographic(v1.m[0], v1.m[1], v1.m[2], v1.m[3]));
  }
}

void bm_matrix4x4_args(benchmark::internal::Benchmark *b) {
  std::uniform_real_distribution<float> rand(0, 10000);
  matrix4x4 *x = new matrix4x4[256];
  matrix4x4 *y = new matrix4x4[256];

  for (int i = 0; i < 256; i++) {
    for (size_t j = 0; j < sizeof(matrix4x4::m) / sizeof(matrix4x4::m[0]);
         j++) {
      x[i].m[j] = rand(gen);
      x[i].m[j] = rand(gen);
    }
  }

  b->Args({(intptr_t)x, (intptr_t)y});
}

BENCHMARK(bm_matrix4x4_add)->Apply(bm_matrix4x4_args);
BENCHMARK(bm_matrix4x4_sub)->Apply(bm_matrix4x4_args);
BENCHMARK(bm_matrix4x4_mul)->Apply(bm_matrix4x4_args);
BENCHMARK(bm_matrix4x4_transpose)->Apply(bm_matrix4x4_args);
BENCHMARK(bm_matrix4x4_cofactor)->Apply(bm_matrix4x4_args);
BENCHMARK(bm_matrix4x4_lookat)->Apply(bm_matrix4x4_args);
BENCHMARK(bm_matrix4x4_projection)->Apply(bm_matrix4x4_args);
BENCHMARK(bm_matrix4x4_projection_inf)->Apply(bm_matrix4x4_args);
BENCHMARK(bm_matrix4x4_projection_orthographic)->Apply(bm_matrix4x4_args);

// Run the benchmark
BENCHMARK_MAIN();
