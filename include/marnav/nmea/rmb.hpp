#ifndef MARNAV_NMEA_RMB_HPP
#define MARNAV_NMEA_RMB_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav::nmea
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
/// 4.  Origin Waypoint ID
/// 5.  Destination Waypoint ID
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::RMB;
	constexpr static const char * TAG = "RMB";

	rmb();
	rmb(const rmb &) = default;
	rmb & operator=(const rmb &) = default;
	rmb(rmb &&) = default;
	rmb & operator=(rmb &&) = default;

protected:
	rmb(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<status> active_; // V:warning
	std::optional<units::nautical_miles>
		cross_track_error_; // cross track error in nautical miles
	std::optional<side> steer_dir_; // direction to steer, left or right
	std::optional<waypoint> waypoint_from_; // Origin waypoint ID
	std::optional<waypoint> waypoint_to_; // Destination waypoint ID
	std::optional<geo::latitude> lat_; // destination waypoint latitude
	std::optional<direction> lat_hem_; // destination waypoint latitude dir, N:north, S:south
	std::optional<geo::longitude> lon_; // destination waypoint longitude
	std::optional<direction> lon_hem_; // destination waypoint longitude dir, E:east, W:west
	std::optional<units::nautical_miles> range_; // range to destination in nautical miles
	std::optional<double> bearing_; // bearing to destination in degrees to true
	std::optional<units::knots> dst_velocity_; // destination closing velocity in knots
	std::optional<status> arrival_status_; // arrival status, A:arrival circle entered
	std::optional<mode_indicator> mode_ind_;

public:
	std::optional<status> get_active() const { return active_; }
	std::optional<units::length> get_cross_track_error() const;
	std::optional<side> get_steer_dir() const { return steer_dir_; }
	std::optional<waypoint> get_waypoint_to() const { return waypoint_to_; }
	std::optional<waypoint> get_waypoint_from() const { return waypoint_from_; }
	std::optional<units::length> get_range() const;
	std::optional<double> get_bearing() const { return bearing_; }
	std::optional<units::velocity> get_dst_velocity() const;
	std::optional<status> get_arrival_status() const { return arrival_status_; }
	std::optional<mode_indicator> get_mode_ind() const { return mode_ind_; }

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;

	void set_active(status t) noexcept { active_ = t; }
	void set_cross_track_error(units::length t);
	void set_steer_dir(side t) noexcept { steer_dir_ = t; }
	void set_waypoint_to(const waypoint & id) { waypoint_to_ = id; }
	void set_waypoint_from(const waypoint & id) { waypoint_from_ = id; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_range(units::length t);
	void set_bearing(double t) noexcept { bearing_ = t; }
	void set_dst_velocity(units::velocity t);
	void set_arrival_status(status t) noexcept { arrival_status_ = t; }
	void set_mode_indicator(mode_indicator t) noexcept { mode_ind_ = t; }
};
}

#endif
