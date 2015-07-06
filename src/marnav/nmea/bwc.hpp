#ifndef __NMEA__BWC__HPP__
#define __NMEA__BWC__HPP__

#include "sentence.hpp"
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief BWC - Bearing & Distance to Waypoint - Geat Circle
///
/// @code
///                                                         12
///        1         2       3 4        5 6   7 8   9 10  11|    13 14
///        |         |       | |        | |   | |   | |   | |    |   |
/// $--BWC,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x.x,T,x.x,M,x.x,N,c--c,m*hh<CR><LF>
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
/// 13. FAA mode indicator (NMEA 2.3 and later, optional)
/// 14. Checksum
///
/// Example 1: <tt>$GPBWC,081837,,,,,,T,,M,,N,*13</tt>
///
/// Example 2: <tt>$GPBWC,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM*11</tt>
///
class bwc : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::BWC;
	constexpr static const char * TAG = "BWC";

	bwc();
	bwc(const bwc &) = default;
	bwc & operator=(const bwc &) = default;

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
	utils::optional<char> faa_mode_indicator; // NMEA 2.3 and later

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
	decltype(faa_mode_indicator) get_faa_mode_indicator() const { return faa_mode_indicator; }

	void set_time_utc(const nmea::time & t) { time_utc = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_bearing_true(double t);
	void set_bearing_mag(double t);
	void set_distance(double t);
	void set_waypoint(const std::string & id);
	void set_faa_mode_indicator(char t) { faa_mode_indicator = t; }
};
}
}

#endif
