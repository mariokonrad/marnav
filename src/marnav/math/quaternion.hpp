#ifndef __MATH__QUATERNION__HPP__
#define __MATH__QUATERNION__HPP__

#include <marnav/math/vector.hpp>
#include <cmath>
#include <cassert>

namespace marnav
{
namespace math
{

template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class quaternion
{
public:
	using value_type = T;

	enum class part { w, x, y, z };

	quaternion(value_type w = 1.0, value_type x = 0.0, value_type y = 0.0, value_type z = 0.0)
		: w(w)
		, x(x)
		, y(y)
		, z(z)
	{
	}

	quaternion(const quaternion &) = default;

	quaternion(quaternion &&) = default;

	quaternion(const vector3<T> & v)
	{
		w = 0.0;
		x = v[0];
		y = v[1];
		z = v[2];
	}

	/// Creates a quaternion for 3D rotation.
	///
	/// @param[in] angle The rotation angle in degrees
	/// @param[in] axis The rotation axis
	quaternion(value_type angle, const vector3<T> & axis)
	{
		const value_type d = axis.length();
		assert(abs(d) > std::numeric_limits<value_type>::epsilon());

		// conversion deg -> rad
		angle *= M_PI / 180.0;

		// sin(phi / 2) with normalization
		value_type s = sin(angle * 0.5) / d;

		w = cos(angle * 0.5);
		x = axis[0] * s;
		y = axis[1] * s;
		z = axis[2] * s;
	}

	static quaternion make_from_euler(value_type yaw, value_type pitch, value_type roll)
	{
		quaternion q;
		q.euler(yaw, pitch, roll);
		return q;
	}

	quaternion & euler(value_type yaw, value_type pitch, value_type roll)
	{
		yaw *= (M_PI / 180.0) / 2.0;
		pitch *= (M_PI / 180.0) / 2.0;
		roll *= (M_PI / 180.0) / 2.0;
		const value_type c_yaw = cos(yaw);
		const value_type s_yaw = sin(yaw);
		const value_type c_pitch = cos(pitch);
		const value_type s_pitch = sin(pitch);
		const value_type c_roll = cos(roll);
		const value_type s_roll = sin(roll);

		w = c_roll * c_pitch * c_yaw + s_roll * s_pitch * s_yaw;
		x = c_roll * s_pitch * c_yaw + s_roll * c_pitch * s_yaw;
		y = c_roll * c_pitch * s_yaw - s_roll * s_pitch * c_yaw;
		z = s_roll * c_pitch * c_yaw - c_roll * s_pitch * s_yaw;

		return *this;
	}

	inline value_type dot(const quaternion & q)
	{
		return w * q.w + x * q.x + y * q.y + z * q.z;
	}

	inline quaternion & normalize(value_type len = 1.0)
	{
		value_type l = length();
		if (abs(l) <= std::numeric_limits<value_type>::epsilon())
			*this *= len / l;
		return *this;
	}

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const { return w * w + x * x + y * y + z * z; }

	inline vector3<T> get_vector3() const { return vector3<T>{x, y, z}; }

	inline vector4<T> get_vector4() const { return vector4<T>{w, x, y, z}; }

	inline value_type operator[](part p) const
	{
		switch (p) {
			case part::w:
				return w;
			case part::x:
				return x;
			case part::y:
				return y;
			case part::z:
				return z;
		}
		return 0.0;
	}

	inline quaternion & operator=(const quaternion &) = default;

	inline quaternion & operator=(quaternion &&) = default;

	inline bool operator==(const quaternion & q)
	{
		if (this == &q)
			return true;

		if (abs(abs(w) - abs(q.w)) > std::numeric_limits<value_type>::epsilon())
			return false;
		if (abs(abs(x) - abs(q.x)) > std::numeric_limits<value_type>::epsilon())
			return false;
		if (abs(abs(y) - abs(q.y)) > std::numeric_limits<value_type>::epsilon())
			return false;
		if (abs(abs(z) - abs(q.z)) > std::numeric_limits<value_type>::epsilon())
			return false;

		return true;
	}

	inline bool operator!=(const quaternion & q) { return !(*this == q); }

	inline quaternion & operator*=(const quaternion & q)
	{
		*this = quaternion{*this} *= q;
		return *this;
	}

	inline quaternion & operator*=(value_type s)
	{
		w *= s;
		x *= s;
		y *= s;
		z *= s;
		return *this;
	}

	inline quaternion & operator+=(const quaternion & q)
	{
		w += q.w;
		x += q.x;
		y += q.y;
		z += q.z;
		return *this;
	}

	inline quaternion & operator-=(const quaternion & q)
	{
		w -= q.w;
		x -= q.x;
		y -= q.y;
		z -= q.z;
		return *this;
	}

	friend quaternion operator+(const quaternion & a, const quaternion & b)
	{
		return quaternion{a} += b;
	}

	friend quaternion operator-(const quaternion & a, const quaternion & b)
	{
		return quaternion{a} -= b;
	}

	friend quaternion operator*(const quaternion & a, const quaternion & b)
	{
		return quaternion{a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z,
			a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y,
			a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z,
			a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x};
	}

	friend quaternion operator*(const quaternion & q, value_type s)
	{
		return quaternion{q} *= s;
	}

	friend quaternion operator*(value_type s, const quaternion & q)
	{
		return quaternion{q} *= s;
	}

	friend quaternion operator*(const vector3<T> & v, const quaternion & q)
	{
		return quaternion{0, v} *= q;
	}

	friend quaternion operator*(const quaternion & q, const vector3<T> & v)
	{
		return q * quaternion{0, v};
	}

	/// Creates a quaternion which represents a roatation from one vector
	/// to another. This is useful if you know the original vector and you
	/// know the destination, but not how to rotate from start to destination.
	/// Once the quaternion is created, it is reusable.
	///
	/// Example:
	/// @code
	/// std::vector<vector3<double>> model; // many vectors in the model
	///
	/// // simple rotation from x-axis to y-axis, 90 deg arround z-axis
	/// vector3<double> from{1.0, 0.0, 0.0};
	/// vector3<double> to{0.0, 1.0, 0.0};
	///
	/// // prepare rotation
	/// quaternion<double> q = quaternion<double>::rot_to(from, to);
	///
	/// // rotate all vectors of the model
	/// for (auto & v : model)
	///     v = q.rot(v);
	/// @endcode
	static quaternion rot_to(const vector3<T> & from, const vector3<T> & to)
	{
		const vector3<T> f = normalize_vec(from);
		const vector3<T> t = normalize_vec(to);
		const value_type angle = acos(f.dot(t)) * 180.0 / M_PI;
		return quaternion{angle, f.cross(t)}.normalize();
	}

	/// Rotates the specified vector arround this quaternion. The result is a newly
	/// created vector.
	inline vector3<T> rot(const vector3<T> & v) const
	{
		return ((*this * quaternion(v)) * quaternion(w, -x, -y, -z)).get_vector3().normalize();
	}

private:
	value_type w, x, y, z;
};

using quat = quaternion<double>;
}
}

#endif
