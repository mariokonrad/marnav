#ifndef MARNAV__MATH__VECTOR__HPP
#define MARNAV__MATH__VECTOR__HPP

#include <initializer_list>
#include <type_traits>
#include <marnav/math/floatingpoint.hpp>
#include <marnav/math/constants.hpp>

namespace marnav
{
namespace math
{

/// @cond DEV
namespace detail
{

/// Returns the dot product for the specified vector.
template <typename T, typename
	= typename std::enable_if<std::is_floating_point<typename T::value_type>::value, T>::type>
typename T::value_type dot_vector(const T & a, const T & b)
{
	using index = typename std::remove_cv<decltype(T::dimension)>::type;

	typename T::value_type result = 0.0;
	for (index i = 0; i < T::dimension; ++i)
		result += a[i] * b[i];
	return result;
}

/// Returns true if both vectors are the same.
template <typename T, typename
	= typename std::enable_if<std::is_floating_point<typename T::value_type>::value, T>::type>
bool equal_vector(const T & a, const T & b)
{
	if (&a == &b)
		return true;

	using index = typename std::remove_cv<decltype(T::dimension)>::type;

	for (index i = 0; i < T::dimension; ++i)
		if (!is_same(a[i], b[i]))
			return false;
	return true;
}

/// Normalizes the specified vector the desired length.
template <typename T, typename
	= typename std::enable_if<std::is_floating_point<typename T::value_type>::value, T>::type>
void normalize_vector(T & a, typename T::value_type len)
{
	const typename T::value_type l = a.length();
	if (!is_zero(l))
		a *= len / l;
}
}
/// @endcond

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
	using size_type = unsigned int;

	constexpr static const size_type dimension = 2;

public:
	vector2(value_type x = 0.0, value_type y = 0.0)
	{
		a[0] = x;
		a[1] = y;
	}

	vector2(const vector2 &) = default;

	vector2(vector2 &&) noexcept = default;

	/// Returns a vector, initialized by the polar coordinates.
	///
	/// @param[in] radius Radius for the vector.
	/// @param[in] phi_deg Angle Phi in degrees.
	/// @return A 2D vector.
	static inline vector2 make_from_polar(value_type radius, value_type phi_deg)
	{
		const value_type phi = phi_deg * pi / 180.0;
		return vector2{radius * cos(phi), radius * sin(phi)};
	}

	/// Returns the angle of polar coordinate in the interval 0..2pi in radiants
	inline value_type phi() const
	{
		value_type p = atan2(a[1], a[0]);
		if (p < 0)
			p += 2.0 * pi;
		return p;
	}

	/// Returns the angle of polar coordinate in the interval 0..2pi in degrees
	inline value_type phi_deg() const { return phi() * 180.0 / pi; }

	/// Calculates the dot product.
	inline value_type dot(const vector2 & v) const { return detail::dot_vector(*this, v); }

	/// Returns the length of the vector.
	inline value_type length() const { return std::sqrt(length2()); }

	/// Returns the square of the length of the vector. This is useful if the
	/// extra calculation of square root, done by the function 'length' is
	/// not necessary or not desired.
	inline value_type length2() const { return detail::dot_vector(*this, *this); }

	/// Normalizes the vector to a specific length.
	inline vector2 & normalize(value_type len = 1.0)
	{
		detail::normalize_vector(*this, len);
		return *this;
	}

	/// Normalizes the vector to a specific length.
	inline vector2 normalize(value_type len = 1.0) const
	{
		return vector2{*this}.normalize(len);
	}

	inline value_type x() const { return a[0]; }

	inline value_type y() const { return a[1]; }

	inline value_type operator[](size_type idx) const { return a[idx]; }

	inline value_type & operator[](size_type idx) { return a[idx]; }

	inline vector2 & operator=(const vector2 &) = default;

	inline vector2 & operator=(vector2 &&) noexcept = default;

	inline bool operator==(const vector2 & v) const { return detail::equal_vector(*this, v); }

	inline bool operator!=(const vector2 & v) const { return !(*this == v); }

	inline vector2 & operator+=(const vector2 & v)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] += v.a[i];
		return *this;
	}

	inline vector2 & operator-=(const vector2 & v)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] -= v.a[i];
		return *this;
	}

	inline vector2 & operator*=(value_type f)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] *= f;
		return *this;
	}

	friend vector2 operator+(const vector2 & w, const vector2 & v) { return vector2{w} += v; }

	friend vector2 operator-(const vector2 & w, const vector2 & v) { return vector2{w} -= v; }

	friend vector2 operator*(const vector2 & v, value_type f) { return vector2{v} *= f; }

	friend vector2 operator*(value_type f, const vector2 & v) { return vector2{v} *= f; }

	friend value_type operator*(const vector2 & a, const vector2 & b) { return a.dot(b); }

private:
	value_type a[dimension];
};

