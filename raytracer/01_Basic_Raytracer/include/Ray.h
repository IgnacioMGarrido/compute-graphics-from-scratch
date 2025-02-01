#pragma once
#include "Vector.h"

namespace rt::math {

template<typename T, std::size_t N>
class Ray {
public:
	Ray(const Vector<T, N>& i_from, const Vector<T, N>& i_to) 
	: m_from(i_from)
	, m_to(i_to)
	{}

	Vector<T, N> From() const { return m_from; };
	Vector<T, N> To() const { return m_to; };
	Vector<T, N> Diff() const { return m_from - m_to; };
	Vector<T, N> Dir() const { return Diff().normalize(); };
private:
	Vector<T, N> m_from;
	Vector<T, N> m_to;
	Vector<T, N> m_diff;

};

using Ray2d = Ray<double, 2>;
using Ray3d = Ray<double, 3>;

using Ray2f = Ray<float, 2>;
using Ray3f = Ray<float, 3>;
} // namespace rt::math
