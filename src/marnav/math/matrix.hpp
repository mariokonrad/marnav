#ifndef __MATH__MATRIX__HPP__
#define __MATH__MATRIX__HPP__

#include <marnav/math/vector.hpp>
#include <marnav/math/floatingpoint.hpp>

namespace marnav
{
namespace math
{

template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class matrix2
{
public:
	using value_type = T;
	using size_type = unsigned int;

	constexpr static const size_type dimension = 2;

	matrix2(const matrix2 &) = default;

	matrix2(matrix2 &&) = default;

	matrix2(
		value_type x11 = 1.0, value_type x12 = 0.0, value_type x21 = 0.0, value_type x22 = 1.0)
	{
		x[0] = x11;
		x[1] = x12;
		x[2] = x21;
		x[3] = x22;
	}

	inline value_type det() const { return (x[0] * x[3] - x[2] * x[1]); }

	inline bool operator==(const matrix2 & m) const
	{
		if (this == &m)
			return true;
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			if (!is_same(x[i], m.x[i]))
				return false;
		return true;
	}

	inline bool operator!=(const matrix2 & m) const { return !(*this == m); }

	inline value_type & operator[](size_type i) { return x[i]; }

	inline value_type operator[](size_type i) const { return x[i]; }

	inline matrix2 & operator=(const matrix2 &) = default;

	inline matrix2 & operator=(matrix2 &&) = default;

	inline matrix2 & operator*=(value_type f)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] *= f;
		return *this;
	}

	inline matrix2 & operator+=(const matrix2 & m)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] += m.x[i];
		return *this;
	}

	inline matrix2 & operator-=(const matrix2 & m)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] -= m.x[i];
		return *this;
	}

	inline matrix2 & operator*=(const matrix2 & m)
	{
		value_type c[4] = {x[0] * m.x[0] + x[1] * m.x[2], x[0] * m.x[1] + x[1] * m.x[3],
			x[2] * m.x[0] + x[3] * m.x[2], x[2] * m.x[1] + x[3] * m.x[3]};
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] = c[i];
		return *this;
	}

	inline value_type spur() const { return x[0] + x[3]; }

	inline matrix2 inv() const
	{
		const value_type d = det();
		if (is_zero(d))
			return matrix2{};
		return (1.0 / d) * matrix2{x[3], -x[1], -x[2], x[0]};
	}

	inline matrix2 transpose() const { return matrix2{x[0], x[2], x[1], x[3]}; }

	inline vector2<T> rowvec(size_type row) const // row in [0..1]
	{
		row *= 2;
		return vector2<T>{x[row], x[row + 1]};
	}

	inline vector2<T> colvec(size_type col) const // col in [0..1]
	{
		return vector2<T>{x[col], x[col + 2]};
	}

	friend matrix2 operator*(value_type f, const matrix2 & m) { return matrix2{m} *= f; }

	friend matrix2 operator+(const matrix2 & a, const matrix2 & b) { return matrix2{a} += b; }

	friend matrix2 operator-(const matrix2 & a, const matrix2 & b) { return matrix2{a} -= b; }

	friend matrix2 operator*(const matrix2 & a, const matrix2 & b) { return matrix2{a} *= b; }

	friend matrix2 operator*(const vector2<T> & v, const matrix2 & m)
	{
		value_type c1 = m.x[0] + m.x[2];
		value_type c2 = m.x[1] + m.x[3];
		return matrix2{v[0] * c1, v[0] * c2, v[1] * c1, v[1] * c2};
	}

	friend vector2<T> operator*(const matrix2 & m, const vector2<T> & v)
	{
		return vector2<T>{m.x[0] * v[0] + m.x[1] * v[1], m.x[2] * v[0] + m.x[3] * v[1]};
	}

private:
	value_type x[4];
};

