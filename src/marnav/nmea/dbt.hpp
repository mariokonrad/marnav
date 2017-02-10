#ifndef MARNAV__NMEA__DBT__HPP
#define MARNAV__NMEA__DBT__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief DBT - Depth Below Transducer
///
/// @code
///        1   2 3   4 5   6
///        |   | |   | |   |
/// $--DBT,x.x,f,x.x,M,x.x,F*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Depth feet
/// 2. Depth feet unit
///    - f = feet
/// 3. Depth meters
/// 4. Depth meters unit
///    - M = meters
/// 5. Depth Fathoms
/// 6. Depth Fathoms unit
///    - F = Fathoms
///
/// In real-world sensors, sometimes not all three conversions are reported.
/// So you night see something like <tt>$SDDBT,,f,22.5,M,,F*cs</tt>
///
class dbt : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::DBT;
	constexpr static const char * TAG = "DBT";

	dbt();
	dbt(const dbt &) = default;
	dbt & operator=(const dbt &) = default;
	dbt(dbt &&) = default;
	dbt & operator=(dbt &&) = default;

protected:
	dbt(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> depth_feet; // water depth in feet
	utils::optional<unit::distance> depth_feet_unit; // f:feet
	utils::optional<double> depth_meter; // water depth in meter
	utils::optional<unit::distance> depth_meter_unit; // M:meter
	utils::optional<double> depth_fathom; // water depth in fathom
	utils::optional<unit::distance> depth_fathom_unit; // F:fathom

public:
	decltype(depth_feet) get_depth_feet() const { return depth_feet; }
	decltype(depth_feet_unit) get_depth_feet_unit() const { return depth_feet_unit; }
	decltype(depth_meter) get_depth_meter() const { return depth_meter; }
	decltype(depth_meter_unit) get_depth_meter_unit() const { return depth_meter_unit; }
	decltype(depth_fathom) get_depth_fathom() const { return depth_fathom; }
	decltype(depth_fathom_unit) get_depth_fathom_unit() const { return depth_fathom_unit; }

	void set_depth_feet(double t) noexcept;
	void set_depth_meter(double t) noexcept;
	void set_depth_fathom(double t) noexcept;
};
}
}

#endif
