#ifndef __NMEA__RMB__HPP__
#define __NMEA__RMB__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(rmb)

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
	MARNAV_NMEA_SENTENCE_FRIENDS(rmb)

public:
	constexpr static const sentence_id ID = sentence_id::RMB;
	constexpr static const char * TAG = "RMB";

	virtual ~rmb() {}

	rmb();
	rmb(const rmb &) = default;
	rmb & operator=(const rmb &) = default;

protected:
	rmb(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<status> active; // V:warning
	utils::optional<double> cross_track_error; // cross track error in nautical miles
	utils::optional<side> steer_dir; // direction to steer, left or right
	utils::optional<waypoint> waypoint_to; // TO waypoint ID
	utils::optional<waypoint> waypoint_from; // FROM waypoint ID
	utils::optional<geo::latitude> lat; // destination waypoint latitude
	utils::optional<direction> lat_hem; // destination waypoint latitude dir, N:north, S:south
	utils::optional<geo::longitude> lon; // destination waypoint longitude
	utils::optional<direction> lon_hem; // destination waypoint longitude dir, E:east, W:west
	utils::optional<double> range; // range to destination in nautical miles
	utils::optional<double> bearing; // bearing to destination in degrees to true
	utils::optional<double> dst_velocity; // destination closing velocity in knots
	utils::optional<status> arrival_status; // arrival status, A:arrival circle entered
	utils::optional<mode_indicator> mode_ind;

public:
	MARNAV_NMEA_GETTER(active)
	MARNAV_NMEA_GETTER(cross_track_error)
	MARNAV_NMEA_GETTER(steer_dir)
	MARNAV_NMEA_GETTER(waypoint_to)
	MARNAV_NMEA_GETTER(waypoint_from)
	MARNAV_NMEA_GETTER(range)
	MARNAV_NMEA_GETTER(bearing)
	MARNAV_NMEA_GETTER(dst_velocity)
	MARNAV_NMEA_GETTER(arrival_status)
	MARNAV_NMEA_GETTER(mode_ind)

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_active(status t) noexcept { active = t; }
	void set_cross_track_error(double t) noexcept { cross_track_error = t; }
	void set_steer_dir(side t) noexcept { steer_dir = t; }
	void set_waypoint_to(const waypoint & id) { waypoint_to = id; }
	void set_waypoint_from(const waypoint & id) { waypoint_from = id; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_range(double t) noexcept { range = t; }
	void set_bearing(double t) noexcept { bearing = t; }
	void set_dst_velocity(double t) noexcept { dst_velocity = t; }
	void set_arrival_status(status t) noexcept { arrival_status = t; }
	void set_mode_indicator(mode_indicator t) noexcept { mode_ind = t; }
};
}
}

#endif
