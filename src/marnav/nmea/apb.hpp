#ifndef MARNAV__NMEA__APB__HPP
#define MARNAV__NMEA__APB__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief APB - Autopilot Sentence "B"
///
/// This is a fixed form of the APA sentence with some ambiguities removed.
///
/// @code
///                                         13    15
///        1 2 3   4 5 6 7 8   9 10   11  12|   14|
///        | | |   | | | | |   | |    |   | |   | |
/// $--APB,A,A,x.x,a,N,A,A,x.x,a,c--c,x.x,a,x.x,a,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Status
///     - A = Data valid
///     - V = LORAN-C Blink or SNR warning
///     - V = general warning flag or other navigation systems when a reliable fix is not
///           available
/// 2.  Status
///     - A = Data valid or not used
///     - V = Loran-C Cycle Lock warning flag
/// 3.  Magnitude of Cross Track Error
/// 4.  Direction to steer
///     - L
///     - R
/// 5.  Cross Track Units
///     - N = Nautical Miles
/// 6.  Status
///     - A = Arrival Circle Entered
/// 7.  Status
///     - A = Perpendicular passed at waypoint
/// 8.  Bearing origin to destination
/// 9.  Bearing origin to destination reference
///     - M = Magnetic
///     - T = True
/// 10. Destination Waypoint ID
/// 11. Bearing, present position to destination
/// 12. Bearing, present position to destination reference
///     - M = Magnetic
///     - T = True
/// 13. Heading to steer to destination waypoint
/// 14. Heading to steer to destination waypoint reference
///     - M = Magnetic
///     - T = True
/// 15. Mode indicator
///     - V = Invalid
///     - A = Autonomous
///     - D = Differential
///
class apb : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::APB;
	constexpr static const char * TAG = "APB";

	apb();
	apb(const apb &) = default;
	apb & operator=(const apb &) = default;
	apb(apb &&) = default;
	apb & operator=(apb &&) = default;

protected:
	apb(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<status> loran_c_blink_warning;
	utils::optional<status> loran_c_cycle_lock_warning;
	utils::optional<double> cross_track_error_magnitude;
	utils::optional<side> direction_to_steer;
	utils::optional<unit::distance> cross_track_unit;
	utils::optional<status> status_arrival;
	utils::optional<status> status_perpendicular_passing;
	utils::optional<double> bearing_origin_to_destination;
	utils::optional<reference> bearing_origin_to_destination_ref;
	utils::optional<waypoint> waypoint_id;
	utils::optional<double> bearing_pos_to_destination;
	utils::optional<reference> bearing_pos_to_destination_ref;
	utils::optional<double> heading_to_steer_to_destination;
	utils::optional<reference> heading_to_steer_to_destination_ref;
	utils::optional<mode_indicator> mode_ind;

	void check() const;

public:
	decltype(loran_c_blink_warning) get_loran_c_blink_warning() const
	{
		return loran_c_blink_warning;
	}
	decltype(loran_c_cycle_lock_warning) get_loran_c_cycle_lock_warning() const
	{
		return loran_c_cycle_lock_warning;
	}
	decltype(cross_track_error_magnitude) get_cross_track_error_magnitude() const
	{
		return cross_track_error_magnitude;
	}
	decltype(direction_to_steer) get_direction_to_steer() const { return direction_to_steer; }
	decltype(cross_track_unit) get_cross_track_unit() const { return cross_track_unit; }
	decltype(status_arrival) get_status_arrival() const { return status_arrival; }
	decltype(status_perpendicular_passing) get_status_perpendicular_passing() const
	{
		return status_perpendicular_passing;
	}
	decltype(bearing_origin_to_destination) get_bearing_origin_to_destination() const
	{
		return bearing_origin_to_destination;
	}
	decltype(bearing_origin_to_destination_ref) get_bearing_origin_to_destination_ref() const
	{
		return bearing_origin_to_destination_ref;
	}
	decltype(waypoint_id) get_waypoint_id() const { return waypoint_id; }
	decltype(bearing_pos_to_destination) get_bearing_pos_to_destination() const
	{
		return bearing_pos_to_destination;
	}
	decltype(bearing_pos_to_destination_ref) get_bearing_pos_to_destination_ref() const
	{
		return bearing_pos_to_destination_ref;
	}
	decltype(heading_to_steer_to_destination) get_heading_to_steer_to_destination() const
	{
		return heading_to_steer_to_destination;
	}
	decltype(heading_to_steer_to_destination_ref)
	get_heading_to_steer_to_destination_ref() const
	{
		return heading_to_steer_to_destination_ref;
	}
	decltype(mode_ind) get_mode_ind() const { return mode_ind; }

	void set_loran_c_blink_warning(status t) noexcept { loran_c_blink_warning = t; }
	void set_loran_c_cycle_lock_warning(status t) noexcept { loran_c_cycle_lock_warning = t; }
	void set_cross_track_error_magnitude(double t) noexcept
	{
		cross_track_error_magnitude = t;
		cross_track_unit = unit::distance::nm;
	}
	void set_direction_to_steer(side t) noexcept { direction_to_steer = t; }
	void set_status_arrival(status t) noexcept { status_arrival = t; }
	void set_status_perpendicular_passing(status t) noexcept
	{
		status_perpendicular_passing = t;
	}
	void set_bearing_origin_to_destination(double t, reference ref);
	void set_waypoint_id(const waypoint & id) { waypoint_id = id; }
	void set_bearing_pos_to_destination(double t, reference ref);
	void set_heading_to_steer_to_destination(double t, reference ref);
	void set_mode_indicator(mode_indicator t);
};
}
}

#endif
