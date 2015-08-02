#ifndef __MATH__VECTOR_HPP__
#define __MATH__VECTOR_HPP__

#include <cmath>
#include <limits>

namespace marnav
{
namespace math
{

class vec2
{
public:
	using value_type = double;

	enum class axis { x, y };
	enum class angle { phi };

public:
	vec2(value_type x = 0.0, value_type y = 0.0)
	{
		this->x[0] = x;
		this->x[1] = y;
	}

	vec2(const vec2 &) = default;
	vec2(vec2 &&) = default;

	vec2(value_type * v)
	{
		x[0] = v[0];
		x[1] = v[1];
	}

	inline vec2 & set(value_type a, value_type b)
	{
		x[0] = a;
		x[1] = b;
		return *this;
	}

	inline vec2 & set_circle(value_type r, value_type phi_deg)
	{
		phi_deg *= (M_PI / 180.0);
		x[0] = r * cos(phi_deg);
		x[1] = r * sin(phi_deg);
		return *this;
	}

	inline value_type dot(const vec2 & v) const { return x[0] * v.x[0] + x[1] * v.x[1]; }

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const { return x[0] * x[0] + x[1] * x[1]; }

	inline vec2 & normalize(value_type len = 1.0)
	{
		const value_type l = length();
		return (l != 0.0) ? (*this *= (len / l)) : (*this);
	}

	inline vec2 normalize(value_type len = 1.0f) const
	{
		const value_type l = length();
		return (l != 0.0) ? (vec2(*this) *= (len / l)) : vec2();
	}

	inline vec2 & rot(value_type angle_deg)
	{
		angle_deg *= M_PI / 180.0;
		value_type c = cos(angle_deg);
		value_type s = sin(angle_deg);
		return * this = vec2(x[0] * c - x[1] * s, x[0] * s + x[1] * c);
	}

	inline vec2 project_to(const vec2 & v) const
	{
		value_type len = v.length2();
		if (len == 0.0)
			return vec2(); // TODO: exception?
		return (this->dot(v) / len) * v;
	}

	inline value_type operator[](int idx) const { return x[idx]; }

	inline vec2 & operator=(const vec2 &) = default;
	inline vec2 & operator=(vec2 &&) = default;

	inline bool operator==(const vec2 & v) const
	{
		return ((x[0] == v.x[0]) && (x[1] == v.x[1]));
	}

	inline vec2 & operator+=(const vec2 & v)
	{
		x[0] += v.x[0];
		x[1] += v.x[1];
		return *this;
	}

	inline vec2 & operator-=(const vec2 & v)
	{
		x[0] -= v.x[0];
		x[1] -= v.x[1];
		return *this;
	}

	inline vec2 & operator*=(value_type f)
	{
		x[0] *= f;
		x[1] *= f;
		return *this;
	}

	friend vec2 operator+(const vec2 & w, const vec2 & v) { return vec2(w) += v; }
	friend vec2 operator-(const vec2 & w, const vec2 & v) { return vec2(w) -= v; }
	friend vec2 operator*(const vec2 & v, value_type f) { return vec2(v) *= f; }
	friend vec2 operator*(value_type f, const vec2 & v) { return vec2(v) *= f; }
	friend value_type operator*(const vec2 & a, const vec2 & b) { return a.dot(b); }

	value_type angle_between(const vec2 & p) const { return angle_between(*this, p); }

	static value_type angle_between(const vec2 & p0, const vec2 & p1)
	{
		return acos(p0.dot(p1) / (p0.length() * p1.length()));
	}

private:
	value_type x[2];
};

class vec3
{
public:
	using value_type = double;

	enum class axis { x, y, z };
	enum class angle { phi, rho };

public:
	vec3(value_type x = 0.0, value_type y = 0.0, value_type z = 0.0)
	{
		this->x[0] = x;
		this->x[1] = y;
		this->x[2] = z;
	}

	vec3(const vec3 &) = default;
	vec3(vec3 &&) = default;

	vec3(value_type * v)
	{
		x[0] = v[0];
		x[1] = v[1];
		x[2] = v[2];
	}

	inline vec3 & set(value_type a, value_type b, value_type c)
	{
		x[0] = a;
		x[1] = b;
		x[2] = c;
		return *this;
	}

	inline vec3 & set_sphere(value_type r, value_type phi_deg, value_type rho_deg)
	{
		phi_deg *= (M_PI / 180.0);
		rho_deg *= (M_PI / 180.0);
		x[0] = r * cos(phi_deg) * cos(rho_deg);
		x[1] = r * cos(phi_deg) * sin(rho_deg);
		x[2] = r * sin(phi_deg);
		return *this;
	}

	inline value_type dot(const vec3 & v) const
	{
		return x[0] * v.x[0] + x[1] * v.x[1] + x[2] * v.x[2];
	}