template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class matrix3
{
public:
	using value_type = T;
	using size_type = unsigned int;

	constexpr static const size_type dimension = 3;

	matrix3(const matrix3 &) = default;

	matrix3(matrix3 &&) = default;

	matrix3(value_type x11 = 1.0, value_type x12 = 0.0, value_type x13 = 0.0,
		value_type x21 = 0.0, value_type x22 = 1.0, value_type x23 = 0.0, value_type x31 = 0.0,
		value_type x32 = 0.0, value_type x33 = 1.0)
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

	inline value_type det() const
	{
		return x[0] * (x[4] * x[8] - x[7] * x[5]) - x[1] * (x[3] * x[8] - x[6] * x[5])
			+ x[2] * (x[3] * x[7] - x[6] * x[4]);
	}

	inline value_type & operator[](size_t i) { return x[i]; }

	inline value_type operator[](size_t i) const { return x[i]; }

	inline bool operator==(const matrix3 & m) const
	{
		if (this == &m)
			return true;
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			if (!is_same(x[i], m.x[i]))
				return false;
		return true;
	}

	inline bool operator!=(const matrix3 & m) const { return !(*this == m); }

	inline matrix3 & operator=(const matrix3 &) = default;

	inline matrix3 & operator=(matrix3 &&) = default;

	inline matrix3 & operator*=(value_type f)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] *= f;
		return *this;
	}

	inline matrix3 & operator+=(const matrix3 & m)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] += m.x[i];
		return *this;
	}

	inline matrix3 & operator-=(const matrix3 & m)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] -= m.x[i];
		return *this;
	}

	inline matrix3 & operator*=(const matrix3 & m)
	{
		value_type c[sizeof(x) / sizeof(value_type)]
			= {x[0] * m.x[0] + x[1] * m.x[3] + x[2] * m.x[6],
				x[0] * m.x[1] + x[1] * m.x[4] + x[2] * m.x[7],
				x[0] * m.x[2] + x[1] * m.x[5] + x[2] * m.x[8],
				x[3] * m.x[0] + x[4] * m.x[3] + x[5] * m.x[6],
				x[3] * m.x[1] + x[4] * m.x[4] + x[5] * m.x[7],
				x[3] * m.x[2] + x[4] * m.x[5] + x[5] * m.x[8],
				x[6] * m.x[0] + x[7] * m.x[3] + x[8] * m.x[6],
				x[6] * m.x[1] + x[7] * m.x[4] + x[8] * m.x[7],
				x[6] * m.x[2] + x[7] * m.x[5] + x[8] * m.x[8]};
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] = is_zero(c[i]) ? 0.0 : c[i];
		return *this;
	}

	inline value_type spur() const { return x[0] + x[4] + x[8]; }

	inline matrix3 transpose() const
	{
		return matrix3(x[0], x[3], x[6], x[1], x[4], x[7], x[2], x[5], x[8]);
	}

	inline vector3<T> rowvec(size_type row) const // row in [0..2]
	{
		row *= 3;
		return vector3<T>{x[row], x[row + 1], x[row + 2]};
	}

	inline vector3<T> colvec(size_type col) const // col in [0..2]
	{
		return vector3<T>{x[col], x[col + 3], x[col + 6]};
	}

	inline matrix3 inv() const
	{
		const value_type d = det();
		if (is_zero(d))
			return matrix3{};
		matrix3 m{*this};
		matrix3 I;
		value_type q;
		for (size_type j = 0; j < 3; ++j) {
			// Diagonalfeld normalisieren
			q = m.x[j * 3 + j];
			if (q == 0.0) {
				// Es darf keine 0 mehr in der Diagonalen stehen
				for (size_type i = j + 1; i < 3; ++i) {
					// Suche Reihe mit einem Feld != 0.0 und addiere
					if (m.x[i * 3 + j] != 0.0) {
						for (size_type k = 0; k < 3; ++k) {
							const size_type i0 = j * 3 + k;
							const size_type i1 = i * 3 + k;
							m.x[i0] += m.x[i1];
							I.x[i0] += I.x[i1];
						}
						q = m.x[j * 3 + j];
						break;
					}
				}
			} else {
				// Diagonalen auf 1 bringen
				for (size_type k = 0; k < 3; ++k) {
					const size_type i0 = j * 3 + k;
					m.x[i0] /= q;
					I.x[i0] /= q;
				}
			}
			// Spalten ausserhalb der Diagonalen auf 0 bringen
			for (size_type i = 0; i < 3; ++i) {
				if (i != j) {
					q = m.x[i * 3 + j];
					for (size_type k = 0; k < 3; ++k) {
						const size_type i0 = i * 3 + k;
						const size_type i1 = j * 3 + k;
						m.x[i0] -= q * m.x[i1];
						I.x[i0] -= q * I.x[i1];
					}
				}
			}
		}
		// Test auf Einheitsmatrix, falls nicht => Berechnung nicht gelungen
		for (size_type i = 0; i < 3; ++i)
			for (size_type j = 0; j < 3; ++j)
				if (m.x[i * 3 + j] != ((i == j) ? 1 : 0))
					return matrix3{};
		return I;
	}

	friend matrix3 operator*(value_type f, const matrix3 & m) { return matrix3{m} *= f; }

	friend matrix3 operator+(const matrix3 & a, const matrix3 & b) { return matrix3{a} += b; }

	friend matrix3 operator-(const matrix3 & a, const matrix3 & b) { return matrix3{a} -= b; }

	friend matrix3 operator*(const matrix3 & a, const matrix3 & b) { return matrix3{a} *= b; }

	friend matrix3 operator*(const vector3<T> & v, const matrix3 & m)
	{
		value_type c1 = m.x[0] + m.x[3] + m.x[6];
		value_type c2 = m.x[1] + m.x[4] + m.x[7];
		value_type c3 = m.x[2] + m.x[5] + m.x[8];
		return matrix3{v[0] * c1, v[0] * c2, v[0] * c3, v[1] * c1, v[1] * c2, v[1] * c3,
			v[2] * c1, v[2] * c2, v[2] * c3};
	}

	friend vector3<T> operator*(const matrix3 & m, const vector3<T> & v)
	{
		return vector3<T>{m.x[0] * v[0] + m.x[1] * v[1] + m.x[2] * v[2],
			m.x[3] * v[0] + m.x[4] * v[1] + m.x[5] * v[2],
			m.x[6] * v[0] + m.x[7] * v[1] + m.x[8] * v[2]};
	}

