#ifndef MARNAV__NMEA__PGRMZ__HPP
#define MARNAV__NMEA__PGRMZ__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief PGRMZ - Garmin Altitude Information
///
/// @code
///        1   2 3
///        |   | |
/// $PGRMZ,x.x,f,h*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Altitude
/// 2. f=feet
/// 3. Fix Type
///    - 1 = no fix
///    - 2 = 2D fix
///    - 3 = 3D fix
///
/// Example: <tt>$PGRMZ,1494,f,*10</tt>
///
class pgrmz : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::PGRMZ;
	constexpr static const char * TAG = "PGRMZ";

	enum class fix_type : char {
		no_fix, ///< NMEA representation: '1'
		d2fix, ///< NMEA representation: '2'
		d3fix ///< NMEA representation: '3'
	};

	pgrmz();
	pgrmz(const pgrmz &) = default;
	pgrmz & operator=(const pgrmz &) = default;
	pgrmz(pgrmz &&) = default;
	pgrmz & operator=(pgrmz &&) = default;

protected:
	pgrmz(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	double altitude = 0.0;
	unit::distance altitude_unit = unit::distance::feet;
	utils::optional<fix_type> fix;

public:
	decltype(altitude) get_altitude() const { return altitude; }
	decltype(altitude_unit) get_altitude_unit() const { return altitude_unit; }
	decltype(fix) get_fix() const { return fix; }

	void set_altitude(double t) noexcept
	{
		altitude = t;
		altitude_unit = unit::distance::feet;
	}
	void set_fix(fix_type t) noexcept { fix = t; }
};

std::string to_string(pgrmz::fix_type value);
}
}

#endif
