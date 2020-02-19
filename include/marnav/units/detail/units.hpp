#ifndef MARNAV_UNITS_DETAIL_UNITS_HPP
#define MARNAV_UNITS_DETAIL_UNITS_HPP

#include "dimension.hpp"

namespace marnav
{
namespace units
{
// clang-format off
template <class T> struct basic_meter {
	using value_type = T;
	using dimension = dim_length;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_foot {
	using value_type = T;
	using dimension = dim_length;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.3048); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.3048); }
};

template <class T> struct basic_inch {
	using value_type = T;
	using dimension = dim_length;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.0254); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.0254); }
};

template <class T> struct basic_yard {
	using value_type = T;
	using dimension = dim_length;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.9144); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.9144); }
};

template <class T> struct basic_imperial_mile {
	using value_type = T;
	using dimension = dim_length;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(1609.34); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(1609.34); }
};

template <class T> struct basic_nautical_mile {
	using value_type = T;
	using dimension = dim_length;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(1852.0); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(1852.0); }
};

template <class T> struct basic_fathom {
	using value_type = T;
	using dimension = dim_length;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(1.8288); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(1.8288); }
};

// ----- area

template <class T> struct basic_squaremeter {
	using value_type = T;
	using dimension = dim_area;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_acre {
	using value_type = T;
	using dimension = dim_area;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(4046.86); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(4046.86); }
};

// ----- volume

template <class T> struct basic_qubicmeter {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_liter {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v / value_type(1000.0); }
	static constexpr value_type from_base(value_type v) noexcept { return v * value_type(1000.0); }
};

template <class T> struct basic_gallon_uk {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.00454609); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.00454609); }
};

template <class T> struct basic_quart_uk {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.0011365225); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.0011365225); }
};

template <class T> struct basic_pint_uk {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.000568261); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.000568261); }
};

template <class T> struct basic_cup_uk {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.000284131); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.000284131); }
};

template <class T> struct basic_gallon_liquid_us {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.00378541); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.00378541); }
};

template <class T> struct basic_quart_liquid_us {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.000946352946); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.000946352946); }
};

template <class T> struct basic_pint_liquid_us {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.000473176); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.000473176); }
};

template <class T> struct basic_cup_liquid_us {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.00024); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.00024); }
};

template <class T> struct basic_gallon_dry_us {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.004404883771); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.004404883771); }
};

template <class T> struct basic_quart_dry_us {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.001101220942715); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.001101220942715); }
};

template <class T> struct basic_pint_dry_us {
	using value_type = T;
	using dimension = dim_volume;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.000550610471); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.000550610471); }
};

// ----- velocity

