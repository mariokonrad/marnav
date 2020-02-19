#ifndef MARNAV_UNITS_DIMENSION_HPP
#define MARNAV_UNITS_DIMENSION_HPP

namespace marnav
{
namespace units
{
// clang-format off
template <
	int Length,
	int Mass,
	int Time,
	int Temperature,
	int Current,
	int AmountOfSubstance,
	int LuminousIntensity>
struct basic_dimension
{
	enum : int {
		len = Length,
		mas = Mass,
		tim = Time,
		tem = Temperature,
		cur = Current,
		amt = AmountOfSubstance,
		lum = LuminousIntensity,
	};
};

using dim_scalar                 = basic_dimension< 0,  0,  0, 0,  0, 0, 0>;
using dim_length                 = basic_dimension< 1,  0,  0, 0,  0, 0, 0>;
using dim_area                   = basic_dimension< 2,  0,  0, 0,  0, 0, 0>;
using dim_volume                 = basic_dimension< 3,  0,  0, 0,  0, 0, 0>;
using dim_mass                   = basic_dimension< 0,  1,  0, 0,  0, 0, 0>;
using dim_temperature            = basic_dimension< 0,  0,  0, 1,  0, 0, 0>;
using dim_time                   = basic_dimension< 0,  0,  1, 0,  0, 0, 0>;
using dim_velocity               = basic_dimension< 1,  0, -1, 0,  0, 0, 0>;
using dim_acceleration           = basic_dimension< 1,  0, -2, 0,  0, 0, 0>;
using dim_pressure               = basic_dimension<-1,  1, -2, 0,  0, 0, 0>;
using dim_frequency              = basic_dimension< 0,  0, -1, 0,  0, 0, 0>;
using dim_energy                 = basic_dimension< 2,  1, -2, 0,  0, 0, 0>;
using dim_power                  = basic_dimension< 2,  1, -3, 0,  0, 0, 0>;
using dim_force                  = basic_dimension< 1,  1, -2, 0,  0, 0, 0>;
using dim_magnetic_flux          = basic_dimension< 2,  1, -2, 0, -1, 0, 0>;
using dim_magnetic_flux_density  = basic_dimension< 0,  1, -2, 0, -1, 0, 0>;
using dim_inductance             = basic_dimension< 0,  1, -2, 0, -2, 0, 0>;
using dim_capacitance            = basic_dimension<-2, -1,  4, 0,  2, 0, 0>;
using dim_electric_current       = basic_dimension< 0,  0,  0, 0,  1, 0, 0>;
using dim_electric_charge        = basic_dimension< 0,  0,  1, 0,  1, 0, 0>;
using dim_voltage                = basic_dimension< 2,  1, -3, 0, -1, 0, 0>;
using dim_electrical_conductance = basic_dimension<-2, -1,  3, 0,  2, 0, 0>;
using dim_electrical_resistance  = basic_dimension< 2,  1, -3, 0, -2, 0, 0>;

template <class Dimension1, class Dimension2>
using dim_result_add = basic_dimension<
	Dimension1::len + Dimension2::len,
	Dimension1::mas + Dimension2::mas,
	Dimension1::tim + Dimension2::tim,
	Dimension1::tem + Dimension2::tem,
	Dimension1::cur + Dimension2::cur,
	Dimension1::amt + Dimension2::amt,
	Dimension1::lum + Dimension2::lum>;

template <class Dimension1, class Dimension2>
using dim_result_sub = basic_dimension<
	Dimension1::len - Dimension2::len,
	Dimension1::mas - Dimension2::mas,
	Dimension1::tim - Dimension2::tim,
	Dimension1::tem - Dimension2::tem,
	Dimension1::cur - Dimension2::cur,
	Dimension1::amt - Dimension2::amt,
	Dimension1::lum - Dimension2::lum>;
// clang-format on
}
}

#endif
