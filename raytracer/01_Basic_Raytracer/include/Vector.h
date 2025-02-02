#pragma once
#include <iostream>
#include <stdexcept>

namespace rt::math {
namespace {

// Thanks John Carmak :P
template<typename T>
T fast_inverse_sqrt(T number) {
	if (number <= 0) return std::numeric_limits<T>::infinity();

	using IntType = typename std::conditional<std::is_same<T, float>::value, uint32_t, uint64_t>::type;
	T x2 = number * 0.5f;
	T y  = number;
	IntType i = *(IntType*)&y;
	i = (std::is_same<T, float>::value ? 0x5F3759DF : 0x5FE6EB50C7B537A9) - (i >> 1);
	y = *(T*)&i;
	y = y * (1.5f - (x2 * y * y));

	return y;
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

	Vector operator*(T scalar) const {
		Vector result;
		for (std::size_t i = 0; i < N; ++i)
		    result[i] = components[i] * scalar;
		return result;
	}

	Vector operator/(T scalar) const {
		Vector result;
		for (std::size_t i = 0; i < N; ++i)
		    result[i] = components[i] / scalar;
		return result;
	}

	T dot(const Vector& other) const {
		T result = 0;
		for (std::size_t i = 0; i < N; ++i)
		    result += components[i] * other[i];
		return result;
	}

	template <typename U = T>
	Vector cross(const Vector<U, N>& other) const {
		static_assert(N == 3, "Cross product is only defined for 3D vectors");

		return Vector({
		    components[1] * other.components[2] - components[2] * other.components[1],
		    components[2] * other.components[0] - components[0] * other.components[2],
		    components[0] * other.components[1] - components[1] * other.components[0]
		});
	}

	T magnitude() const {
		T dotProduct = dot(*this);
		if (dotProduct == 0)
			return 0;
		//We loose some FPSs using the default sqrt implementation but we'll see how bad it is or if we can live with that.
		return std::sqrt(dotProduct);
		/*return 1 / fast_inverse_sqrt<T>(dotProduct);*/
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
