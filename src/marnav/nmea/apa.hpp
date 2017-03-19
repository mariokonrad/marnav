#ifndef MARNAV__NMEA__APA__HPP
#define MARNAV__NMEA__APA__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief APA - Autopilot Sentence "A"
///
/// This sentence is sent by some GPS receivers to allow them to be used to control
/// an autopilot unit. This sentence is commonly used by autopilots and contains
/// navigation receiver warning flag status, cross-track-error, waypoint arrival status,
/// initial bearing from origin waypoint to the destination, continuous bearing from
/// present position to destination and recommended heading-to-steer to destination
/// waypoint for the active navigation leg of the journey.
///
/// @code
///        1 2 3    4 5 6 7 8   9 10
///        | | |    | | | | |   | |
/// $--APA,A,A,x.xx,L,N,A,A,xxx,M,c---c*hh<CR><LF>
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
///     - K = Kilometers
/// 6.  Status
///     - A = Arrival Circle Entered
/// 7.  Status
///     - A = Perpendicular passed at waypoint
/// 8.  Bearing origin to destination
/// 9.  Bearing origin to destination reference
///     - M = Magnetic
///     - T = True
/// 10. Destination Waypoint ID
///
/// @note Not recommended for new designs.
///
class apa : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::APA;
	constexpr static const char * TAG = "APA";

	apa();
	apa(const apa &) = default;
	apa & operator=(const apa &) = default;
	apa(apa &&) = default;
	apa & operator=(apa &&) = default;

protected:
	apa(talker talk, fields::const_iterator first, fields::const_iterator last);
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
};
}
}

#endif
