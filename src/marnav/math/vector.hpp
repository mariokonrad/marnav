#ifndef __MATH__VECTOR_HPP__
#define __MATH__VECTOR_HPP__

#include <cmath>
#include <limits>

namespace marnav
{
namespace math
{

/// A 2D vector.
///
/// @tparam T Basic data type, must be a floating point type.
///
template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class vector2
{
public:
	using value_type = T;

public:
	vector2(value_type x = 0.0, value_type y = 0.0)
	{
		a[0] = x;
		a[1] = y;
	}

	vector2(const vector2 &) = default;

	vector2(vector2 &&) = default;

	/// Returns a vector, initialized by the polar coordinates.
	///
	/// @param[in] radius Radius for the vector.
	/// @param[in] phi Angle Phi in degrees.
	/// @return A 2D vector.
	static inline vector2 make_from_polar(value_type radius, value_type phi_deg)
	{
		const value_type phi = phi_deg * M_PI / 180.0;
		return vector2{radius * cos(phi), radius * sin(phi)};
	}

	/// Returns the angle of polar coordinate in the interval 0..2pi in radiants
	inline value_type phi() const
	{
		value_type p = atan2(a[1], a[0]);
		if (p < 0)
			p += 2.0 * M_PI;
		return p;
	}

	/// Returns the angle of polar coordinate in the interval 0..2pi in degrees
	inline value_type phi_deg() const { return phi() * 180.0 / M_PI; }

	/// Calculates the dot product.
	inline value_type dot(const vector2 & v) const { return a[0] * v.a[0] + a[1] * v.a[1]; }

	/// Returns the length of the vector.
	inline value_type length() const { return sqrt(length2()); }

	/// Returns the square of the length of the vector. This is useful if the
	/// extra calculation of square root, done by the function 'length' is
	/// not necessary or not desired.
	inline value_type length2() const { return a[0] * a[0] + a[1] * a[1]; }

	/// Normalizes the vector to a specific length.
	inline vector2 & normalize(value_type len = 1.0)
	{
		const value_type l = length();
		if (abs(l) > std::numeric_limits<value_type>::epsilon())
			*this *= len / l;
		return *this;
	}

	/// Set all components of the vector that are below epsilon to exact zero.
	inline vector2 & nullify(void)
	{
		constexpr const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		a[0] = abs(a[0]) <= EPSILON ? 0.0 : a[0];
		a[1] = abs(a[1]) <= EPSILON ? 0.0 : a[1];
		return *this;
	}

	inline value_type x() const { return a[0]; }

	inline value_type y() const { return a[1]; }

	inline value_type operator[](int idx) const { return a[idx]; }

	inline vector2 & operator=(const vector2 &) = default;

	inline vector2 & operator=(vector2 &&) = default;

	inline bool operator==(const vector2 & v) const
	{
		return (this == &v) || ((a[0] == v.a[0]) && (a[1] == v.a[1]));
	}

	inline bool operator!=(const vector2 & v) const { return !(*this == v); }

	inline vector2 & operator+=(const vector2 & v)
	{
		a[0] += v.a[0];
		a[1] += v.a[1];
		return *this;
	}

	inline vector2 & operator-=(const vector2 & v)
	{
		a[0] -= v.a[0];
		a[1] -= v.a[1];
		return *this;
	}

	inline vector2 & operator*=(value_type f)
	{
		a[0] *= f;
		a[1] *= f;
		return *this;
	}

	friend vector2 operator+(const vector2 & w, const vector2 & v) { return vector2{w} += v; }

	friend vector2 operator-(const vector2 & w, const vector2 & v) { return vector2{w} -= v; }

	friend vector2 operator*(const vector2 & v, value_type f) { return vector2{v} *= f; }

	friend vector2 operator*(value_type f, const vector2 & v) { return vector2{v} *= f; }

	friend value_type operator*(const vector2 & a, const vector2 & b) { return a.dot(b); }

private:
	value_type a[2];
};

template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class vector3
{
public:
	using value_type = T;

public:
	vector3(value_type x = 0.0, value_type y = 0.0, value_type z = 0.0)
	{
		a[0] = x;
		a[1] = y;
		a[2] = z;
	}

	vector3(const vector3 &) = default;

	vector3(vector3 &&) = default;

	/// Returns a vector, initialized by the sphere coordinates.
	static inline vector3 make_from_sphere(
		value_type radius, value_type phi_deg, value_type rho_deg)
	{
		const value_type phi = phi_deg * M_PI / 180.0;
		const value_type rho = rho_deg * M_PI / 180.0;
		return vector3{
			radius * cos(phi) * sin(rho), radius * sin(phi) * sin(rho), radius * cos(rho)};
	}

	inline value_type dot(const vector3 & v) const
	{
		return a[0] * v.a[0] + a[1] * v.a[1] + a[2] * v.a[2];
	}

	inline vector3 cross(const vector3 & v) const
	{
		return vector3(a[1] * v.a[2] - a[2] * v.a[1], a[2] * v.a[0] - a[0] * v.a[2],
			a[0] * v.a[1] - a[1] * v.a[0]);
	}

	/// Set all components of the vector that are below epsilon to exact zero.
	inline vector3 & nullify(void)
	{
		constexpr const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		a[0] = abs(a[0]) <= EPSILON ? 0.0 : a[0];
		a[1] = abs(a[1]) <= EPSILON ? 0.0 : a[1];
		a[2] = abs(a[2]) <= EPSILON ? 0.0 : a[2];
		return *this;
	}

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const { return a[0] * a[0] + a[1] * a[1] + a[2] * a[2]; }

	inline vector3 & normalize(value_type len = 1.0)
	{
		value_type l = length();
		if (abs(l) > std::numeric_limits<value_type>::epsilon())
			*this *= len / l;
		return *this;
	}

	inline value_type get_sphere_r() const { return length(); }

	inline value_type get_sphere_rho() const
	{
		value_type b = sqrt(a[0] * a[0] + a[1] * a[1]);
		return (b != 0.0) ? (atan(a[2] / b) * 180.0 / M_PI) : 0.0;
	}

	inline value_type get_sphere_phi() const
	{
		value_type b = atan2(a[1], a[0]);
		if (b < 0)
			b += 2.0 * M_PI;
		return b;
	}

	inline value_type x() const { return a[0]; }

	inline value_type y() const { return a[1]; }

	inline value_type z() const { return a[2]; }

	inline value_type operator[](int idx) const { return a[idx]; }

	inline value_type & operator[](int idx) { return a[idx]; }

	inline operator const value_type *(void) const { return a; }

	inline vector3 & operator=(const vector3 &) = default;

	inline vector3 & operator=(vector3 &&) = default;

	inline bool operator==(const vector3 & v) const
	{
		return (this == &v) || ((a[0] == v.a[0]) && (a[1] == v.a[1]) && (a[2] == v.a[2]));
	}

	inline bool operator!=(const vector3 & v) const { return !(*this == v); }

	inline vector3 & operator+=(const vector3 & v)
	{
		a[0] += v.a[0];
		a[1] += v.a[1];
		a[2] += v.a[2];
		return *this;
	}

	inline vector3 & operator-=(const vector3 & v)
	{
		a[0] -= v.a[0];
		a[1] -= v.a[1];
		a[2] -= v.a[2];
		return *this;
	}

	inline vector3 & operator*=(value_type f)
	{
		a[0] *= f;
		a[1] *= f;
		a[2] *= f;
		return *this;
	}

	friend vector3 operator+(const vector3 & w, const vector3 & v) { return vector3{w} += v; }

	friend vector3 operator-(const vector3 & w, const vector3 & v) { return vector3{w} -= v; }

	friend vector3 operator*(const vector3 & v, value_type f) { return vector3{v} *= f; }

	friend vector3 operator*(value_type f, const vector3 & v) { return vector3{v} *= f; }

	friend value_type operator*(const vector3 & a, const vector3 & b) { return a.dot(b); }

private:
	value_type a[3];
};

template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class vector4
{
public:
	using value_type = T;

public:
	vector4(value_type x = 0.0, value_type y = 0.0, value_type z = 0.0, value_type w = 0.0)
	{
		a[0] = x;
		a[1] = y;
		a[2] = z;
		a[3] = w;
	}

	vector4(const vector4 &) = default;

	vector4(vector4 &&) = default;

	inline value_type dot(const vector4 & v) const
	{
		return a[0] * v.a[0] + a[1] * v.a[1] + a[2] * v.a[2] + a[3] * v.a[3];
	}

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const
	{
		return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3];
	}

