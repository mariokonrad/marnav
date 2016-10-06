#ifndef __NMEA__TLL__HPP__
#define __NMEA__TLL__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(tll)

/// @brief TLL - Target latitude and longitude
///
/// @code
///        1  2        3 4         5 6    7         8 9
///        |  |        | |         | |    |         | |
/// $--TLL,xx,llll.lll,a,yyyyy.yyy,a,c--c,hhmmss.ss,a,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Target number 00 - 99
/// 2. Latitude
/// 3. Latitude hemisphere
///    - N = North
///    - S = South
/// 4. Longitude
/// 5. Longitude hemisphere
///    - E = East
///    - W = West
/// 6. Target name
/// 7. UTC of data
/// 8. Target status
///    - L = lost,tracked target has beenlost
///    - Q = query,target in the process of acquisition
///    - T = tracking
/// 9. Reference target
///    - R
///    - null/empty
///
class tll : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(tll)

public:
	constexpr static const sentence_id ID = sentence_id::TLL;
	constexpr static const char * TAG = "TLL";

	tll();
	tll(const tll &) = default;
	tll & operator=(const tll &) = default;
	tll(tll &&) = default;
	tll & operator=(tll &&) = default;

protected:
	tll(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	uint32_t number = 0;
	geo::latitude lat;
	direction lat_hem = direction::north;
	geo::longitude lon;
	direction lon_hem = direction::east;
	waypoint name;
	nmea::time time_utc;
	target_status status = target_status::tracking;
	utils::optional<char> reference_target;

public:
	decltype(number) get_number() const { return number; }
	decltype(name) get_name() const { return name; }
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(status) get_status() const { return status; }
	decltype(reference_target) get_reference_target() const { return reference_target; }

	geo::longitude get_longitude() const;
	geo::latitude get_latitude() const;

	void set_number(uint32_t t) noexcept { number = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_name(const waypoint & t) { name = t; }
	void set_time_utc(const nmea::time & t) noexcept { time_utc = t; }
	void set_status(target_status t) noexcept { status = t; }
	void set_reference_target(char t) noexcept { reference_target = t; }
};
}
}

#endif