	inline vec3 cross(const vec3 & v) const
	{
		return vec3(x[1] * v.x[2] - x[2] * v.x[1], x[2] * v.x[0] - x[0] * v.x[2],
			x[0] * v.x[1] - x[1] * v.x[0]);
	}

	inline vec3 & nullify(void)
	{
		const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		x[0] = ((x[0] <= EPSILON) && (x[0] >= -EPSILON)) ? 0.0 : x[0];
		x[1] = ((x[1] <= EPSILON) && (x[1] >= -EPSILON)) ? 0.0 : x[1];
		x[2] = ((x[2] <= EPSILON) && (x[2] >= -EPSILON)) ? 0.0 : x[2];
		return *this;
	}

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const { return x[0] * x[0] + x[1] * x[1] + x[2] * x[2]; }

	inline vec3 & normalize(value_type len = 1.0)
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

	inline vec3 normalize(value_type len = 1.0) const
	{
		const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		value_type l = length();
		if ((l < EPSILON) && (l > -EPSILON))
			return *this;
		return vec3(*this) * (len / l);
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

	inline vec3 & rot(axis a, value_type angle_deg)
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

	inline vec3 & rot_x(value_type angle_deg)
	{
		angle_deg *= M_PI / 180.0;
		value_type c = cos(angle_deg);
		value_type s = sin(angle_deg);
		return * this = vec3(x[0], x[1] * c - x[2] * s, x[1] * s + x[2] * c);
	}

	inline vec3 & rot_y(value_type angle_deg)
	{
		angle_deg *= M_PI / 180.0;
		value_type c = cos(angle_deg);
		value_type s = sin(angle_deg);
		return * this = vec3(x[0] * c - x[2] * s, x[1], x[0] * s + x[2] * c);
	}

	inline vec3 & rot_z(value_type angle_deg)
	{
		angle_deg *= M_PI / 180.0;
		value_type c = cos(angle_deg);
		value_type s = sin(angle_deg);
		return * this = vec3(x[0] * c - x[1] * s, x[0] * s + x[1] * c, x[2]);
	}

	inline vec3 & rot_sphere(angle a, value_type angle_deg)
	{
		switch (a) {
			case angle::phi:
				return rot_phi(angle_deg);
			case angle::rho:
				return rot_rho(angle_deg);
		}
		return *this;
	}

	inline vec3 & rot_phi(value_type angle_deg)
	{
		return set_sphere(get_sphere_r(), get_sphere_phi() + angle_deg, get_sphere_rho());
	}

	inline vec3 & rot_rho(value_type angle_deg)
	{
		return set_sphere(get_sphere_r(), get_sphere_phi(), get_sphere_rho() + angle_deg);
	}

	inline vec3 project_to(const vec3 & v) const
	{
		value_type len = v.length2();
		if (len == 0.0)
			return vec3(); // TODO: exception?
		return (this->dot(v) / len) * v;
	}

	inline value_type operator[](int idx) const { return x[idx]; }

	inline value_type & operator[](int idx) { return x[idx]; }

	inline operator const value_type *(void) const { return x; }

	inline vec3 & operator=(const vec3 &) = default;
	inline vec3 & operator=(vec3 &&) = default;

	inline bool operator==(const vec3 & v) const
	{
		return ((x[0] == v.x[0]) && (x[1] == v.x[1]) && (x[2] == v.x[2]));
	}

	inline vec3 & operator+=(const vec3 & v)
	{
		x[0] += v.x[0];
		x[1] += v.x[1];
		x[2] += v.x[2];
		return *this;
	}

	inline vec3 & operator-=(const vec3 & v)
	{
		x[0] -= v.x[0];
		x[1] -= v.x[1];
		x[2] -= v.x[2];
		return *this;
	}

	inline vec3 & operator*=(value_type f)
	{
		x[0] *= f;
		x[1] *= f;
		x[2] *= f;
		return *this;
	}

	friend vec3 operator+(const vec3 & w, const vec3 & v) { return vec3(w) += v; }
	friend vec3 operator-(const vec3 & w, const vec3 & v) { return vec3(w) -= v; }
	friend vec3 operator*(const vec3 & v, value_type f) { return vec3(v) *= f; }
	friend vec3 operator*(value_type f, const vec3 & v) { return vec3(v) *= f; }
	friend value_type operator*(const vec3 & a, const vec3 & b) { return a.dot(b); }

	value_type angle_between(const vec3 & p) const { return angle_between(*this, p); }

	static value_type angle_between(const vec3 & p0, const vec3 & p1)
	{
		return acos(p0.dot(p1) / (p0.length() * p1.length()));
	}

private:
	value_type x[3];
};

class vec4
{
public:
	using value_type = double;

	enum class axis { x, y, z, w };
	enum class angle { phi, rho };

public:
	vec4(value_type x = 0.0, value_type y = 0.0, value_type z = 0.0, value_type w = 0.0)
	{
		this->x[0] = x;
		this->x[1] = y;
		this->x[2] = z;
		this->x[3] = w;
	}

