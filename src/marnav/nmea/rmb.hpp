#ifndef __NMEA__RMB__HPP__
#define __NMEA__RMB__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief RMB - Recommended Minimum Navigation Information
///
/// To be sent by a navigation receiver when a destination waypoint is active.
///
/// @code
///                                                             14
///        1 2   3 4    5    6       7 8        9 10  11  12  13|
///        | |   | |    |    |       | |        | |   |   |   | |
/// $--RMB,A,x.x,a,c--c,c--c,llll.ll,a,yyyyy.yy,a,x.x,x.x,x.x,A,m,*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Status
///     - A = Active
///     - V = Void
/// 2.  Cross Track error - nautical miles
/// 3.  Direction to Steer
///     - L = Left
///     - R = Right
/// 4.  TO Waypoint ID
/// 5.  FROM Waypoint ID
/// 6.  Destination Waypoint Latitude
/// 7.  Destination Waypoint Latitude hemisphere
///     - N = North
///     - S = South
/// 8.  Destination Waypoint Longitude
/// 9.  Destination Waypoint Longitude hemisphere
///     - E = East
///     - W = West
/// 10. Range to destination in nautical miles
/// 11. Bearing to destination in degrees True
/// 12. Destination closing velocity in knots
/// 13. Arrival Status
///     - A = Arrival Circle Entered
///     - V = Not Entered
/// 14. FAA mode indicator (NMEA 2.3 and later)
///
/// Example:
/// @code
/// $GPRMB,A,0.66,L,003,004,4917.24,N,12309.57,W,001.3,052.5,000.5,V*0B
/// @endcode
///
class rmb : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::RMB;
	constexpr static const char * TAG = "RMB";

	rmb();
	rmb(const rmb &) = default;
	rmb & operator=(const rmb &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument,
		std::runtime_error);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<status> active; // V:warning
	utils::optional<double> cross_track_error; // cross track error in nautical miles
	utils::optional<side> steer_dir; // direction to steer, left or right
	utils::optional<std::string> waypoint_to; // TO waypoint ID
	utils::optional<std::string> waypoint_from; // FROM waypoint ID
	utils::optional<geo::latitude> lat; // destination waypoint latitude
	utils::optional<direction> lat_hem; // destination waypoint latitude dir, N:north, S:south
	utils::optional<geo::longitude> lon; // destination waypoint longitude
	utils::optional<direction> lon_hem; // destination waypoint longitude dir, E:east, W:west
	utils::optional<double> range; // range to destination in nautical miles
	utils::optional<double> bearing; // bearing to destination in degrees to true
	utils::optional<double> dst_velocity; // destination closing velocity in knots
	utils::optional<status> arrival_status; // arrival status, A:arrival circle entered
	utils::optional<positioning_system_mode_indicator> mode_indicator;

public:
	NMEA_GETTER(active)
	NMEA_GETTER(cross_track_error)
	NMEA_GETTER(steer_dir)
	NMEA_GETTER(waypoint_to)
	NMEA_GETTER(waypoint_from)
	NMEA_GETTER(lat)
	NMEA_GETTER(lat_hem)
	NMEA_GETTER(lon)
	NMEA_GETTER(lon_hem)
	NMEA_GETTER(range)
	NMEA_GETTER(bearing)
	NMEA_GETTER(dst_velocity)
	NMEA_GETTER(arrival_status)
	NMEA_GETTER(mode_indicator)

	void set_active(status t) { active = t; }
	void set_cross_track_error(double t) { cross_track_error = t; }
	void set_steer_dir(side t) { steer_dir = t; }
	void set_waypoint_to(const std::string & id);
	void set_waypoint_from(const std::string & id);
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_range(double t) { range = t; }
	void set_bearing(double t) { bearing = t; }
	void set_dst_velocity(double t) { dst_velocity = t; }
	void set_arrival_status(status t) { arrival_status = t; }
	void set_mode_indicator(positioning_system_mode_indicator t) { mode_indicator = t; }
};
}
}

#endif
