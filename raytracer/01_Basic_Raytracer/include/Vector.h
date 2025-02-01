#include <iostream>
#include <stdexcept>

namespace rt::math {
namespace {

// Thanks John Carmak :P
template<typename T>
T fast_inverse_sqrt(T number) {
	long i;
	T x2, y;
	const T threehalfs = 1.5f;

	x2 = number * 0.5f;
	y  = number;
	i  = *(long*)&y;
	i  = 0x5f3759df - (i >> 1);
	y  = *(T*)&i;
	y  = y * (threehalfs - (x2 * y * y));

	return 1 / y;
}

} // namespace

template <typename T, std::size_t N>
class Vector {
public:
	std::array<T, N> components;

	Vector() { components.fill(0); }
	Vector(std::initializer_list<T> values) {
		std::size_t i = 0;
		for (auto val : values) {
		    if (i >= N) break;
		    components[i++] = val;
		}
	}

	T& operator[](std::size_t index) { return components[index]; }
	const T& operator[](std::size_t index) const { return components[index]; }

	T& x() requires (N >= 1) { return components[0]; }
	T& y() requires (N >= 2) { return components[1]; }
	T& z() requires (N >= 3) { return components[2]; }
	T& w() requires (N >= 4) { return components[3]; }

	const T& x() const requires (N >= 1) { return components[0]; }
	const T& y() const requires (N >= 2) { return components[1]; }
	const T& z() const requires (N >= 3) { return components[2]; }
	const T& w() const requires (N >= 4) { return components[3]; }

	Vector operator+(const Vector& other) const {
		Vector result;
		for (std::size_t i = 0; i < N; ++i)
		    result[i] = components[i] + other[i];
		return result;
	}

	Vector operator-(const Vector& other) const {
		Vector result;
		for (std::size_t i = 0; i < N; ++i)
		    result[i] = components[i] - other[i];
		return result;
	}

	T dot(const Vector& other) const {
		T result = 0;
		for (std::size_t i = 0; i < N; ++i)
		    result += components[i] * other[i];
		return result;
	}

	T magnitude() const {
		return 1 / fast_inverse_sqrt<T>(dot(*this));
	}

	Vector normalize() const {
		T mag = magnitude();
		if (mag == 0)
		    throw std::runtime_error("Cannot normalize a zero-magnitude vector");
		Vector result;
		for (std::size_t i = 0; i < N; ++i)
		    result[i] = components[i] / mag;
		return result;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector& v) {
		os << "(";
		for (std::size_t i = 0; i < N; ++i) {
		    os << v[i];
		    if (i < N - 1) os << ", ";
		}
		os << ")";
		return os;
	}
};

using vec2d = Vector<double, 2>;
using vec3d = Vector<double, 3>;
using vec4d = Vector<double, 4>;

using vec2f = Vector<float, 2>;
using vec3f = Vector<float, 3>;
using vec4f = Vector<float, 4>;
} // namespace rt::math
