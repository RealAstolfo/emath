CC = gcc
CXX = g++
LD = ld
AR = ar
AS = as

INC = -I./include -I./vendors
LIB =  -L. -L/usr/lib64 -L/usr/local/lib64

CFLAGS = -march=native -O3 -pg -Wall -Wextra -pedantic $(INC)
CXXFLAGS = -std=c++20 $(CFLAGS)
LDFLAGS = $(LIB) -O3

# Math
matrix4x4.o:
	${CXX} ${CXXFLAGS} -c src/matrix4x4.cpp -o $@

quaternion.o:
	${CXX} ${CXXFLAGS} -c src/quaternion.cpp -o $@

vec2.o:
	${CXX} ${CXXFLAGS} -c src/vec2.cpp -o $@

vec3.o:
	${CXX} ${CXXFLAGS} -c src/vec3.cpp -o $@

math.o: matrix4x4.o quaternion.o vec2.o vec3.o
	${LD} -r $^ -o $@

#########################################################################################

# Mathematics Benchmarking
#########################################################################################

math-benchmark.o:
	${CXX} ${CXXFLAGS} -c builds/benchmark/math_benchmark.cpp -o $@

math-benchmark: math.o math-benchmark.o
	${CXX} ${CXXFLAGS} -lbenchmark $^ -o $@

all: math-benchmark

clean:
	-rm -f math-benchmark *.o