	inline vector4 & normalize(value_type len = 1.0)
	{
		value_type l = length();
		if (abs(l) > std::numeric_limits<value_type>::epsilon())
			*this *= (len / l);
		return *this;
	}

	/// Set all components of the vector that are below epsilon to exact zero.
	inline vector4 & nullify(void)
	{
		constexpr const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		a[0] = abs(a[0]) <= EPSILON ? 0.0 : a[0];
		a[1] = abs(a[1]) <= EPSILON ? 0.0 : a[1];
		a[2] = abs(a[2]) <= EPSILON ? 0.0 : a[2];
		a[3] = abs(a[3]) <= EPSILON ? 0.0 : a[3];
		return *this;
	}

	inline value_type operator[](int idx) const { return a[idx]; }

	inline vector4 & operator=(const vector4 &) = default;

	inline vector4 & operator=(vector4 &&) = default;

	inline bool operator==(const vector4 & v) const
	{
		return (this == &v)
			|| ((a[0] == v.a[0]) && (a[1] == v.a[1]) && (a[2] == v.a[2]) && (a[3] == v.a[3]));
	}

	inline bool operator!=(const vector4 & v) const { return !(*this == v); }

	inline vector4 & operator+=(const vector4 & v)
	{
		a[0] += v.a[0];
		a[1] += v.a[1];
		a[2] += v.a[2];
		a[3] += v.a[3];
		return *this;
	}

