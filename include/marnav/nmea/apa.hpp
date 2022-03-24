#ifndef MARNAV_NMEA_APA_HPP
#define MARNAV_NMEA_APA_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <optional>

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
	constexpr static sentence_id ID = sentence_id::APA;
	constexpr static const char * TAG = "APA";

	apa();
	apa(const apa &) = default;
	apa & operator=(const apa &) = default;
	apa(apa &&) = default;
	apa & operator=(apa &&) = default;

protected:
	apa(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<status> loran_c_blink_warning_;
	std::optional<status> loran_c_cycle_lock_warning_;
	std::optional<double> cross_track_error_magnitude_;
	std::optional<side> direction_to_steer_;
	std::optional<unit::distance> cross_track_unit_;
	std::optional<status> status_arrival_;
	std::optional<status> status_perpendicular_passing_;
	std::optional<double> bearing_origin_to_destination_;
	std::optional<reference> bearing_origin_to_destination_ref_;
	std::optional<waypoint> waypoint_id_;

	void check() const;

public:
	std::optional<status> get_loran_c_blink_warning() const { return loran_c_blink_warning_; }
	std::optional<status> get_loran_c_cycle_lock_warning() const
	{
		return loran_c_cycle_lock_warning_;
	}
	std::optional<double> get_cross_track_error_magnitude() const
	{
		return cross_track_error_magnitude_;
	}
	std::optional<side> get_direction_to_steer() const { return direction_to_steer_; }
	std::optional<unit::distance> get_cross_track_unit() const { return cross_track_unit_; }
	std::optional<status> get_status_arrival() const { return status_arrival_; }
	std::optional<status> get_status_perpendicular_passing() const
	{
		return status_perpendicular_passing_;
	}
	std::optional<double> get_bearing_origin_to_destination() const
	{
		return bearing_origin_to_destination_;
	}
	std::optional<reference> get_bearing_origin_to_destination_ref() const
	{
		return bearing_origin_to_destination_ref_;
	}
	std::optional<waypoint> get_waypoint_id() const { return waypoint_id_; }

	void set_loran_c_blink_warning(status t) noexcept { loran_c_blink_warning_ = t; }
	void set_loran_c_cycle_lock_warning(status t) noexcept { loran_c_cycle_lock_warning_ = t; }
	void set_cross_track_error_magnitude(double t) noexcept
	{
		cross_track_error_magnitude_ = t;
		cross_track_unit_ = unit::distance::nm;
	}
	void set_direction_to_steer(side t) noexcept { direction_to_steer_ = t; }
	void set_status_arrival(status t) noexcept { status_arrival_ = t; }
	void set_status_perpendicular_passing(status t) noexcept
	{
		status_perpendicular_passing_ = t;
	}
	void set_bearing_origin_to_destination(double t, reference ref);
	void set_waypoint_id(const waypoint & id) { waypoint_id_ = id; }
};
}
}

#endif
