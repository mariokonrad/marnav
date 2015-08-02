#ifndef __MATH__VECTOR_HPP__
#define __MATH__VECTOR_HPP__

#include <cmath>
#include <limits>

namespace marnav
{
namespace math
{

template <typename T> class vector2
{
public:
	using value_type = T;

	enum class axis { x, y };
	enum class angle { phi };

public:
	vector2(value_type x = 0.0, value_type y = 0.0)
	{
		this->x[0] = x;
		this->x[1] = y;
	}

	vector2(const vector2 &) = default;

	vector2(vector2 &&) = default;

	vector2(value_type * v)
	{
		x[0] = v[0];
		x[1] = v[1];
	}

	static inline vector2 make_from_circle(value_type radius, value_type phi_deg)
	{
		phi_deg *= (M_PI / 180.0);
		return vector2{radius * cos(phi_deg), radius * sin(phi_deg)};
	}

	inline value_type phi_deg() const
	{
		if ((x[0] > 0) && (x[1] > 0))
			return atan(x[1] / x[0]) * 180.0 / M_PI;
		if ((x[0] < 0) && (x[1] > 0))
			return 90.0 + atan(x[0] / x[1]) * 180.0 / M_PI;
		if ((x[0] < 0) && (x[1] < 0))
			return 180.0 + atan(x[1] / x[0]) * 180.0 / M_PI;
		if ((x[0] > 0) && (x[1] < 0))
			return 270.0 + atan(x[0] / x[1]) * 180.0 / M_PI;

		return 0;
	}

	inline value_type dot(const vector2 & v) const { return x[0] * v.x[0] + x[1] * v.x[1]; }

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const { return x[0] * x[0] + x[1] * x[1]; }

	inline vector2 & normalize(value_type len = 1.0)
	{
		const value_type l = length();
		return (l != 0.0) ? (*this *= (len / l)) : (*this);
	}

	inline vector2 normalize(value_type len = 1.0f) const
	{
		const value_type l = length();
		return (l != 0.0) ? (vector2(*this) *= (len / l)) : vector2();
	}

	inline vector2 & rot(value_type angle_deg)
	{
		angle_deg *= M_PI / 180.0;
		value_type c = cos(angle_deg);
		value_type s = sin(angle_deg);
		return * this = vector2(x[0] * c - x[1] * s, x[0] * s + x[1] * c);
	}

	inline vector2 project_to(const vector2 & v) const
	{
		value_type len = v.length2();
		if (len == 0.0)
			return vector2(); // TODO: exception?
		return (this->dot(v) / len) * v;
	}

	inline value_type operator[](int idx) const { return x[idx]; }

	inline vector2 & operator=(const vector2 &) = default;

	inline vector2 & operator=(vector2 &&) = default;

	inline bool operator==(const vector2 & v) const
	{
		return ((x[0] == v.x[0]) && (x[1] == v.x[1]));
	}

	inline vector2 & operator+=(const vector2 & v)
	{
		x[0] += v.x[0];
		x[1] += v.x[1];
		return *this;
	}

	inline vector2 & operator-=(const vector2 & v)
	{
		x[0] -= v.x[0];
		x[1] -= v.x[1];
		return *this;
	}

	inline vector2 & operator*=(value_type f)
	{
		x[0] *= f;
		x[1] *= f;
		return *this;
	}

	friend vector2 operator+(const vector2 & w, const vector2 & v) { return vector2(w) += v; }

	friend vector2 operator-(const vector2 & w, const vector2 & v) { return vector2(w) -= v; }

	friend vector2 operator*(const vector2 & v, value_type f) { return vector2(v) *= f; }

	friend vector2 operator*(value_type f, const vector2 & v) { return vector2(v) *= f; }

	friend value_type operator*(const vector2 & a, const vector2 & b) { return a.dot(b); }

	value_type angle_between(const vector2 & p) const { return angle_between(*this, p); }

	static value_type angle_between(const vector2 & p0, const vector2 & p1)
	{
		return acos(p0.dot(p1) / (p0.length() * p1.length()));
	}

private:
	value_type x[2];
};

using vec2 = vector2<double>;

template <typename T> class vector3
{
public:
	using value_type = T;

	enum class axis { x, y, z };
	enum class angle { phi, rho };

public:
	vector3(value_type x = 0.0, value_type y = 0.0, value_type z = 0.0)
	{
		this->x[0] = x;
		this->x[1] = y;
		this->x[2] = z;
	}

	vector3(const vector3 &) = default;

	vector3(vector3 &&) = default;

	vector3(value_type * v)
	{
		x[0] = v[0];
		x[1] = v[1];
		x[2] = v[2];
	}

	inline vector3 & set(value_type a, value_type b, value_type c)
	{
		x[0] = a;
		x[1] = b;
		x[2] = c;
		return *this;
	}

	inline vector3 & set_sphere(value_type r, value_type phi_deg, value_type rho_deg)
	{
		phi_deg *= (M_PI / 180.0);
		rho_deg *= (M_PI / 180.0);
		x[0] = r * cos(phi_deg) * cos(rho_deg);
		x[1] = r * cos(phi_deg) * sin(rho_deg);
		x[2] = r * sin(phi_deg);
		return *this;
	}

	inline value_type dot(const vector3 & v) const
	{
		return x[0] * v.x[0] + x[1] * v.x[1] + x[2] * v.x[2];
	}

	inline vector3 cross(const vector3 & v) const
	{
		return vector3(x[1] * v.x[2] - x[2] * v.x[1], x[2] * v.x[0] - x[0] * v.x[2],
			x[0] * v.x[1] - x[1] * v.x[0]);
	}

	inline vector3 & nullify(void)
	{
		const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		x[0] = ((x[0] <= EPSILON) && (x[0] >= -EPSILON)) ? 0.0 : x[0];
		x[1] = ((x[1] <= EPSILON) && (x[1] >= -EPSILON)) ? 0.0 : x[1];
		x[2] = ((x[2] <= EPSILON) && (x[2] >= -EPSILON)) ? 0.0 : x[2];
		return *this;
	}

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const { return x[0] * x[0] + x[1] * x[1] + x[2] * x[2]; }

	inline vector3 & normalize(value_type len = 1.0)
	{
		const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		value_type l = length();
		if ((l < EPSILON) && (l > -EPSILON))
			return *this;
		l = len / l;
		x[0] *= l;
		x[1] *= l;
		x[2] *= l;
		return *this;
	}

	inline vector3 normalize(value_type len = 1.0) const
	{
		const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		value_type l = length();
		if ((l < EPSILON) && (l > -EPSILON))
			return *this;
		return vector3(*this) * (len / l);
	}

	inline value_type get_sphere_r() const { return length(); }

	inline value_type get_sphere_phi() const
	{
		value_type a = sqrt(x[0] * x[0] + x[1] * x[1]);
		return (a != 0.0) ? (atan(x[2] / a) * 180.0 / M_PI) : 0.0;
	}

	inline value_type get_sphere_rho() const
	{
		const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		if (x[0] >= -EPSILON && x[0] <= EPSILON) {
			if (x[1] >= -EPSILON && x[1] <= EPSILON)
				return 0.0;
			else if (x[1] > 0.0)
				return 90.0;
			else if (x[1] < 0.0)
				return 270.0;
		}
		if (x[0] > 0.0) {
			return atan(x[1] / x[0]) * 180.0 / M_PI;
		} else // (x[0] < 0.0)
		{
			return 180.0 + atan(x[1] / x[0]) * 180.0 / M_PI;
		}
	}

	inline vector3 & rot(axis a, value_type angle_deg)
	{
		switch (a) {
			case axis::x:
				return rot_x(angle_deg);
			case axis::y:
				return rot_y(angle_deg);
			case axis::z:
				return rot_z(angle_deg);
		}
		return *this;
	}

	inline vector3 & rot_x(value_type angle_deg)
	{
		angle_deg *= M_PI / 180.0;
		value_type c = cos(angle_deg);
		value_type s = sin(angle_deg);
		return * this = vector3(x[0], x[1] * c - x[2] * s, x[1] * s + x[2] * c);
	}

	inline vector3 & rot_y(value_type angle_deg)
	{
		angle_deg *= M_PI / 180.0;
		value_type c = cos(angle_deg);
		value_type s = sin(angle_deg);
		return * this = vector3(x[0] * c - x[2] * s, x[1], x[0] * s + x[2] * c);
	}

	inline vector3 & rot_z(value_type angle_deg)
	{
		angle_deg *= M_PI / 180.0;
		value_type c = cos(angle_deg);
		value_type s = sin(angle_deg);
		return * this = vector3(x[0] * c - x[1] * s, x[0] * s + x[1] * c, x[2]);
	}

	inline vector3 & rot_sphere(angle a, value_type angle_deg)
	{
		switch (a) {
			case angle::phi:
				return rot_phi(angle_deg);
			case angle::rho:
				return rot_rho(angle_deg);
		}
		return *this;
	}

	inline vector3 & rot_phi(value_type angle_deg)
	{
		return set_sphere(get_sphere_r(), get_sphere_phi() + angle_deg, get_sphere_rho());
	}

	inline vector3 & rot_rho(value_type angle_deg)
	{
		return set_sphere(get_sphere_r(), get_sphere_phi(), get_sphere_rho() + angle_deg);
	}

	inline vector3 project_to(const vector3 & v) const
	{
		value_type len = v.length2();
		if (len == 0.0)
			return vector3(); // TODO: exception?
		return (this->dot(v) / len) * v;
	}

	inline value_type operator[](int idx) const { return x[idx]; }

	inline value_type & operator[](int idx) { return x[idx]; }

	inline operator const value_type *(void) const { return x; }

	inline vector3 & operator=(const vector3 &) = default;

	inline vector3 & operator=(vector3 &&) = default;

	inline bool operator==(const vector3 & v) const
	{
		return ((x[0] == v.x[0]) && (x[1] == v.x[1]) && (x[2] == v.x[2]));
	}

	inline vector3 & operator+=(const vector3 & v)
	{
		x[0] += v.x[0];
		x[1] += v.x[1];
		x[2] += v.x[2];
		return *this;
	}

	inline vector3 & operator-=(const vector3 & v)
	{
		x[0] -= v.x[0];
		x[1] -= v.x[1];
		x[2] -= v.x[2];
		return *this;
	}

	inline vector3 & operator*=(value_type f)
	{
		x[0] *= f;
		x[1] *= f;
		x[2] *= f;
		return *this;
	}

	friend vector3 operator+(const vector3 & w, const vector3 & v) { return vector3(w) += v; }

	friend vector3 operator-(const vector3 & w, const vector3 & v) { return vector3(w) -= v; }

	friend vector3 operator*(const vector3 & v, value_type f) { return vector3(v) *= f; }

	friend vector3 operator*(value_type f, const vector3 & v) { return vector3(v) *= f; }

	friend value_type operator*(const vector3 & a, const vector3 & b) { return a.dot(b); }

	value_type angle_between(const vector3 & p) const { return angle_between(*this, p); }

	static value_type angle_between(const vector3 & p0, const vector3 & p1)
	{
		return acos(p0.dot(p1) / (p0.length() * p1.length()));
	}

private:
	value_type x[3];
};

using vec3 = vector3<double>;

template <typename T> class vector4
{
public:
	using value_type = T;

	enum class axis { x, y, z, w };
	enum class angle { phi, rho };

public:
	vector4(value_type x = 0.0, value_type y = 0.0, value_type z = 0.0, value_type w = 0.0)
	{
		this->x[0] = x;
		this->x[1] = y;
		this->x[2] = z;
		this->x[3] = w;
	}

	vector4(const vector4 &) = default;

	vector4(vector4 &&) = default;

	vector4(value_type * v)
	{
		x[0] = v[0];
		x[1] = v[1];
		x[2] = v[2];
		x[3] = v[3];
	}

	inline vector4 & set(value_type a, value_type b, value_type c, value_type d)
	{
		x[0] = a;
		x[1] = b;
		x[2] = c;
		x[3] = d;
		return *this;
	}

	inline value_type dot(const vector4 & v) const
	{
		return x[0] * v.x[0] + x[1] * v.x[1] + x[2] * v.x[2] + x[3] * v.x[3];
	}

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const
	{
		return x[0] * x[0] + x[1] * x[1] + x[2] * x[2] + x[3] * x[3];
	}

	inline vector4 & normalize(value_type len = 1.0)
	{
		value_type l = length();
		return (l != 0.0) ? (*this *= (len / l)) : (*this);
	}

	inline value_type operator[](int idx) const { return x[idx]; }

	inline operator const value_type *(void) const { return x; }

	inline vector4 & operator=(const vector4 &) = default;

	inline vector4 & operator=(vector4 &&) = default;

	inline bool operator==(const vector4 & v) const
	{
		return ((x[0] == v.x[0]) && (x[1] == v.x[1]) && (x[2] == v.x[2]) && (x[3] == v.x[3]));
	}

	inline vector4 & operator+=(const vector4 & v)
	{
		x[0] += v.x[0];
		x[1] += v.x[1];
		x[2] += v.x[2];
		x[3] += v.x[3];
		return *this;
	}

	inline vector4 & operator-=(const vector4 & v)
	{
		x[0] -= v.x[0];
		x[1] -= v.x[1];
		x[2] -= v.x[2];
		x[3] -= v.x[3];
		return *this;
	}

	inline vector4 & operator*=(value_type f)
	{
		x[0] *= f;
		x[1] *= f;
		x[2] *= f;
		x[3] *= f;
		return *this;
	}

	friend vector4 operator+(const vector4 & w, const vector4 & v) { return vector4(w) += v; }

	friend vector4 operator-(const vector4 & w, const vector4 & v) { return vector4(w) -= v; }

	friend vector4 operator*(const vector4 & v, value_type f) { return vector4(v) *= f; }

	friend vector4 operator*(value_type f, const vector4 & v) { return vector4(v) *= f; }

	friend value_type operator*(const vector4 & a, const vector4 & b) { return a.dot(b); }

private:
	value_type x[4];
};

using vec4 = vector4<double>;

template <unsigned int N, typename T = double> class vector_n // N >= 1
{
public:
	using value_type = T;

	vector_n()
	{
		for (unsigned int i = 0; i < N; ++i)
			x[i] = 0.0;
	}

	vector_n(const vector_n &) = default;

	vector_n(vector_n &&) = default;

	vector_n(value_type * v)
	{
		for (unsigned int i = 0; i < N; ++i)
			x[i] = v[i];
	}

	inline value_type dot(const vector_n & v) const
	{
		value_type r = 0.0;
		for (unsigned int i = 0; i < N; ++i)
			r += (x[i] * v.x[i]);
		return r;
	}

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const
	{
		value_type r = 0.0;
		for (unsigned int i = 0; i < N; ++i)
			r += (x[i] * x[i]);
		return r;
	}

	inline vector_n & normalize(value_type len = 1.0)
	{
		const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		value_type l = length();
		return ((l < EPSILON) && (l > -EPSILON)) ? (*this *= (len / l)) : (*this);
	}

	inline value_type operator[](int idx) const { return x[idx]; }

	inline value_type & operator[](int idx) { return x[idx]; }

	inline vector_n & operator=(const vector_n &) = default;

	inline vector_n & operator=(vector_n &&) = default;

	inline bool operator==(const vector_n & v) const
	{
		for (unsigned int i = 0; i < N; ++i)
			if (x[i] != v.x[i])
				return false;
		return true;
	}

	inline vector_n & operator+=(const vector_n & v)
	{
		for (unsigned int i = 0; i < N; ++i)
			x[i] += v.x[i];
		return *this;
	}

	inline vector_n & operator-=(const vector_n & v)
	{
		for (unsigned int i = 0; i < N; ++i)
			x[i] -= v.x[i];
		return *this;
	}

	inline vector_n & operator*=(value_type f)
	{
		for (unsigned int i = 0; i < N; ++i)
			x[i] *= f;
		return *this;
	}

	friend vector_n operator+(const vector_n & w, const vector_n & v)
	{
		return vector_n(w) += v;
	}

	friend vector_n operator-(const vector_n & w, const vector_n & v)
	{
		return vector_n(w) -= v;
	}

	friend vector_n operator*(const vector_n & v, value_type f) { return vector_n(v) *= f; }

	friend vector_n operator*(value_type f, const vector_n & v) { return vector_n(v) *= f; }

	friend value_type operator*(const vector_n & a, const vector_n & b) { return a.dot(b); }

private:
	value_type x[N];
};
}
}

#endif