private:
	value_type x[9];
};

template <typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class matrix4
{
public:
	using value_type = T;
	using size_type = unsigned int;

	constexpr static const size_type dimension = 4;

	matrix4(const matrix4 &) = default;

	matrix4(matrix4 &&) = default;

	matrix4(value_type x11 = 1.0, value_type x12 = 0.0, value_type x13 = 0.0,
		value_type x14 = 0.0, value_type x21 = 0.0, value_type x22 = 1.0, value_type x23 = 0.0,
		value_type x24 = 0.0, value_type x31 = 0.0, value_type x32 = 0.0, value_type x33 = 1.0,
		value_type x34 = 0.0, value_type x41 = 0.0, value_type x42 = 0.0, value_type x43 = 0.0,
		value_type x44 = 1.0)
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

	inline value_type det() const
	{
		// Regel von Sarrus
		return x[0] * x[5] * x[10] * x[15] - x[12] * x[9] * x[6] * x[3]
			+ x[1] * x[6] * x[11] * x[12] - x[13] * x[10] * x[7] * x[0]
			+ x[2] * x[7] * x[8] * x[13] - x[14] * x[11] * x[4] * x[1]
			+ x[3] * x[4] * x[9] * x[14] - x[15] * x[8] * x[5] * x[2];
	}

	inline bool operator==(const matrix4 & m) const
	{
		if (this == &m)
			return true;
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			if (!is_same(x[i], m.x[i]))
				return false;
		return true;
	}

	inline bool operator!=(const matrix4 & m) const { return !(*this == m); }

	inline matrix4 & operator=(const matrix4 &) = default;

	inline matrix4 & operator=(matrix4 &&) = default;

	inline matrix4 & operator*=(value_type f)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] *= f;
		return *this;
	}

	inline matrix4 & operator+=(const matrix4 & m)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] += m.x[i];
		return *this;
	}

	inline matrix4 & operator-=(const matrix4 & m)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
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
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] = is_zero(c[i]) ? 0.0 : c[i];
		return *this;
	}

	inline value_type & operator[](size_t i) { return x[i]; }

	inline value_type operator[](size_t i) const { return x[i]; }

	inline value_type spur() const { return x[0] + x[5] + x[10] + x[15]; }

	inline matrix4 transpose() const
	{
		return matrix4{x[0], x[4], x[8], x[12], x[1], x[5], x[9], x[13], x[2], x[6], x[10],
			x[14], x[3], x[7], x[11], x[15]};
	}

	inline vector4<T> rowvec(size_type row) const // row in [0..3]
	{
		row *= 4;
		return vector4<T>{x[row], x[row + 1], x[row + 2], x[row + 3]};
	}

	inline vector4<T> colvec(size_type col) const // col in [0..3]
	{
		return vector4<T>{x[col], x[col + 4], x[col + 8], x[col + 12]};
	}

	inline matrix4 inv() const
	{
		const value_type d = det();
		if (is_zero(d))
			return matrix4{};
		matrix4 m{*this};
		matrix4 I;
		for (size_type j = 0; j < 4; ++j) {
			// Diagonalfeld normalisieren
			value_type q = m.x[j * 4 + j];
			if (q == 0.0) {
				// Es darf keine 0 mehr in der Diagonalen stehen
				for (size_type i = j + 1; i < 4; ++i) {
					// Suche Reihe mit einem Feld != 0.0 und addiere
					if (m.x[i * 4 + j] != 0.0) {
						for (size_type k = 0; k < 4; ++k) {
							const size_type i0 = j * 4 + k;
							const size_type i1 = i * 4 + k;
							m.x[i0] += m.x[i1];
							I.x[i0] += I.x[i1];
						}
						q = m.x[j * 4 + j];
						break;
					}
				}
			} else {
				// Diagonalen auf 1 bringen
				for (size_type k = 0; k < 4; ++k) {
					const size_type i0 = j * 4 + k;
					m.x[i0] /= q;
					I.x[i0] /= q;
				}
			}
			// Spalten ausserhalb der Diagonalen auf 0 bringen
			for (size_type i = 0; i < 4; ++i) {
				if (i != j) {
					q = m.x[i * 4 + j];
					for (size_type k = 0; k < 4; ++k) {
						const size_type i0 = i * 4 + k;
						const size_type i1 = j * 4 + k;
						m.x[i0] -= q * m.x[i1];
						I.x[i0] -= q * I.x[i1];
					}
				}
			}
		}
		// Test auf Einheitsmatrix, falls nicht => Berechnung nicht gelungen
		for (size_type i = 0; i < 4; ++i)
			for (size_type j = 0; j < 4; ++j)
				if (m.x[i * 4 + j] != ((i == j) ? 1 : 0))
					return matrix4{};
		return I;
	}

	friend matrix4 operator*(value_type f, const matrix4 & m) { return matrix4{m} *= f; }

	friend matrix4 operator+(const matrix4 & a, const matrix4 & b) { return matrix4{a} += b; }

	friend matrix4 operator-(const matrix4 & a, const matrix4 & b) { return matrix4{a} -= b; }

	friend matrix4 operator*(const matrix4 & a, const matrix4 & b) { return matrix4{a} *= b; }

	friend matrix4 operator*(const vector4<T> & v, const matrix4 & m)
	{
		value_type c1 = m.x[0] + m.x[4] + m.x[8] + m.x[12];
		value_type c2 = m.x[1] + m.x[5] + m.x[9] + m.x[13];
		value_type c3 = m.x[2] + m.x[6] + m.x[10] + m.x[14];
		value_type c4 = m.x[3] + m.x[7] + m.x[11] + m.x[15];
		return matrix4(v[0] * c1, v[0] * c2, v[0] * c3, v[0] * c4, v[1] * c1, v[1] * c2,
			v[1] * c3, v[1] * c4, v[2] * c1, v[2] * c2, v[2] * c3, v[2] * c4, v[3] * c1,
			v[3] * c2, v[3] * c3, v[3] * c4);
	}

	friend vector4<T> operator*(const matrix4 & m, const vector4<T> & v)
	{
		return vec4(m.x[0] * v[0] + m.x[1] * v[1] + m.x[2] * v[2] + m.x[3] * v[3],
			m.x[4] * v[0] + m.x[5] * v[1] + m.x[6] * v[2] + m.x[7] * v[3],
			m.x[8] * v[0] + m.x[9] * v[1] + m.x[10] * v[2] + m.x[11] * v[3],
			m.x[12] * v[0] + m.x[13] * v[1] + m.x[14] * v[2] + m.x[15] * v[3]);
	}

