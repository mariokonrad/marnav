#ifndef MARNAV__NMEA__WPL__HPP
#define MARNAV__NMEA__WPL__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
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
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::WPL;
	constexpr static const char * TAG = "WPL";

	wpl();
	wpl(const wpl &) = default;
	wpl & operator=(const wpl &) = default;
	wpl(wpl &&) = default;
	wpl & operator=(wpl &&) = default;

protected:
	wpl(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<geo::latitude> lat;
	utils::optional<direction> lat_hem; // latitude hemisphere (N or S)
	utils::optional<geo::longitude> lon;
	utils::optional<direction> lon_hem; // longitude hemisphere (E or W)
	utils::optional<waypoint> waypoint_id;

public:
	decltype(waypoint_id) get_waypoint_id() const { return waypoint_id; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_waypoint(const waypoint & id) { waypoint_id = id; }
};
}
}

#endif
