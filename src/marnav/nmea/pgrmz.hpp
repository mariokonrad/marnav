#ifndef __NMEA__PGRMZ__HPP__
#define __NMEA__PGRMZ__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(pgrmz)

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
/// 3. Position fix dimensions
///    - 2 = user altitude
///    - 3 = GPS altitude
///
/// Example: <tt>$PGRMZ,1494,f,*10</tt>
///
class pgrmz : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(pgrmz)

public:
	constexpr static const sentence_id ID = sentence_id::PGRMZ;
	constexpr static const char * TAG = "PGRMZ";

	virtual ~pgrmz() {}

	pgrmz();
	pgrmz(const pgrmz &) = default;
	pgrmz & operator=(const pgrmz &) = default;

protected:
	pgrmz(
		const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	double altitude = 0.0;
	unit::distance altitude_unit = unit::distance::feet;
	utils::optional<uint32_t> pos_fix_dim; /// @todo Maybe here is an enumeration in order?

public:
	NMEA_GETTER(altitude)
	NMEA_GETTER(altitude_unit)
	NMEA_GETTER(pos_fix_dim)

	void set_altitude(double t) noexcept
	{
		altitude = t;
		altitude_unit = unit::distance::feet;
	}
	void set_pos_fix_dim(uint32_t t) noexcept;
};
}
}

#endif
