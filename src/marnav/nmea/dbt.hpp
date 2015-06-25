#ifndef __NMEA__DBT__HPP__
#define __NMEA__DBT__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief DBT - Depth Below Transducer
///
/// @code
///        1   2 3   4 5   6 7
///        |   | |   | |   | |
/// $--DBT,x.x,f,x.x,M,x.x,F*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
///  1. Depth, feet
///  2. f = feet
///  3. Depth, meters
///  4. M = meters
///  5. Depth, Fathoms
///  6. F = Fathoms
///  7. Checksum
///
/// In real-world sensors, sometimes not all three conversions are reported.
/// So you night see something like <tt>$SDDBT,,f,22.5,M,,F*cs</tt>
///
class dbt : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::DBT;

	dbt();
	dbt(const dbt &) = default;
	dbt & operator=(const dbt &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> depth_feet; // water depth in feet
	utils::optional<char> depth_unit_feet; // f:feet
	utils::optional<double> depth_meter; // water depth in meter
	utils::optional<char> depth_unit_meter; // M:meter
	utils::optional<double> depth_fathom; // water depth in fathom
	utils::optional<char> depth_unit_fathom; // F:fathom

public:
	decltype(depth_feet) get_depth_feet() const { return depth_feet; }
	decltype(depth_unit_feet) get_depth_unit_feet() const { return depth_unit_feet; }
	decltype(depth_meter) get_depth_meter() const { return depth_meter; }
	decltype(depth_unit_meter) get_depth_unit_meter() const { return depth_unit_meter; }
	decltype(depth_fathom) get_depth_fathom() const { return depth_fathom; }
	decltype(depth_unit_fathom) get_depth_unit_fathom() const { return depth_unit_fathom; }

	void set_depth_feet(double t);
	void set_depth_meter(double t);
	void set_depth_fathom(double t);
};
}
}

#endif