template <class T> struct basic_meter_per_second {
	using value_type = T;
	using dimension = dim_velocity;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_knot {
	using value_type = T;
	using dimension = dim_velocity;
	static constexpr value_type to_base(value_type v) noexcept { return v  / value_type(1.94384); }
	static constexpr value_type from_base(value_type v) noexcept { return v * value_type(1.94384); }
};

template <class T> struct basic_kilometer_per_hour {
	using value_type = T;
	using dimension = dim_velocity;
	static constexpr value_type to_base(value_type v) noexcept { return v / value_type(3.6); }
	static constexpr value_type from_base(value_type v) noexcept { return v * value_type(3.6); }
};

template <class T> struct basic_mile_per_hour {
	using value_type = T;
	using dimension = dim_velocity;
	static constexpr value_type to_base(value_type v) noexcept { return v / value_type(2.23694); }
	static constexpr value_type from_base(value_type v) noexcept { return v * value_type(2.23694); }
};

// ----- temperature

template <class T> struct basic_kelvin {
	using value_type = T;
	using dimension = dim_temperature;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_celsius {
	using value_type = T;
	using dimension = dim_temperature;
	static constexpr value_type to_base(value_type v) noexcept { return v + value_type(273.15); }
	static constexpr value_type from_base(value_type v) noexcept { return v - value_type(273.15); }
};

template <class T> struct basic_fahrenheit {
	using value_type = T;
	using dimension = dim_temperature;
	static constexpr value_type to_base(value_type v) noexcept { return (v + value_type(459.67)) * value_type(5.0 / 9.0); }
	static constexpr value_type from_base(value_type v) noexcept { return v * value_type(9.0 / 5.0) - value_type(459.67); }
};

template <class T> struct basic_rankine {
	using value_type = T;
	using dimension = dim_temperature;
	static constexpr value_type to_base(value_type v) noexcept { return v / value_type(1.8); }
	static constexpr value_type from_base(value_type v) noexcept { return v * value_type(1.8); }
};

template <class T> struct basic_reaumur {
	using value_type = T;
	using dimension = dim_temperature;
	static constexpr double to_base(double v) noexcept { return v * value_type(1.25) + value_type(273.15); }
	static constexpr double from_base(double v) noexcept { return (v - value_type(273.15)) * value_type(0.8); }
};

// ----- pressure

template <class T> struct basic_bar {
	using value_type = T;
	using dimension = dim_pressure;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_pascal {
	using value_type = T;
	using dimension = dim_pressure;
	static constexpr value_type to_base(value_type v) noexcept { return v / value_type(100000.0); }
	static constexpr value_type from_base(value_type v) noexcept { return v * value_type(100000.0); }
};

template <class T> struct basic_psi {
	using value_type = T;
	using dimension = dim_pressure;
	static constexpr value_type to_base(value_type v) noexcept { return v / value_type(14.503773773); }
	static constexpr value_type from_base(value_type v) noexcept { return v * value_type(14.503773773); }
};

template <class T> struct basic_torr {
	using value_type = T;
	using dimension = dim_pressure;
	static constexpr value_type to_base(value_type v) noexcept { return v / value_type(750.061682704); }
	static constexpr value_type from_base(value_type v) noexcept { return v * value_type(750.061682704); }
};

template <class T> struct basic_atm {
	using value_type = T;
	using dimension = dim_pressure;
	static constexpr value_type to_base(value_type v) noexcept { return v / value_type(0.986923); }
	static constexpr value_type from_base(value_type v) noexcept { return v * value_type(0.986923); }
};

// ----- mass

template <class T> struct basic_kilogram {
	using value_type = T;
	using dimension = dim_mass;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_pound {
	using value_type = T;
	using dimension = dim_mass;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.453592333346); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.453592333346); }
};

template <class T> struct basic_ounce {
	using value_type = T;
	using dimension = dim_mass;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.0283495); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.0283495); }
};

template <class T> struct basic_troy_ounce {
	using value_type = T;
	using dimension = dim_mass;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(0.0311034768); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(0.0311034768); }
};

template <class T> struct basic_stone {
	using value_type = T;
	using dimension = dim_mass;
	static constexpr value_type to_base(value_type v) noexcept { return v * value_type(6.35029); }
	static constexpr value_type from_base(value_type v) noexcept { return v / value_type(6.35029); }
};

// ----- magnetism

template <class T> struct basic_tesla {
	using value_type = T;
	using dimension = dim_magnetic_flux;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_weber {
	using value_type = T;
	using dimension = dim_magnetic_flux_density;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

// ----- frequency

template <class T> struct basic_hertz {
	using value_type = T;
	using dimension = dim_frequency;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

// ----- force

template <class T> struct basic_newton {
	using value_type = T;
	using dimension = dim_force;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

// ----- energy

template <class T> struct basic_joule {
	using value_type = T;
	using dimension = dim_energy;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_watt {
	using value_type = T;
	using dimension = dim_power;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

// ----- electrical

template <class T> struct basic_ampere {
	using value_type = T;
	using dimension = dim_electric_current;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_volt {
	using value_type = T;
	using dimension = dim_voltage;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_coulomb {
	using value_type = T;
	using dimension = dim_electric_charge;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_farad {
	using value_type = T;
	using dimension = dim_capacitance;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_ohm {
	using value_type = T;
	using dimension = dim_electrical_resistance;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_siemens {
	using value_type = T;
	using dimension = dim_electrical_conductance;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

template <class T> struct basic_henry {
	using value_type = T;
	using dimension = dim_inductance;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};

// ----- time

template <class T> struct basic_second {
	using value_type = T;
	using dimension = dim_time;
	static constexpr value_type to_base(value_type v) noexcept { return v; }
	static constexpr value_type from_base(value_type v) noexcept { return v; }
};
// clang-format on
}
}

#endif
