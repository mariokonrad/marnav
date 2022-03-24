#ifndef MARNAV_NMEA_DBT_HPP
#define MARNAV_NMEA_DBT_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
	constexpr static sentence_id ID = sentence_id::DBT;
	constexpr static const char * TAG = "DBT";

	dbt();
	dbt(const dbt &) = default;
	dbt & operator=(const dbt &) = default;
	dbt(dbt &&) = default;
	dbt & operator=(dbt &&) = default;

protected:
	dbt(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<units::feet> depth_feet_;
	std::optional<units::meters> depth_meter_;
	std::optional<units::fathoms> depth_fathom_;

public:
	std::optional<units::length> get_depth_feet() const;
	std::optional<units::length> get_depth_meter() const;
	std::optional<units::length> get_depth_fathom() const;

	void set_depth_feet(units::length t);
	void set_depth_meter(units::length t);
	void set_depth_fathom(units::length t);
};
}
}

#endif