/// A 3D vector.
///
/// @tparam T Basic data type, must be a floating point type.
///
template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class vector3
{
public:
	using value_type = T;
	using size_type = unsigned int;

	constexpr static const size_type dimension = 3;

public:
	vector3(value_type x = 0.0, value_type y = 0.0, value_type z = 0.0)
	{
		a[0] = x;
		a[1] = y;
		a[2] = z;
	}

	vector3(const vector3 &) = default;

	vector3(vector3 &&) noexcept = default;

	/// Returns a vector, initialized by the sphere coordinates (mathematical conventions).
	///
	/// @param[in] radius The radius component.
	/// @param[in] theta_deg The angle theta, lying on the xy-plane
	/// @param[in] phi_deg The angle phi, from the z-axis
	static inline vector3 make_from_sphere(
		value_type radius, value_type theta_deg, value_type phi_deg)
	{
		const value_type phi = phi_deg * pi / 180.0;
		const value_type theta = theta_deg * pi / 180.0;
		return vector3{radius * std::sin(theta) * std::cos(phi),
			radius * std::sin(theta) * std::sin(phi), radius * std::cos(theta)};
	}

	inline value_type dot(const vector3 & v) const { return detail::dot_vector(*this, v); }

	inline vector3 cross(const vector3 & v) const
	{
		return vector3(a[1] * v.a[2] - a[2] * v.a[1], a[2] * v.a[0] - a[0] * v.a[2],
			a[0] * v.a[1] - a[1] * v.a[0]);
	}

	inline value_type length() const { return std::sqrt(length2()); }

	inline value_type length2() const { return detail::dot_vector(*this, *this); }

	inline vector3 & normalize(value_type len = 1.0)
	{
		detail::normalize_vector(*this, len);
		return *this;
	}

	/// Normalizes the vector to a specific length.
	inline vector3 normalize(value_type len = 1.0) const
	{
		return vector3{*this}.normalize(len);
	}

	inline value_type get_sphere_r() const { return length(); }

	inline value_type get_sphere_theta() const
	{
		const value_type len = length();
		if (is_zero(len))
			return 0.0;
		return std::acos(a[2] / len) * 180.0 / pi;
	}

	inline value_type get_sphere_phi() const
	{
		value_type b = std::atan2(a[1], a[0]);
		if (b < 0.0)
			b += 2.0 * pi;
		return b * 180.0 / pi;
	}

	inline value_type x() const { return a[0]; }

	inline value_type y() const { return a[1]; }

	inline value_type z() const { return a[2]; }

	inline value_type operator[](size_type idx) const { return a[idx]; }

	inline value_type & operator[](size_type idx) { return a[idx]; }

	inline operator const value_type *() const { return a; }

	inline vector3 & operator=(const vector3 &) = default;

	inline vector3 & operator=(vector3 &&) noexcept = default;

	inline bool operator==(const vector3 & v) const { return detail::equal_vector(*this, v); }

	inline bool operator!=(const vector3 & v) const { return !(*this == v); }

	inline vector3 & operator+=(const vector3 & v)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] += v.a[i];
		return *this;
	}

	inline vector3 & operator-=(const vector3 & v)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] -= v.a[i];
		return *this;
	}

	inline vector3 & operator*=(value_type f)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] *= f;
		return *this;
	}

	friend vector3 operator+(const vector3 & w, const vector3 & v) { return vector3{w} += v; }

	friend vector3 operator-(const vector3 & w, const vector3 & v) { return vector3{w} -= v; }

	friend vector3 operator*(const vector3 & v, value_type f) { return vector3{v} *= f; }

	friend vector3 operator*(value_type f, const vector3 & v) { return vector3{v} *= f; }

	friend value_type operator*(const vector3 & a, const vector3 & b) { return a.dot(b); }

private:
	value_type a[dimension];
};

