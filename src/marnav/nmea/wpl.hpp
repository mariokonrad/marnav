#ifndef __NMEA__WPL__HPP__
#define __NMEA__WPL__HPP__

#include "sentence.hpp"
#include "angle.hpp"
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
public:
	constexpr static const sentence_id ID = sentence_id::WPL;
	constexpr static const char * TAG = "WPL";

	wpl();
	wpl(const wpl &) = default;
	wpl & operator=(const wpl &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<geo::latitude> lat;
	utils::optional<char> lat_hem; // latitude hemisphere (N or S)
	utils::optional<geo::longitude> lon;
	utils::optional<char> lon_hem; // longitude hemisphere (E or W)
	utils::optional<std::string> waypoint_id;

public:
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(waypoint_id) get_waypoint() const { return waypoint_id; }

	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_waypoint(const std::string & id);
};
}
}

#endif
