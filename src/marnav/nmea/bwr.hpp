#ifndef __NMEA__BWR__HPP__
#define __NMEA__BWR__HPP__

#include "sentence.hpp"
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief BWR - Bearing & Distance to Waypoint - Geat Circle
///
/// @code
///                                                         12
///        1         2       3 4        5 6   7 8   9 10  11|    13 14
///        |         |       | |        | |   | |   | |   | |    |   |
/// $--BWR,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x.x,T,x.x,M,x.x,N,c--c,m*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1.  UTCTime
/// 2.  Waypoint Latitude
/// 3.  N = North, S = South
/// 4.  Waypoint Longitude
/// 5.  E = East, W = West
/// 6.  Bearing, True
/// 7.  T = True
/// 8.  Bearing, Magnetic
/// 9.  M = Magnetic
/// 10. Nautical Miles
/// 11. N = Nautical Miles
/// 12. Waypoint ID
/// 13. Checksum
///
class bwr : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::BWR;
	constexpr static const char * TAG = "BWR";

	bwr();
	bwr(const bwr &) = default;
	bwr & operator=(const bwr &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time_utc;
	utils::optional<geo::latitude> lat;
	utils::optional<char> lat_hem;
	utils::optional<geo::longitude> lon;
	utils::optional<char> lon_hem;
	utils::optional<double> bearing_true;
	utils::optional<char> bearing_true_ref;
	utils::optional<double> bearing_mag;
	utils::optional<char> bearing_mag_ref;
	utils::optional<double> distance; // nautical miles
	utils::optional<char> distance_unit;
	utils::optional<std::string> waypoint_id;

public:
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(bearing_true) get_bearing_true() const { return bearing_true; }
	decltype(bearing_true_ref) get_bearing_true_ref() const { return bearing_true_ref; }
	decltype(bearing_mag) get_bearing_mag() const { return bearing_mag; }
	decltype(bearing_mag_ref) get_bearing_mag_ref() const { return bearing_mag_ref; }
	decltype(distance) get_distance() const { return distance; }
	decltype(distance_unit) get_distance_unit() const { return distance_unit; }
	decltype(waypoint_id) get_waypoint_id() const { return waypoint_id; }

	void set_time_utc(const nmea::time & t) { time_utc = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_bearing_true(double t);
	void set_bearing_mag(double t);
	void set_distance(double t);
	void set_waypoint(const std::string & id);
};
}
}

#endif
