#ifndef MARNAV_UNITS_BASIC_QUANTITY_OPS_HPP
#define MARNAV_UNITS_BASIC_QUANTITY_OPS_HPP

#include "basic_quantity.hpp"
#include "basic_unit.hpp"
#include "dimension.hpp"

namespace marnav
{
namespace units
{
template <class T, class VT>
constexpr basic_quantity<T, VT> operator*(
	const basic_quantity<T, VT> & v, const VT & s) noexcept
{
	return basic_quantity<T, VT>(v.value() * s);
}

template <class T, class VT>
constexpr basic_quantity<T, VT> operator*(
	const VT & s, const basic_quantity<T, VT> & v) noexcept
{
	return basic_quantity<T, VT>(v.value() * s);
}

template <class T, class VT>
constexpr basic_quantity<T, VT> operator+(
	const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept
{
	return basic_quantity<T, VT>(v1.value() + v2.value());
}

template <class T, class VT>
constexpr basic_quantity<T, VT> operator-(
	const basic_quantity<T, VT> & v1, const basic_quantity<T, VT> & v2) noexcept
{
	return basic_quantity<T, VT>(v1.value() - v2.value());
}

template <class Unit1, class Ratio1, class Unit2, class Ratio2,
	class ResultDim = dim_result_add<typename Unit1::dimension, typename Unit2::dimension>,
	class ResultValueType = typename Unit1::value_type,
	typename = typename std::enable_if<
		std::is_same<typename Unit1::value_type, typename Unit2::value_type>::value>::type>
constexpr basic_quantity<ResultDim, ResultValueType> operator*(
	const basic_unit<Unit1, Ratio1> & u1, const basic_unit<Unit2, Ratio2> & u2) noexcept
{
	return basic_quantity<ResultDim, ResultValueType>(
		(Unit1::to_base(u1.value()) * Ratio1::num / Ratio1::den) * Unit2::to_base(u2.value())
		* Ratio2::num / Ratio2::den);
}

template <class Unit1, class Ratio1, class Unit2, class Ratio2,
	class ResultDim = dim_result_sub<typename Unit1::dimension, typename Unit2::dimension>,
	class ResultValueType = typename Unit1::value_type,
	typename = typename std::enable_if<
		std::is_same<typename Unit1::value_type, typename Unit2::value_type>::value>::type>
constexpr basic_quantity<ResultDim, ResultValueType> operator/(
	const basic_unit<Unit1, Ratio1> & u1, const basic_unit<Unit2, Ratio2> & u2) noexcept
{
	return basic_quantity<ResultDim, ResultValueType>(
		(Unit1::to_base(u1.value()) * Ratio1::num / Ratio1::den) / Unit2::to_base(u2.value())
		* Ratio2::num / Ratio2::den);
}

template <class VT, class Dimension1, class Dimension2,
	class ResultDim = dim_result_add<Dimension1, Dimension2>>
constexpr basic_quantity<ResultDim, VT> operator*(const basic_quantity<Dimension1, VT> & v1,
	const basic_quantity<Dimension2, VT> & v2) noexcept
{
	return basic_quantity<ResultDim, VT>(v1.value() * v2.value());
}

template <class VT, class Dimension1, class Dimension2,
	class ResultDim = dim_result_sub<Dimension1, Dimension2>>
constexpr basic_quantity<ResultDim, VT> operator/(const basic_quantity<Dimension1, VT> & v1,
	const basic_quantity<Dimension2, VT> & v2) noexcept
{
	return basic_quantity<ResultDim, VT>(v1.value() / v2.value());
}
}
}

#endif
