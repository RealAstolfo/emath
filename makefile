CXX = clang++

INC = -I./include -I./vendors
LIB =  -L. -L/usr/lib64 -L/usr/local/lib64

CFLAGS = -march=native -O3 -flto -fno-sanitize=all -Wall -Wextra -pedantic $(INC)
CXXFLAGS = -std=c++20 $(CFLAGS)
LDFLAGS = $(LIB) -O3

BENCHMARK = `pkg-config --cflags --libs benchmark`

# Rules for creating object files
matrix4x4.o:
	${CXX} ${CXXFLAGS} -c src/matrix4x4.cpp -o $@

quaternion.o:
	${CXX} ${CXXFLAGS} -c src/quaternion.cpp -o $@

vec2.o:
	${CXX} ${CXXFLAGS} -c src/vec2.cpp -o $@

vec3.o:
	${CXX} ${CXXFLAGS} -c src/vec3.cpp -o $@

MATH = matrix4x4.o quaternion.o vec2.o vec3.o

# Rule for creating the benchmark executable
math-benchmark: ${MATH}
	${CXX} ${CXXFLAGS} builds/benchmark/math_benchmark.cpp $^ ${BENCHMARK} -o $@

all: math-benchmark

clean:
	-rm -f math-benchmark *.o
