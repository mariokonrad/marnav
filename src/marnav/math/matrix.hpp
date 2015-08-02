#ifndef __MATH__MATRIX_HPP__
#define __MATH__MATRIX_HPP__

#include <marnav/math/vector.hpp>

namespace marnav
{
namespace math
{

template <typename T> class matrix2
{
public:
	using value_type = T;

	matrix2() { load_identity(); }

	matrix2(const matrix2 &) = default;

	matrix2(matrix2 &&) = default;

	matrix2(value_type x11, value_type x12, value_type x21, value_type x22)
	{
		x[0] = x11;
		x[1] = x12;
		x[2] = x21;
		x[3] = x22;
	}

	matrix2(value_type m[4])
	{
		for (int i = 0; i < 4; ++i)
			x[i] = m[i];
	}

	inline void load_identity(void)
	{
		for (int i = 0; i < 4; ++i)
			x[i] = (i % 3) ? 0.0 : 1.0;
	}

	inline const value_type * get(void) const { return x; }

	inline value_type det(void) const { return (x[0] * x[3] - x[2] * x[1]); }

	inline matrix2 & operator=(const matrix2 &) = default;

	inline matrix2 & operator=(matrix2 &&) = default;

	inline matrix2 & operator*=(value_type f)
	{
		for (int i = 0; i < 4; ++i)
			x[i] *= f;
		return *this;
	}

	inline matrix2 & operator+=(const matrix2 & m)
	{
		for (int i = 0; i < 4; ++i)
			x[i] += m.x[i];
		return *this;
	}

	inline matrix2 & operator-=(const matrix2 & m)
	{
		for (int i = 0; i < 4; ++i)
			x[i] -= m.x[i];
		return *this;
	}

	inline matrix2 & operator*=(const matrix2 & m)
	{
		value_type c[4] = {x[0] * m.x[0] + x[1] * m.x[2], x[0] * m.x[1] + x[1] * m.x[3],
			x[2] * m.x[0] + x[3] * m.x[2], x[2] * m.x[1] + x[3] * m.x[3]};
		for (int i = 0; i < 4; ++i)
			x[i] = c[i];
		return *this;
	}

	inline value_type spur(void) const { return x[0] + x[3]; }

	inline matrix2 inv(void) const
	{
		value_type d = det();
		if (d < 1.0e-7 && d > -1.0e-7)
			return matrix2();
		return (1.0 / d) * matrix2(x[3], -x[1], -x[2], x[0]);
	}

	inline matrix2 transpose(void) const { return matrix2(x[0], x[2], x[1], x[3]); }

	inline vec2 rowvec(int row) const // row in [0..1]
	{
		row *= 2;
		return vec2(x[row], x[row + 1]);
	}

	inline vec2 colvec(int col) const // col in [0..1]
	{
		return vec2(x[col], x[col + 2]);
	}

	friend matrix2 operator*(value_type f, const matrix2 & m) { return matrix2(m) *= f; }

	friend matrix2 operator+(const matrix2 & a, const matrix2 & b) { return matrix2(a) += b; }

	friend matrix2 operator-(const matrix2 & a, const matrix2 & b) { return matrix2(a) -= b; }

	friend matrix2 operator*(const matrix2 & a, const matrix2 & b) { return matrix2(a) *= b; }

	friend matrix2 operator*(const vec2 & v, const matrix2 & m)
	{
		value_type c1 = m.x[0] + m.x[2];
		value_type c2 = m.x[1] + m.x[3];
		return matrix2(v[0] * c1, v[0] * c2, v[1] * c1, v[1] * c2);
	}

	friend vec2 operator*(const matrix2 & m, const vec2 & v)
	{
		return vec2(m.x[0] * v[0] + m.x[1] * v[1], m.x[2] * v[0] + m.x[3] * v[1]);
	}

private:
	value_type x[4];
};

using mat2 = matrix2<double>;

template <typename T> class matrix3
{
public:
	using value_type = T;

	matrix3() { load_identity(); }

	matrix3(const matrix3 &) = default;

	matrix3(matrix3 &&) = default;

	matrix3(value_type x11, value_type x12, value_type x13, value_type x21, value_type x22,
		value_type x23, value_type x31, value_type x32, value_type x33)
	{
		x[0] = x11;
		x[1] = x12;
		x[2] = x13;
		x[3] = x21;
		x[4] = x22;
		x[5] = x23;
		x[6] = x31;
		x[7] = x32;
		x[8] = x33;
	}

	matrix3(value_type m[9])
	{
		for (int i = 0; i < 9; ++i)
			x[i] = m[i];
	}

	inline void load_identity(void)
	{
		for (int i = 0; i < 9; ++i)
			x[i] = (i % 4) ? 0.0 : 1.0;
	}

	inline value_type det(void) const
	{
		return x[0] * (x[4] * x[8] - x[7] * x[5]) - x[1] * (x[3] * x[8] - x[6] * x[5])
			+ x[2] * (x[3] * x[7] - x[6] * x[4]);
	}

	inline matrix3 & operator=(const matrix3 &) = default;

	inline matrix3 & operator=(matrix3 &&) = default;

	inline matrix3 & operator*=(value_type f)
	{
		for (int i = 0; i < 9; ++i)
			x[i] *= f;
		return *this;
	}

	inline matrix3 & operator+=(const matrix3 & m)
	{
		for (int i = 0; i < 9; ++i)
			x[i] += m.x[i];
		return *this;
	}

	inline matrix3 & operator-=(const matrix3 & m)
	{
		for (int i = 0; i < 9; ++i)
			x[i] -= m.x[i];
		return *this;
	}

	inline matrix3 & operator*=(const matrix3 & m)
	{
		value_type c[9] = {x[0] * m.x[0] + x[1] * m.x[3] + x[2] * m.x[6],
			x[0] * m.x[1] + x[1] * m.x[4] + x[2] * m.x[7],
			x[0] * m.x[2] + x[1] * m.x[5] + x[2] * m.x[8],
			x[3] * m.x[0] + x[4] * m.x[3] + x[5] * m.x[6],
			x[3] * m.x[1] + x[4] * m.x[4] + x[5] * m.x[7],
			x[3] * m.x[2] + x[4] * m.x[5] + x[5] * m.x[8],
			x[6] * m.x[0] + x[7] * m.x[3] + x[8] * m.x[6],
			x[6] * m.x[1] + x[7] * m.x[4] + x[8] * m.x[7],
			x[6] * m.x[2] + x[7] * m.x[5] + x[8] * m.x[8]};
		for (int i = 0; i < 9; ++i)
			x[i] = ((c[i] < 1.0e-10) && (c[i] > -1.0e-10)) ? 0.0 : c[i];
		return *this;
	}

	inline const value_type * get(void) const { return x; }

	inline value_type spur(void) const { return x[0] + x[4] + x[8]; }

	inline matrix3 transpose(void) const
	{
		return matrix3(x[0], x[3], x[6], x[1], x[4], x[7], x[2], x[5], x[8]);
	}

	inline vec3 rowvec(int row) const // row in [0..2]
	{
		row *= 3;
		return vec3(x[row], x[row + 1], x[row + 2]);
	}

	inline vec3 colvec(int col) const // col in [0..2]
	{
		return vec3(x[col], x[col + 3], x[col + 6]);
	}

	inline matrix3 inv(void) const
	{
		value_type d = det();
		if ((d < 1.0e-7) && (d > -1.0e-7))
			return matrix3();
		matrix3 m(*this), I;
		int i0, i1;
		value_type q;
		for (int j = 0; j < 3; ++j) {
			// Diagonalfeld normalisieren
			q = m.x[j * 3 + j];
			if (q == 0.0) {
				// Es darf keine 0 mehr in der Diagonalen stehen
				for (int i = j + 1; i < 3; ++i) {
					// Suche Reihe mit einem Feld != 0.0 und addiere
					if (m.x[i * 3 + j] != 0.0) {
						for (int k = 0; k < 3; ++k) {
							i0 = j * 3 + k;
							i1 = i * 3 + k;
							m.x[i0] += m.x[i1];
							I.x[i0] += I.x[i1];
						}
						q = m.x[j * 3 + j];
						break;
					}
				}
			} else {
				// Diagonalen auf 1 bringen
				for (int k = 0; k < 3; ++k) {
					i0 = j * 3 + k;
					m.x[i0] /= q;
					I.x[i0] /= q;
				}
			}
			// Spalten ausserhalb der Diagonalen auf 0 bringen
			for (int i = 0; i < 3; ++i) {
				if (i != j) {
					q = m.x[i * 3 + j];
					for (int k = 0; k < 3; ++k) {
						i0 = i * 3 + k;
						i1 = j * 3 + k;
						m.x[i0] -= q * m.x[i1];
						I.x[i0] -= q * I.x[i1];
					}
				}
			}
		}
		// Test auf Einheitsmatrix, falls nicht => Berechnung nicht gelungen
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				if (m.x[i * 3 + j] != ((i == j) ? 1 : 0))
					return matrix3();
		return I;
	}

	friend matrix3 operator*(value_type f, const matrix3 & m) { return matrix3(m) *= f; }

	friend matrix3 operator+(const matrix3 & a, const matrix3 & b) { return matrix3(a) += b; }

	friend matrix3 operator-(const matrix3 & a, const matrix3 & b) { return matrix3(a) -= b; }

	friend matrix3 operator*(const matrix3 & a, const matrix3 & b) { return matrix3(a) *= b; }

	friend matrix3 operator*(const vec3 & v, const matrix3 & m)
	{
		value_type c1 = m.x[0] + m.x[3] + m.x[6];
		value_type c2 = m.x[1] + m.x[4] + m.x[7];
		value_type c3 = m.x[2] + m.x[5] + m.x[8];
		return matrix3(v[0] * c1, v[0] * c2, v[0] * c3, v[1] * c1, v[1] * c2, v[1] * c3,
			v[2] * c1, v[2] * c2, v[2] * c3);
	}

	friend vec3 operator*(const matrix3 & m, const vec3 & v)
	{
		return vec3(m.x[0] * v[0] + m.x[1] * v[1] + m.x[2] * v[2],
			m.x[3] * v[0] + m.x[4] * v[1] + m.x[5] * v[2],
			m.x[6] * v[0] + m.x[7] * v[1] + m.x[8] * v[2]);
	}

private:
	value_type x[9];
};

using mat3 = matrix3<double>;

template <typename T> class matrix4
{
public:
	using value_type = T;

	matrix4() { load_identity(); }

	matrix4(const matrix4 &) = default;

	matrix4(matrix4 &&) = default;

	matrix4(value_type x11, value_type x12, value_type x13, value_type x14, value_type x21,
		value_type x22, value_type x23, value_type x24, value_type x31, value_type x32,
		value_type x33, value_type x34, value_type x41, value_type x42, value_type x43,
		value_type x44)
	{
		x[0] = x11;
		x[1] = x12;
		x[2] = x13;
		x[3] = x14;
		x[4] = x21;
		x[5] = x22;
		x[6] = x23;
		x[7] = x24;
		x[8] = x31;
		x[9] = x32;
		x[10] = x33;
		x[11] = x34;
		x[12] = x41;
		x[13] = x42;
		x[14] = x43;
		x[15] = x44;
	}

	matrix4(value_type m[16])
	{
		for (int i = 0; i < 16; ++i)
			x[i] = m[i];
	}

	inline void load_identity(void)
	{
		for (int i = 0; i < 16; ++i)
			x[i] = (i % 5) ? 0.0 : 1.0;
	}

	inline value_type det(void) const
	{
		return // Regel von Sarrus
			x[0] * x[5] * x[10] * x[15] - x[12] * x[9] * x[6] * x[3]
			+ x[1] * x[6] * x[11] * x[12] - x[13] * x[10] * x[7] * x[0]
			+ x[2] * x[7] * x[8] * x[13] - x[14] * x[11] * x[4] * x[1]
			+ x[3] * x[4] * x[9] * x[14] - x[15] * x[8] * x[5] * x[2];
	}

	inline matrix4 & operator=(const matrix4 &) = default;

	inline matrix4 & operator=(matrix4 &&) = default;

	inline matrix4 & operator*=(value_type f)
	{
		for (int i = 0; i < 16; ++i)
			x[i] *= f;
		return *this;
	}

	inline matrix4 & operator+=(const matrix4 & m)
	{
		for (int i = 0; i < 16; ++i)
			x[i] += m.x[i];
		return *this;
	}

	inline matrix4 & operator-=(const matrix4 & m)
	{
		for (int i = 0; i < 16; ++i)
			x[i] -= m.x[i];
		return *this;
	}

	inline matrix4 & operator*=(const matrix4 & m)
	{
		value_type c[16] = {x[0] * m.x[0] + x[1] * m.x[4] + x[2] * m.x[8] + x[3] * m.x[12],
			x[0] * m.x[1] + x[1] * m.x[5] + x[2] * m.x[9] + x[3] * m.x[13],
			x[0] * m.x[2] + x[1] * m.x[6] + x[2] * m.x[10] + x[3] * m.x[14],
			x[0] * m.x[3] + x[1] * m.x[7] + x[2] * m.x[11] + x[3] * m.x[15],
			x[4] * m.x[0] + x[5] * m.x[4] + x[6] * m.x[8] + x[7] * m.x[12],
			x[4] * m.x[1] + x[5] * m.x[5] + x[6] * m.x[9] + x[7] * m.x[13],
			x[4] * m.x[2] + x[5] * m.x[6] + x[6] * m.x[10] + x[7] * m.x[14],
			x[4] * m.x[3] + x[5] * m.x[7] + x[6] * m.x[11] + x[7] * m.x[15],
			x[8] * m.x[0] + x[9] * m.x[4] + x[10] * m.x[8] + x[11] * m.x[12],
			x[8] * m.x[1] + x[9] * m.x[5] + x[10] * m.x[9] + x[11] * m.x[13],
			x[8] * m.x[2] + x[9] * m.x[6] + x[10] * m.x[10] + x[11] * m.x[14],
			x[8] * m.x[3] + x[9] * m.x[7] + x[10] * m.x[11] + x[11] * m.x[15],
			x[12] * m.x[0] + x[13] * m.x[4] + x[14] * m.x[8] + x[15] * m.x[12],
			x[12] * m.x[1] + x[13] * m.x[5] + x[14] * m.x[9] + x[15] * m.x[13],
			x[12] * m.x[2] + x[13] * m.x[6] + x[14] * m.x[10] + x[15] * m.x[14],
			x[12] * m.x[3] + x[13] * m.x[7] + x[14] * m.x[11] + x[15] * m.x[15]};
		for (int i = 0; i < 16; ++i)
			x[i] = ((c[i] < 1.0e-10) && (c[i] > -1.0e-10)) ? 0.0 : c[i];
		return *this;
	}

	inline value_type & operator[](size_t i) { return x[i]; }

	inline value_type operator[](size_t i) const { return x[i]; }

	inline const value_type * get(void) const { return x; }

	inline value_type spur(void) const { return x[0] + x[5] + x[10] + x[15]; }

	inline matrix4 transpose(void) const
	{
		return matrix4(x[0], x[4], x[8], x[12], x[1], x[5], x[9], x[13], x[2], x[6], x[10],
			x[14], x[3], x[7], x[11], x[15]);
	}

	inline vec4 rowvec(int row) const // row in [0..3]
	{
		row *= 4;
		return vec4(x[row], x[row + 1], x[row + 2], x[row + 3]);
	}

	inline vec4 colvec(int col) const // col in [0..3]
	{
		return vec4(x[col], x[col + 4], x[col + 8], x[col + 12]);
	}

	inline matrix4 inv(void) const
	{
		value_type d = det();
		if ((d < 1.0e-7) && (d > -1.0e-7))
			return matrix4();
		matrix4 m(*this), I;
		int i0, i1;
		for (int j = 0; j < 4; ++j) {
			// Diagonalfeld normalisieren
			value_type q = m.x[j * 4 + j];
			if (q == 0.0) {
				// Es darf keine 0 mehr in der Diagonalen stehen
				for (int i = j + 1; i < 4; ++i) {
					// Suche Reihe mit einem Feld != 0.0 und addiere
					if (m.x[i * 4 + j] != 0.0) {
						for (int k = 0; k < 4; ++k) {
							i0 = j * 4 + k;
							i1 = i * 4 + k;
							m.x[i0] += m.x[i1];
							I.x[i0] += I.x[i1];
						}
						q = m.x[j * 4 + j];
						break;
					}
				}
			} else {
				// Diagonalen auf 1 bringen
				for (int k = 0; k < 4; ++k) {
					i0 = j * 4 + k;
					m.x[i0] /= q;
					I.x[i0] /= q;
				}
			}
			// Spalten ausserhalb der Diagonalen auf 0 bringen
			for (int i = 0; i < 4; ++i) {
				if (i != j) {
					q = m.x[i * 4 + j];
					for (int k = 0; k < 4; ++k) {
						i0 = i * 4 + k;
						i1 = j * 4 + k;
						m.x[i0] -= q * m.x[i1];
						I.x[i0] -= q * I.x[i1];
					}
				}
			}
		}
		// Test auf Einheitsmatrix, falls nicht => Berechnung nicht gelungen
		for (int i = 0; i < 4; ++i)
			for (int j = 0; j < 4; ++j)
				if (m.x[i * 4 + j] != ((i == j) ? 1 : 0))
					return matrix4();
		return I;
	}

	friend matrix4 operator*(value_type f, const matrix4 & m) { return matrix4(m) *= f; }

	friend matrix4 operator+(const matrix4 & a, const matrix4 & b) { return matrix4(a) += b; }

	friend matrix4 operator-(const matrix4 & a, const matrix4 & b) { return matrix4(a) -= b; }

	friend matrix4 operator*(const matrix4 & a, const matrix4 & b) { return matrix4(a) *= b; }

	friend matrix4 operator*(const vec4 & v, const matrix4 & m)
	{
		value_type c1 = m.x[0] + m.x[4] + m.x[8] + m.x[12];
		value_type c2 = m.x[1] + m.x[5] + m.x[9] + m.x[13];
		value_type c3 = m.x[2] + m.x[6] + m.x[10] + m.x[14];
		value_type c4 = m.x[3] + m.x[7] + m.x[11] + m.x[15];
		return matrix4(v[0] * c1, v[0] * c2, v[0] * c3, v[0] * c4, v[1] * c1, v[1] * c2,
			v[1] * c3, v[1] * c4, v[2] * c1, v[2] * c2, v[2] * c3, v[2] * c4, v[3] * c1,
			v[3] * c2, v[3] * c3, v[3] * c4);
	}

	friend vec4 operator*(const matrix4 & m, const vec4 & v)
	{
		return vec4(m.x[0] * v[0] + m.x[1] * v[1] + m.x[2] * v[2] + m.x[3] * v[3],
			m.x[4] * v[0] + m.x[5] * v[1] + m.x[6] * v[2] + m.x[7] * v[3],
			m.x[8] * v[0] + m.x[9] * v[1] + m.x[10] * v[2] + m.x[11] * v[3],
			m.x[12] * v[0] + m.x[13] * v[1] + m.x[14] * v[2] + m.x[15] * v[3]);
	}

private:
	value_type x[16];
};

using mat4 = matrix4<double>;

template <unsigned int N, typename T> class matrix_n // N >= 1
{
public:
	using value_type = T;

	matrix_n() { load_identity(); }

	matrix_n(const matrix_n &) = default;

	matrix_n(matrix_n &&) = default;

	matrix_n(value_type m[])
	{
		for (unsigned int i = 0; i < N * N; ++i)
			x[i] = m[i];
	}

	inline void load_identity(void)
	{
		for (unsigned int i = 0; i < N * N; ++i)
			x[i] = (i % (N + 1)) ? 0.0 : 1.0;
	}

	inline matrix_n & operator=(const matrix_n &) = default;

	inline matrix_n & operator=(matrix_n &&) = default;

	inline matrix_n & operator*=(value_type f)
	{
		for (unsigned int i = 0; i < N * N; ++i)
			x[i] *= f;
		return *this;
	}

	inline matrix_n & operator+=(const matrix_n & m)
	{
		for (unsigned int i = 0; i < N * N; ++i)
			x[i] += m.x[i];
		return *this;
	}

	inline matrix_n & operator-=(const matrix_n & m)
	{
		for (unsigned int i = 0; i < N * N; ++i)
			x[i] -= m.x[i];
		return *this;
	}

	inline value_type spur(void) const
	{
		value_type s = 0.0;
		for (unsigned int i = 0; i < N; ++i)
			s += x[i * N + i];
		return s;
	}

	inline matrix_n transpose(void) const
	{
		matrix_n r;
		for (unsigned int i = 0; i < N; ++i)
			for (unsigned int j = 0; j < N; ++j)
				r.x[i * N + j] = x[j * N + i];
		return r;
	}

	inline matrix_n & operator*=(const matrix_n & m)
	{
		value_type c[N * N];
		unsigned int idx;
		for (unsigned int i = 0; i < N; ++i)
			for (unsigned int j = 0; j < N; ++j) {
				idx = i * N + j;
				c[idx] = 0.0;
				for (unsigned int k = 0; k < N; ++k)
					c[idx] += x[i * N + k] * m.x[k * N + j];
			}
		for (unsigned int i = 0; i < N * N; ++i)
			x[i] = ((c[i] < 1.0e-10) && (c[i] > -1.0e-10)) ? 0.0 : c[i];
		return *this;
	}

	inline value_type det(void) const
	{ // Regel von Sarrus
		value_type r = 0.0;
		value_type ap, am;
		unsigned int k;
		for (unsigned int j = 0; j < N; ++j) {
			ap = am = 1.0;
			for (unsigned int i = 0; i < N; ++i) {
				k = (j + i) % N;
				ap *= x[i * N + k];
				am *= x[(N - 1 - i) * N + k];
			}
			r += ap - am;
		}
		return r;
	}

	inline matrix_n inv(void) const
	{
		value_type d = det();
		if ((d < 1.0e-7) && (d > -1.0e-7))
			return matrix_n();
		matrix_n m(*this), I;
		unsigned int i0, i1;
		value_type q;
		for (unsigned int j = 0; j < N; ++j) {
			// Diagonalfeld normalisieren
			q = m.x[j * N + j];
			if (q == 0.0) {
				// Es darf keine 0 mehr in der Diagonalen stehen
				for (unsigned int i = j + 1; i < N; ++i) {
					// Suche Reihe mit einem Feld != 0.0 und addiere
					if (m.x[i * N + j] != 0.0) {
						for (unsigned int k = 0; k < N; ++k) {
							i0 = j * N + k;
							i1 = i * N + k;
							m.x[i0] += m.x[i1];
							I.x[i0] += I.x[i1];
						}
						q = m.x[j * N + j];
						break;
					}
				}
			} else { // Diagonalen auf 1 bringen
				for (unsigned int k = 0; k < N; ++k) {
					i0 = j * N + k;
					m.x[i0] /= q;
					I.x[i0] /= q;
				}
			}
			// Spalten ausserhalb der Diagonalen auf 0 bringen
			for (unsigned int i = 0; i < N; ++i) {
				if (i != j) {
					q = m.x[i * N + j];
					for (unsigned int k = 0; k < N; ++k) {
						i0 = i * N + k;
						i1 = j * N + k;
						m.x[i0] -= q * m.x[i1];
						I.x[i0] -= q * I.x[i1];
					}
				}
			}
		}
		// Test auf Einheitsmatrix, falls nicht => Berechnung nicht gelungen
		for (unsigned int i = 0; i < N; ++i)
			for (unsigned int j = 0; j < N; ++j)
				if (m.x[i * N + j] != ((i == j) ? 1 : 0))
					return matrix_n();
		return I;
	}

	inline vector_n<N, T> rowvec(int row) const // row in [0..N-1]
	{
		vector_n<N, T> v;
		row *= N;
		for (unsigned int i = 0; i < N; ++i)
			v[i] = x[row + i];
		return v;
	}

	inline vector_n<N, T> colvec(int col) const // col in [0..N-1]
	{
		vector_n<N, T> v;
		for (unsigned int i = 0; i < N; ++i)
			v[i] = x[col + i * N];
		return v;
	}

	friend matrix_n operator*(value_type f, const matrix_n & m) { return matrix_n(m) *= f; }

	friend matrix_n<N, T> operator+(const matrix_n & a, const matrix_n & b)
	{
		return matrix_n(a) += b;
	}

	friend matrix_n<N, T> operator-(const matrix_n & a, const matrix_n & b)
	{
		return matrix_n(a) -= b;
	}

	friend matrix_n<N, T> operator*(const matrix_n & a, const matrix_n & b)
	{
		return matrix_n(a) *= b;
	}

	friend matrix_n<N, T> operator*(const vector_n<N, T> & v, const matrix_n & m)
	{
		matrix_n r;
		vector_n<N, T> c;
		for (unsigned int i = 0; i < N; ++i)
			for (unsigned int j = 0; j < N; ++j)
				c[i] += m.x[i * N + j];
		for (unsigned int i = 0; i < N; ++i)
			for (unsigned int j = 0; j < N; ++j)
				r.x[i * N + j] = c[j] * v[i];
		return r;
	}

	friend vector_n<N, T> operator*(const matrix_n & m, const vector_n<N, T> & v)
	{
		vector_n<N, T> r;
		for (unsigned int i = 0; i < N; ++i)
			for (unsigned int j = 0; j < N; ++j)
				r[i] += m.x[j + i * N] * v[i];
		return r;
	}

private:
	value_type x[N * N];
};
}
}

#endif