	vec4(const vec4 &) = default;
	vec4(vec4 &&) = default;

	vec4(value_type * v)
	{
		x[0] = v[0];
		x[1] = v[1];
		x[2] = v[2];
		x[3] = v[3];
	}

	inline vec4 & set(value_type a, value_type b, value_type c, value_type d)
	{
		x[0] = a;
		x[1] = b;
		x[2] = c;
		x[3] = d;
		return *this;
	}

	inline value_type dot(const vec4 & v) const
	{
		return x[0] * v.x[0] + x[1] * v.x[1] + x[2] * v.x[2] + x[3] * v.x[3];
	}

	inline value_type length() const { return sqrt(length2()); }

	inline value_type length2() const
	{
		return x[0] * x[0] + x[1] * x[1] + x[2] * x[2] + x[3] * x[3];
	}

	inline vec4 & normalize(value_type len = 1.0)
	{
		value_type l = length();
		return (l != 0.0) ? (*this *= (len / l)) : (*this);
	}

	inline value_type operator[](int idx) const { return x[idx]; }

	inline operator const value_type *(void) const { return x; }

	inline vec4 & operator=(const vec4 &) = default;
	inline vec4 & operator=(vec4 &&) = default;

	inline bool operator==(const vec4 & v) const
	{
		return ((x[0] == v.x[0]) && (x[1] == v.x[1]) && (x[2] == v.x[2]) && (x[3] == v.x[3]));
	}

	inline vec4 & operator+=(const vec4 & v)
	{
		x[0] += v.x[0];
		x[1] += v.x[1];
		x[2] += v.x[2];
		x[3] += v.x[3];
		return *this;
	}

	inline vec4 & operator-=(const vec4 & v)
	{
		x[0] -= v.x[0];
		x[1] -= v.x[1];
		x[2] -= v.x[2];
		x[3] -= v.x[3];
		return *this;
	}

	inline vec4 & operator*=(value_type f)
	{
		x[0] *= f;
		x[1] *= f;
		x[2] *= f;
		x[3] *= f;
		return *this;
	}

	friend vec4 operator+(const vec4 & w, const vec4 & v) { return vec4(w) += v; }
	friend vec4 operator-(const vec4 & w, const vec4 & v) { return vec4(w) -= v; }
	friend vec4 operator*(const vec4 & v, value_type f) { return vec4(v) *= f; }
	friend vec4 operator*(value_type f, const vec4 & v) { return vec4(v) *= f; }
	friend value_type operator*(const vec4 & a, const vec4 & b) { return a.dot(b); }
private:
	value_type x[4];
};

template <unsigned int N> class vecn // N >= 1
{
public:
	using value_type = double;

	vecn()
	{
		for (unsigned int i = 0; i < N; ++i)
			x[i] = 0.0;
	}

	vecn(const vecn<N> &) = default;
	vecn(vecn<N> &&) = default;

	vecn(value_type * v)
	{
		for (unsigned int i = 0; i < N; ++i)
			x[i] = v[i];
	}

	inline value_type dot(const vecn<N> & v) const
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

	inline vecn<N> & normalize(value_type len = 1.0)
	{
		const value_type EPSILON = std::numeric_limits<value_type>::epsilon();
		value_type l = length();
		return ((l < EPSILON) && (l > -EPSILON)) ? (*this *= (len / l)) : (*this);
	}

	inline value_type operator[](int idx) const { return x[idx]; }

	inline vecn<N> & operator=(const vecn<N> &) = default;
	inline vecn<N> & operator=(vecn<N> &&) = default;

	inline bool operator==(const vecn<N> & v) const
	{
		for (unsigned int i = 0; i < N; ++i)
			if (x[i] != v.x[i])
				return false;
		return true;
	}

	inline vecn<N> & operator+=(const vecn<N> & v)
	{
		for (unsigned int i = 0; i < N; ++i)
			x[i] += v.x[i];
		return *this;
	}

	inline vecn<N> & operator-=(const vecn<N> & v)
	{
		for (unsigned int i = 0; i < N; ++i)
			x[i] -= v.x[i];
		return *this;
	}

	inline vecn<N> & operator*=(value_type f)
	{
		for (unsigned int i = 0; i < N; ++i)
			x[i] *= f;
		return *this;
	}

	friend vecn<N> operator+(const vecn<N> & w, const vecn<N> & v) { return vecn<N>(w) += v; }
	friend vecn<N> operator-(const vecn<N> & w, const vecn<N> & v) { return vecn<N>(w) -= v; }
	friend vecn<N> operator*(const vecn<N> & v, value_type f) { return vecn<N>(v) *= f; }
	friend vecn<N> operator*(value_type f, const vecn<N> & v) { return vecn<N>(v) *= f; }
	friend value_type operator*(const vecn<N> & a, const vecn<N> & b) { return a.dot(b); }

private:
	value_type x[N];
};
}
}

#endif