	inline vector4 & operator-=(const vector4 & v)
	{
		a[0] -= v.a[0];
		a[1] -= v.a[1];
		a[2] -= v.a[2];
		a[3] -= v.a[3];
		return *this;
	}

	inline vector4 & operator*=(value_type f)
	{
		a[0] *= f;
		a[1] *= f;
		a[2] *= f;
		a[3] *= f;
		return *this;
	}

	friend vector4 operator+(const vector4 & w, const vector4 & v) { return vector4(w) += v; }

	friend vector4 operator-(const vector4 & w, const vector4 & v) { return vector4(w) -= v; }

	friend vector4 operator*(const vector4 & v, value_type f) { return vector4(v) *= f; }

	friend vector4 operator*(value_type f, const vector4 & v) { return vector4(v) *= f; }

	friend value_type operator*(const vector4 & a, const vector4 & b) { return a.dot(b); }

private:
	value_type a[4];
};

template <unsigned int N, typename T = double,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class vector_n
{
public:
	using value_type = T;

	vector_n()
	{
		static_assert(N >= 1, "invalid dimension of vector_n, constraint: N>=1");

		for (unsigned int i = 0; i < N; ++i)
			a[i] = 0.0;
	}

	vector_n(const vector_n &) = default;

	vector_n(vector_n &&) = default;

	vector_n(std::initializer_list<T> v)
	{
		assert(v.size() == N);
		unsigned int i = 0;
		for (auto j = begin(v); j != end(v); ++i, ++j)
			a[i] = *j;
	}

	inline value_type dot(const vector_n & v) const
	{
		value_type r = 0.0;
		for (unsigned int i = 0; i < N; ++i)
			r += (a[i] * v.a[i]);
		return r;
	}

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const
	{
		value_type r = 0.0;
		for (unsigned int i = 0; i < N; ++i)
			r += (a[i] * a[i]);
		return r;
	}

	inline vector_n & normalize(value_type len = 1.0)
	{
		value_type l = length();
		if (abs(l) > std::numeric_limits<value_type>::epsilon())
			*this *= len / l;
		return *this;
	}

	inline value_type operator[](int idx) const { return a[idx]; }

	inline value_type & operator[](int idx) { return a[idx]; }

	inline vector_n & operator=(const vector_n &) = default;

	inline vector_n & operator=(vector_n &&) = default;

	inline bool operator==(const vector_n & v) const
	{
		if (this == &v)
			return true;
		for (unsigned int i = 0; i < N; ++i)
			if (a[i] != v.a[i])
				return false;
		return true;
	}

	inline bool operator!=(const vector_n & v) const { return !(*this == v); }

	inline vector_n & operator+=(const vector_n & v)
	{
		for (unsigned int i = 0; i < N; ++i)
			a[i] += v.a[i];
		return *this;
	}

	inline vector_n & operator-=(const vector_n & v)
	{
		for (unsigned int i = 0; i < N; ++i)
			a[i] -= v.a[i];
		return *this;
	}

	inline vector_n & operator*=(value_type f)
	{
		for (unsigned int i = 0; i < N; ++i)
			a[i] *= f;
		return *this;
	}

	friend vector_n operator+(const vector_n & w, const vector_n & v)
	{
		return vector_n{w} += v;
	}

	friend vector_n operator-(const vector_n & w, const vector_n & v)
	{
		return vector_n{w} -= v;
	}

	friend vector_n operator*(const vector_n & v, value_type f) { return vector_n{v} *= f; }

	friend vector_n operator*(value_type f, const vector_n & v) { return vector_n{v} *= f; }

	friend value_type operator*(const vector_n & a, const vector_n & b) { return a.dot(b); }

private:
	value_type a[N];
};

using vec2 = vector2<double>;
using vec3 = vector3<double>;
using vec4 = vector4<double>;

/// @{
/// Returns a new constructed, normalized vector of the specified one.

template <typename T> vector2<T> normalize_vec(const vector2<T> & v)
{
	vector2<T> t{v};
	t.normalize();
	return t;
}

template <typename T> vector3<T> normalize_vec(const vector3<T> & v)
{
	vector3<T> t{v};
	t.normalize();
	return t;
}

template <typename T> vector3<T> normalize_vec(const vector4<T> & v)
{
	vector4<T> t{v};
	t.normalize();
	return t;
}

/// @}

/// @{
/// Returns the angle between the two specified vectors in degrees.

template <typename T> T angle_between(const vector2<T> & v0, const vector2<T> & v1)
{
	return acos(v0.dot(v1) / (v0.length() * v1.length()));
}

template <typename T> T angle_between(const vector3<T> & p0, const vector3<T> & p1)
{
	return acos(p0.dot(p1) / (p0.length() * p1.length()));
}

/// @}

/// @{
/// Returns a newly constructed vector which is a projection of \c v0 onto \c v1.

template <typename T> vector2<T> project_onto(const vector2<T> & v0, const vector2<T> & v1)
{
	typename vector2<T>::value_type len = v1.length2();
	if (abs(len) <= std::numeric_limits<typename vector2<T>::value_type>::epsilon())
		return vector2<T>{};
	return ((v0 * v1) / len) * v1;
}

template <typename T> vector2<T> project_onto(const vector3<T> & v0, const vector3<T> & v1)
{
	typename vector3<T>::value_type len = v1.length2();
	if (abs(len) <= std::numeric_limits<typename vector3<T>::value_type>::epsilon())
		return vector3<T>{};
	return ((v0 * v1) / len) * v1;
}

/// @}

}
}

#endif
