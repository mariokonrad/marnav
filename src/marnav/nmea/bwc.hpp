#ifndef MARNAV__NMEA__BWC__HPP
#define MARNAV__NMEA__BWC__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief BWC - Bearing & Distance to Waypoint - Geat Circle
///
/// @code
///                                                         12
///        1         2       3 4        5 6   7 8   9 10  11|    13
///        |         |       | |        | |   | |   | |   | |    |
/// $--BWC,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x.x,T,x.x,M,x.x,N,c--c,m*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  UTCTime
/// 2.  Waypoint Latitude
/// 3.  Latitude Hemisphere
///     - N = North
///     - S = South
/// 4.  Waypoint Longitude
/// 5.  Longitude Hemisphere
///     - E = East
///     - W = West
/// 6.  Bearing True
/// 7.  Bearing True reference
///     - T = True
/// 8.  Bearing Magnetic
/// 9.  Bearing Magnetic reference
///     - M = Magnetic
/// 10. Nautical Miles
/// 11. Nautical Miles unit
///     - N = Nautical Miles
/// 12. Waypoint ID
/// 13. Mode Indicator
///     - A = Autonomous
///     - D = Differential
///     - E = Estimated
///     - M = Manual Input
///     - S = Simulated
///     - N = Data not valid
///
/// Example: <tt>$GPBWC,081837,,,,,,T,,M,,N,*13</tt>
///
/// Example: <tt>$GPBWC,220516,5130.02,N,00046.34,W,213.8,T,218.0,M,0004.6,N,EGLM*11</tt>
///
class bwc : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::BWC;
	constexpr static const char * TAG = "BWC";

	bwc();
	bwc(const bwc &) = default;
	bwc & operator=(const bwc &) = default;
	bwc(bwc &&) = default;
	bwc & operator=(bwc &&) = default;

protected:
	bwc(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time_utc;
	utils::optional<geo::latitude> lat;
	utils::optional<direction> lat_hem;
	utils::optional<geo::longitude> lon;
	utils::optional<direction> lon_hem;
	utils::optional<double> bearing_true;
	utils::optional<reference> bearing_true_ref;
	utils::optional<double> bearing_mag;
	utils::optional<reference> bearing_mag_ref;
	utils::optional<double> distance; // nautical miles
	utils::optional<unit::distance> distance_unit;
	utils::optional<waypoint> waypoint_id;
	utils::optional<mode_indicator> mode_ind; // NMEA 2.3 and later

public:
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(bearing_true) get_bearing_true() const { return bearing_true; }
	decltype(bearing_true_ref) get_bearing_true_ref() const { return bearing_true_ref; }
	decltype(bearing_mag) get_bearing_mag() const { return bearing_mag; }
	decltype(bearing_mag_ref) get_bearing_mag_ref() const { return bearing_mag_ref; }
	decltype(distance) get_distance() const { return distance; }
	decltype(distance_unit) get_distance_unit() const { return distance_unit; }
	decltype(waypoint_id) get_waypoint_id() const { return waypoint_id; }
	decltype(mode_ind) get_mode_ind() const { return mode_ind; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_time_utc(const nmea::time & t) noexcept { time_utc = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_bearing_true(double t) noexcept;
	void set_bearing_mag(double t) noexcept;
	void set_distance(double t) noexcept;
	void set_waypoint(const waypoint & id) { waypoint_id = id; }
	void set_mode_indicator(mode_indicator t) noexcept { mode_ind = t; }
};
}
}

#endif