/// A 4D vector.
///
/// @tparam T Basic data type, must be a floating point type.
///
template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class vector4
{
public:
	using value_type = T;
	using size_type = unsigned int;

	constexpr static const size_type dimension = 4;

public:
	vector4(value_type x = 0.0, value_type y = 0.0, value_type z = 0.0, value_type w = 0.0)
	{
		a[0] = x;
		a[1] = y;
		a[2] = z;
		a[3] = w;
	}

	vector4(const vector4 &) = default;

	vector4(vector4 &&) noexcept = default;

	inline value_type dot(const vector4 & v) const { return detail::dot_vector(*this, v); }

	inline value_type length() const { return std::sqrt(length2()); }

	inline value_type length2() const { return detail::dot_vector(*this, *this); }

	inline vector4 & normalize(value_type len = 1.0)
	{
		detail::normalize_vector(*this, len);
		return *this;
	}

	/// Normalizes the vector to a specific length.
	inline vector4 normalize(value_type len = 1.0) const
	{
		return vector4{*this}.normalize(len);
	}

	inline value_type operator[](size_type idx) const { return a[idx]; }

	inline value_type & operator[](size_type idx) { return a[idx]; }

	inline vector4 & operator=(const vector4 &) = default;

	inline vector4 & operator=(vector4 &&) noexcept = default;

	inline bool operator==(const vector4 & v) const { return detail::equal_vector(*this, v); }

	inline bool operator!=(const vector4 & v) const { return !(*this == v); }

	inline vector4 & operator+=(const vector4 & v)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] += v.a[i];
		return *this;
	}

	inline vector4 & operator-=(const vector4 & v)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] -= v.a[i];
		return *this;
	}

	inline vector4 & operator*=(value_type f)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] *= f;
		return *this;
	}

	friend vector4 operator+(const vector4 & w, const vector4 & v) { return vector4{w} += v; }

	friend vector4 operator-(const vector4 & w, const vector4 & v) { return vector4{w} -= v; }

	friend vector4 operator*(const vector4 & v, value_type f) { return vector4{v} *= f; }

	friend vector4 operator*(value_type f, const vector4 & v) { return vector4{v} *= f; }

	friend value_type operator*(const vector4 & a, const vector4 & b) { return a.dot(b); }

private:
	value_type a[dimension];
};

/// A n-dimensional vector.
///
/// @tparam N Dimension of the vector
/// @tparam T Basic data type, must be a floating point type.
///
template <unsigned int N, typename T = double,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class vector_n
{
public:
	using value_type = T;
	using size_type = decltype(N);

	constexpr static const size_type dimension = N;

	vector_n()
	{
		static_assert(N >= 1, "invalid dimension of vector_n, constraint: N>=1");

		for (size_type i = 0; i < dimension; ++i)
			a[i] = 0.0;
	}

	vector_n(const vector_n &) = default;

	vector_n(vector_n &&) noexcept = default;

	vector_n(std::initializer_list<T> v)
	{
		assert(v.size() == N);
		size_type i = 0;
		for (auto j = begin(v); j != end(v); ++i, ++j)
			a[i] = *j;
	}

	inline value_type dot(const vector_n & v) const { return detail::dot_vector(*this, v); }

	inline value_type length() const { return std::sqrt(length2()); }

	inline value_type length2() const { return detail::dot_vector(*this, *this); }

	inline vector_n & normalize(value_type len = 1.0)
	{
		detail::normalize_vector(*this, len);
		return *this;
	}

	/// Normalizes the vector to a specific length.
	inline vector_n normalize(value_type len = 1.0) const
	{
		return vector_n{*this}.normalize(len);
	}

	inline value_type operator[](size_type idx) const { return a[idx]; }

	inline value_type & operator[](size_type idx) { return a[idx]; }

	inline vector_n & operator=(const vector_n &) = default;

	inline vector_n & operator=(vector_n &&) noexcept = default;

	inline bool operator==(const vector_n & v) const { return detail::equal_vector(*this, v); }

	inline bool operator!=(const vector_n & v) const { return !(*this == v); }

	inline vector_n & operator+=(const vector_n & v)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] += v.a[i];
		return *this;
	}

	inline vector_n & operator-=(const vector_n & v)
	{
		for (size_type i = 0; i < dimension; ++i)
			a[i] -= v.a[i];
		return *this;
	}

	inline vector_n & operator*=(value_type f)
	{
		for (size_type i = 0; i < dimension; ++i)
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
	value_type a[dimension];
};

using vec2 = vector2<double>;
using vec3 = vector3<double>;
using vec4 = vector4<double>;

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
	if (is_zero(len))
		return vector2<T>{};
	return ((v0 * v1) / len) * v1;
}

template <typename T> vector3<T> project_onto(const vector3<T> & v0, const vector3<T> & v1)
{
	typename vector3<T>::value_type len = v1.length2();
	if (is_zero(len))
		return vector3<T>{};
	return ((v0 * v1) / len) * v1;
}

/// @}

/// @{

/// Set all components of the vector that are below epsilon to exact zero.
///
/// @param[inout] v The vector to nullify
/// @return The nullified vector
///
template <typename T, typename
	= typename std::enable_if<std::is_floating_point<typename T::value_type>::value, T>::type>
T & nullify(T & v)
{
	using index = typename std::remove_cv<decltype(T::dimension)>::type;

	for (index i = 0; i < T::dimension; ++i)
		v[i] = is_zero(v[i]) ? 0.0 : v[i];
	return v;
}

/// Set all components of the vector that are below epsilon to exact zero.
///
/// @param[in] v The vector to nullify, will not be modified
/// @return A nullified vector
///
template <typename T, typename
	= typename std::enable_if<std::is_floating_point<typename T::value_type>::value, T>::type>
T nullify(const T & v)
{
	return nullify(T{v});
}

/// @}
}
}

#endif
