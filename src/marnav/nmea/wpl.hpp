#ifndef __NMEA__WPL__HPP__
#define __NMEA__WPL__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(wpl)

/// @brief WPL - Waypoint Location
///
/// @code
///        1       2 3        4 5
///        |       | |        | |
/// $--WPL,llll.ll,a,yyyyy.yy,a,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Latitude
/// 2. Latitude hemisphere
///    - N = North
///    - S = South
/// 3. Longitude
/// 4. Longitude hemisphere
///    - E = East
///    - W = West
/// 5. Waypoint ID
///
class wpl : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(wpl)

public:
	constexpr static const sentence_id ID = sentence_id::WPL;
	constexpr static const char * TAG = "WPL";

	wpl();
	wpl(const wpl &) = default;
	wpl & operator=(const wpl &) = default;
	wpl(wpl &&) = default;
	wpl & operator=(wpl &&) = default;

protected:
	wpl(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<geo::latitude> lat;
	utils::optional<direction> lat_hem; // latitude hemisphere (N or S)
	utils::optional<geo::longitude> lon;
	utils::optional<direction> lon_hem; // longitude hemisphere (E or W)
	utils::optional<waypoint> waypoint_id;

public:
	MARNAV_NMEA_GETTER(waypoint_id)

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_waypoint(const waypoint & id) { waypoint_id = id; }
};
}
}

#endif