private:
	value_type x[16];
};

template <unsigned int N, typename T,
	typename = typename std::enable_if<std::is_floating_point<T>::value, T>::type>
class matrix_n
{
public:
	using value_type = T;
	using size_type = decltype(N);

	constexpr static const size_type dimension = N;

	matrix_n()
	{
		static_assert(N >= 1, "invalid dimension of matrix_n, constraint: N>=1");

		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] = (i % (dimension + 1)) ? 0.0 : 1.0;
	}

	matrix_n(const matrix_n &) = default;

	matrix_n(matrix_n &&) = default;

	matrix_n(std::initializer_list<T> v)
	{
		assert(v.size() == N);
		unsigned int i = 0;
		for (auto j = begin(v); j != end(v); ++i, ++j)
			x[i] = *j;
	}

	inline bool operator==(const matrix_n & m) const
	{
		if (this == &m)
			return true;
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			if (!is_same(x[i], m.x[i]))
				return false;
		return true;
	}

	inline bool operator!=(const matrix_n & m) const { return !(*this == m); }

	inline matrix_n & operator=(const matrix_n &) = default;

	inline matrix_n & operator=(matrix_n &&) = default;

	inline matrix_n & operator*=(value_type f)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] *= f;
		return *this;
	}

	inline matrix_n & operator+=(const matrix_n & m)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] += m.x[i];
		return *this;
	}

	inline matrix_n & operator-=(const matrix_n & m)
	{
		for (size_t i = 0; i < sizeof(x) / sizeof(value_type); ++i)
			x[i] -= m.x[i];
		return *this;
	}

	inline value_type spur() const
	{
		value_type s = 0.0;
		for (size_type i = 0; i < dimension; ++i)
			s += x[i * dimension + i];
		return s;
	}

	inline matrix_n transpose() const
	{
		matrix_n r;
		for (size_type i = 0; i < dimension; ++i)
			for (size_type j = 0; j < dimension; ++j)
				r.x[i * dimension + j] = x[j * dimension + i];
		return r;
	}

	inline matrix_n & operator*=(const matrix_n & m)
	{
		value_type c[dimension * dimension];
		for (size_type i = 0; i < dimension; ++i)
			for (size_type j = 0; j < dimension; ++j) {
				const size_type idx = i * dimension + j;
				c[idx] = 0.0;
				for (size_type k = 0; k < dimension; ++k)
					c[idx] += x[i * dimension + k] * m.x[k * dimension + j];
			}
		for (size_type i = 0; i < dimension * dimension; ++i)
			x[i] = is_zero(c[i]) ? 0.0 : c[i];
		return *this;
	}

	inline value_type det() const
	{
		// Regel von Sarrus
		value_type r = 0.0;
		for (size_type j = 0; j < dimension; ++j) {
			value_type ap = 1.0;
			value_type am = 1.0;
			for (size_type i = 0; i < dimension; ++i) {
				const size_type k = (j + i) % dimension;
				ap *= x[i * dimension + k];
				am *= x[(dimension - 1 - i) * dimension + k];
			}
			r += ap - am;
		}
		return r;
	}

	inline matrix_n inv() const
	{
		const value_type d = det();
		if (is_zero(d))
			return matrix_n{};
		matrix_n m{*this};
		matrix_n I;
		value_type q;
		for (size_type j = 0; j < dimension; ++j) {
			// Diagonalfeld normalisieren
			q = m.x[j * dimension + j];
			if (q == 0.0) {
				// Es darf keine 0 mehr in der Diagonalen stehen
				for (size_type i = j + 1; i < dimension; ++i) {
					// Suche Reihe mit einem Feld != 0.0 und addiere
					if (m.x[i * dimension + j] != 0.0) {
						for (size_type k = 0; k < dimension; ++k) {
							const size_type i0 = j * dimension + k;
							const size_type i1 = i * dimension + k;
							m.x[i0] += m.x[i1];
							I.x[i0] += I.x[i1];
						}
						q = m.x[j * dimension + j];
						break;
					}
				}
			} else { // Diagonalen auf 1 bringen
				for (size_type k = 0; k < dimension; ++k) {
					const size_type i0 = j * dimension + k;
					m.x[i0] /= q;
					I.x[i0] /= q;
				}
			}
			// Spalten ausserhalb der Diagonalen auf 0 bringen
			for (size_type i = 0; i < dimension; ++i) {
				if (i != j) {
					q = m.x[i * dimension + j];
					for (size_type k = 0; k < dimension; ++k) {
						const size_type i0 = i * dimension + k;
						const size_type i1 = j * dimension + k;
						m.x[i0] -= q * m.x[i1];
						I.x[i0] -= q * I.x[i1];
					}
				}
			}
		}
		// Test auf Einheitsmatrix, falls nicht => Berechnung nicht gelungen
		for (size_type i = 0; i < dimension; ++i)
			for (size_type j = 0; j < dimension; ++j)
				if (m.x[i * dimension + j] != ((i == j) ? 1 : 0))
					return matrix_n{};
		return I;
	}

	inline vector_n<N, T> rowvec(size_type row) const // row in [0..dimension-1]
	{
		vector_n<N, T> v;
		row *= dimension;
		for (size_type i = 0; i < dimension; ++i)
			v[i] = x[row + i];
		return v;
	}

	inline vector_n<N, T> colvec(size_type col) const // col in [0..N-1]
	{
		vector_n<N, T> v;
		for (size_type i = 0; i < dimension; ++i)
			v[i] = x[col + i * dimension];
		return v;
	}

	friend matrix_n operator*(value_type f, const matrix_n & m) { return matrix_n{m} *= f; }

	friend matrix_n<N, T> operator+(const matrix_n & a, const matrix_n & b)
	{
		return matrix_n{a} += b;
	}

	friend matrix_n<N, T> operator-(const matrix_n & a, const matrix_n & b)
	{
		return matrix_n{a} -= b;
	}

	friend matrix_n<N, T> operator*(const matrix_n & a, const matrix_n & b)
	{
		return matrix_n{a} *= b;
	}

	friend matrix_n<N, T> operator*(const vector_n<N, T> & v, const matrix_n & m)
	{
		matrix_n r;
		vector_n<N, T> c;
		for (size_type i = 0; i < dimension; ++i)
			for (size_type j = 0; j < dimension; ++j)
				c[i] += m.x[i * dimension + j];
		for (size_type i = 0; i < dimension; ++i)
			for (size_type j = 0; j < dimension; ++j)
				r.x[i * dimension + j] = c[j] * v[i];
		return r;
	}

	friend vector_n<N, T> operator*(const matrix_n & m, const vector_n<N, T> & v)
	{
		vector_n<N, T> r;
		for (size_type i = 0; i < dimension; ++i)
			for (size_type j = 0; j < dimension; ++j)
				r[i] += m.x[j + i * dimension] * v[i];
		return r;
	}

private:
	value_type x[N * N];
};

using mat2 = matrix2<double>;
using mat3 = matrix3<double>;
using mat4 = matrix4<double>;
}
}

#endif
