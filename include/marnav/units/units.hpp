#ifndef MARNAV_UNITS_UNITS_HPP
#define MARNAV_UNITS_UNITS_HPP

#include "detail/dimension.hpp"
#include "detail/basic_unit.hpp"
#include "detail/basic_unit_ops.hpp"
#include "detail/basic_unit_cmp.hpp"
#include "detail/basic_unit_fnc.hpp"
#include "detail/basic_quantity.hpp"
#include "detail/basic_quantity_ops.hpp"
#include "detail/basic_quantity_fnc.hpp"
#include "detail/basic_quantity_cmp.hpp"
#include "detail/units.hpp"

namespace marnav
{
namespace units
{
// clang-format off

// --- units

// length
using meters                 = basic_unit<basic_meter                     <double>>;
using feet                   = basic_unit<basic_foot                      <double>>;
using inches                 = basic_unit<basic_inch                      <double>>;
using yards                  = basic_unit<basic_yard                      <double>>;
using imperial_miles         = basic_unit<basic_imperial_mile             <double>>;
using nautical_miles         = basic_unit<basic_nautical_mile             <double>>;
using fathoms                = basic_unit<basic_fathom                    <double>>;

using kilometers             = basic_unit<basic_meter                     <double>, std::kilo>;
using millimeters            = basic_unit<basic_meter                     <double>, std::milli>;

// area
using squaremeters           = basic_unit<basic_squaremeter               <double>>;
using acres                  = basic_unit<basic_acre                      <double>>;

// volume
using qubicmeters            = basic_unit<basic_qubicmeter                <double>>;
using liters                 = basic_unit<basic_liter                     <double>>;
using gallons_uk             = basic_unit<basic_gallon_uk                 <double>>;
using quarts_uk              = basic_unit<basic_quart_uk                  <double>>;
using pints_uk               = basic_unit<basic_pint_uk                   <double>>;
using cups_uk                = basic_unit<basic_cup_uk                    <double>>;
using gallons_liquid_us      = basic_unit<basic_gallon_liquid_us          <double>>;
using quarts_liquid_us       = basic_unit<basic_quart_liquid_us           <double>>;
using pints_liquid_us        = basic_unit<basic_pint_liquid_us            <double>>;
using cups_liquid_us         = basic_unit<basic_cup_liquid_us             <double>>;
using gallons_dry_us         = basic_unit<basic_gallon_dry_us             <double>>;
using quarts_dry_us          = basic_unit<basic_quart_dry_us              <double>>;
using pints_dry_us           = basic_unit<basic_pint_dry_us               <double>>;

// velocity
using meters_per_second      = basic_unit<basic_meter_per_second          <double>>;
using knots                  = basic_unit<basic_knot                      <double>>;
using kilometers_per_hour    = basic_unit<basic_kilometer_per_hour        <double>>;
using miles_per_hour         = basic_unit<basic_mile_per_hour             <double>>;

// temperature
using kelvin                 = basic_unit<basic_kelvin                    <double>>;
using celsius                = basic_unit<basic_celsius                   <double>>;
using fahrenheit             = basic_unit<basic_fahrenheit                <double>>;
using rankine                = basic_unit<basic_rankine                   <double>>;
using reaumur                = basic_unit<basic_reaumur                   <double>>;

// pressure
using bar                    = basic_unit<basic_bar                       <double>>;
using pascal                 = basic_unit<basic_pascal                    <double>>;
using psi                    = basic_unit<basic_psi                       <double>>;
using torr                   = basic_unit<basic_torr                      <double>>;
using atm                    = basic_unit<basic_atm                       <double>>;

// mass
using kilograms              = basic_unit<basic_kilogram                  <double>>;
using pounds                 = basic_unit<basic_pound                     <double>>;
using ounces                 = basic_unit<basic_ounce                     <double>>;
using troy_ounces            = basic_unit<basic_troy_ounce                <double>>;
using stones                 = basic_unit<basic_stone                     <double>>;

// magnetism
using tesla                  = basic_unit<basic_tesla                     <double>>;
using weber                  = basic_unit<basic_weber                     <double>>;

// frequency
using hertz                  = basic_unit<basic_hertz                     <double>>;

// force
using newton                 = basic_unit<basic_newton                    <double>>;

// energy
using joule                  = basic_unit<basic_joule                     <double>>;
using watt                   = basic_unit<basic_watt                      <double>>;

// electric
using ampere                 = basic_unit<basic_ampere                    <double>>;
using volt                   = basic_unit<basic_volt                      <double>>;
using coulomb                = basic_unit<basic_coulomb                   <double>>;
using farad                  = basic_unit<basic_farad                     <double>>;
using ohm                    = basic_unit<basic_ohm                       <double>>;
using siemens                = basic_unit<basic_siemens                   <double>>;
using henry                  = basic_unit<basic_henry                     <double>>;

// time
using seconds                = basic_unit<basic_second                    <double>>;

// --- quantities

using length                 = basic_quantity<dim_length,                 double>;
using area                   = basic_quantity<dim_area,                   double>;
using volume                 = basic_quantity<dim_volume,                 double>;
using velocity               = basic_quantity<dim_velocity,               double>;
using temperature            = basic_quantity<dim_temperature,            double>;
using pressure               = basic_quantity<dim_pressure,               double>;
using mass                   = basic_quantity<dim_mass,                   double>;
using magnetic_flux_density  = basic_quantity<dim_magnetic_flux_density,  double>;
using magnetic_flux          = basic_quantity<dim_magnetic_flux,          double>;
using frequency              = basic_quantity<dim_frequency,              double>;
using force                  = basic_quantity<dim_force,                  double>;
using energy                 = basic_quantity<dim_energy,                 double>;
using power                  = basic_quantity<dim_power,                  double>;
using electric_current       = basic_quantity<dim_electric_current,       double>;
using voltage                = basic_quantity<dim_voltage,                double>;
using electric_charge        = basic_quantity<dim_electric_charge,        double>;
using capacitance            = basic_quantity<dim_capacitance,            double>;
using electrical_resistance  = basic_quantity<dim_electrical_resistance,  double>;
using electrical_conductance = basic_quantity<dim_electrical_conductance, double>;
using inductance             = basic_quantity<dim_inductance,             double>;
using time                   = basic_quantity<dim_time,                   double>;

// clang-format on
}
}

#endif
