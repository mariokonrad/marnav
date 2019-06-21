#ifndef MARNAV__MATH__QUATERNION__HPP
#define MARNAV__MATH__QUATERNION__HPP

#include <cmath>
#include <cassert>
#include <marnav/math/vector.hpp>
#include <marnav/math/floatingpoint.hpp>
#include <marnav/math/constants.hpp>

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
	using size_type = unsigned int;

	quaternion(value_type w = 1.0, value_type x = 0.0, value_type y = 0.0, value_type z = 0.0)
	{
		a[0] = w;
		a[1] = x;
		a[2] = y;
		a[3] = z;
	}

	quaternion(const quaternion &) = default;

	quaternion(quaternion &&) noexcept = default;

	quaternion(const vector3<T> & v)
	{
		a[0] = 0.0;
		a[1] = v[0];
		a[2] = v[1];
		a[3] = v[2];
	}

	/// Creates a quaternion for 3D rotation.
	///
	/// @param[in] angle The rotation angle in degrees
	/// @param[in] axis The rotation axis
	quaternion(value_type angle, const vector3<T> & axis)
	{
		const value_type d = axis.length();
		assert(!is_zero(d));

		// conversion deg -> rad
		angle *= pi / 180.0;

		// sin(phi / 2) with normalization
		value_type s = sin(angle * 0.5) / d;

		a[0] = cos(angle * 0.5);
		a[1] = axis[0] * s;
		a[2] = axis[1] * s;
		a[3] = axis[2] * s;
	}

	inline value_type w() const { return a[0]; }
	inline value_type x() const { return a[1]; }
	inline value_type y() const { return a[2]; }
	inline value_type z() const { return a[3]; }

	static quaternion make_from_euler(value_type yaw, value_type pitch, value_type roll)
	{
		quaternion q;
		q.euler(yaw, pitch, roll);
		return q;
	}

	quaternion & euler(value_type yaw, value_type pitch, value_type roll)
	{
		yaw *= (pi / 180.0) / 2.0;
		pitch *= (pi / 180.0) / 2.0;
		roll *= (pi / 180.0) / 2.0;
		const value_type c_yaw = cos(yaw);
		const value_type s_yaw = sin(yaw);
		const value_type c_pitch = cos(pitch);
		const value_type s_pitch = sin(pitch);
		const value_type c_roll = cos(roll);
		const value_type s_roll = sin(roll);

		a[0] = c_roll * c_pitch * c_yaw + s_roll * s_pitch * s_yaw;
		a[1] = c_roll * s_pitch * c_yaw + s_roll * c_pitch * s_yaw;
		a[2] = c_roll * c_pitch * s_yaw - s_roll * s_pitch * c_yaw;
		a[3] = s_roll * c_pitch * c_yaw - c_roll * s_pitch * s_yaw;

		return *this;
	}

	inline value_type dot(const quaternion & q)
	{
		return w() * q.w() + x() * q.x() + y() * q.y() + z() * q.z();
	}

	inline quaternion conjugate() const { return quaternion{w(), -x(), -y(), -z()}; }

	inline quaternion & normalize(value_type len = 1.0)
	{
		value_type l = length();
		if (is_zero(l))
			*this *= len / l;
		return *this;
	}

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const
	{
		return a[0] * a[0] + a[1] * a[1] + a[2] * a[2] + a[3] * a[3];
	}

	inline vector3<T> get_vector3() const { return vector3<T>{x(), y(), z()}; }

	inline vector4<T> get_vector4() const { return vector4<T>{w(), x(), y(), z()}; }

	inline value_type operator[](size_type index) const { return a[index]; }

	inline quaternion & operator=(const quaternion &) = default;

	inline quaternion & operator=(quaternion &&) noexcept = default;

	inline bool operator==(const quaternion & q)
	{
		if (this == &q)
			return true;

		for (size_type i = 0; i < 4; ++i)
			if (!is_same(a[i], q.a[i]))
				return false;
		return true;
	}

	inline bool operator!=(const quaternion & q) { return !(*this == q); }

	inline quaternion & operator*=(const quaternion & q)
	{
		*this = quaternion{*this} * q;
		return *this;
	}

	inline quaternion & operator*=(value_type s)
	{
		for (size_type i = 0; i < 4; ++i)
			a[i] *= s;
		return *this;
	}

	inline quaternion & operator+=(const quaternion & q)
	{
		for (size_type i = 0; i < 4; ++i)
			a[i] += q.a[i];
		return *this;
	}

	inline quaternion & operator-=(const quaternion & q)
	{
		for (size_type i = 0; i < 4; ++i)
			a[i] -= q.a[i];
		return *this;
	}

	friend quaternion operator+(const quaternion & q1, const quaternion & q2)
	{
		return quaternion{q1} += q2;
	}

	friend quaternion operator-(const quaternion & q1, const quaternion & q2)
	{
		return quaternion{q1} -= q2;
	}

	friend quaternion operator*(const quaternion & q1, const quaternion & q2)
	{
		return quaternion{q1.w() * q2.w() - q1.x() * q2.x() - q1.y() * q2.y() - q1.z() * q2.z(),
			q1.w() * q2.x() + q1.x() * q2.w() + q1.y() * q2.z() - q1.z() * q2.y(),
			q1.w() * q2.y() + q1.y() * q2.w() + q1.z() * q2.x() - q1.x() * q2.z(),
			q1.w() * q2.z() + q1.z() * q2.w() + q1.x() * q2.y() - q1.y() * q2.x()};
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
		const vector3<T> f = from.normalize();
		const vector3<T> t = to.normalize();
		const value_type angle = acos(f.dot(t)) * 180.0 / pi;
		return quaternion{angle, f.cross(t)}.normalize();
	}

	/// Rotates the specified vector arround this quaternion. The result is a newly
	/// created vector.
	inline vector3<T> rot(const vector3<T> & v) const
	{
		return ((*this * quaternion(v)) * conjugate()).get_vector3().normalize();
	}

private:
	value_type a[4];
};

using quat = quaternion<double>;
}
}

#endif
