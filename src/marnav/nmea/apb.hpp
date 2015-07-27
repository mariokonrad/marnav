#ifndef __NMEA__APB__HPP__
#define __NMEA__APB__HPP__

#include "sentence.hpp"
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
public:
	constexpr static const sentence_id ID = sentence_id::APB;
	constexpr static const char * TAG = "APB";

	apb();
	apb(const apb &) = default;
	apb & operator=(const apb &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<char> loran_c_blink_warning;
	utils::optional<char> loran_c_cycle_lock_warning;
	utils::optional<double> cross_track_error_magnitude;
	utils::optional<side> direction_to_steer; // L or R
	utils::optional<char> cross_track_unit; // N = nautical miles
	utils::optional<char> status_arrival;
	utils::optional<char> status_perpendicular_passing;
	utils::optional<uint32_t> bearing_origin_to_destination;
	utils::optional<char> bearing_origin_to_destination_ref;
	utils::optional<std::string> waypoint_id;
	utils::optional<uint32_t> bearing_pos_to_destination;
	utils::optional<char> bearing_pos_to_destination_ref;
	utils::optional<uint32_t> heading_to_steer_to_destination;
	utils::optional<char> heading_to_steer_to_destination_ref;
	utils::optional<char> mode_indicator;

	void check() const throw(std::invalid_argument);

public:
	NMEA_GETTER(loran_c_blink_warning)
	NMEA_GETTER(loran_c_cycle_lock_warning)
	NMEA_GETTER(cross_track_error_magnitude)
	NMEA_GETTER(direction_to_steer)
	NMEA_GETTER(cross_track_unit)
	NMEA_GETTER(status_arrival)
	NMEA_GETTER(status_perpendicular_passing)
	NMEA_GETTER(bearing_origin_to_destination)
	NMEA_GETTER(bearing_origin_to_destination_ref)
	NMEA_GETTER(waypoint_id)
	NMEA_GETTER(bearing_pos_to_destination)
	NMEA_GETTER(bearing_pos_to_destination_ref)
	NMEA_GETTER(heading_to_steer_to_destination)
	NMEA_GETTER(heading_to_steer_to_destination_ref)
	NMEA_GETTER(mode_indicator)

	void set_loran_c_blink_warning(char t) { loran_c_blink_warning = t; }
	void set_loran_c_cycle_lock_warning(char t) { loran_c_cycle_lock_warning = t; }
	void set_cross_track_error_magnitude(double t) { cross_track_error_magnitude = t; }
	void set_direction_to_steer(side t) { direction_to_steer = t; }
	void set_cross_track_unit(char t) { cross_track_unit = t; }
	void set_status_arrival(char t) { status_arrival = t; }
	void set_status_perpendicular_passing(char t) { status_perpendicular_passing = t; }
	void set_bearing_origin_to_destination(uint32_t t, char ref)
	{
		bearing_origin_to_destination = t;
		bearing_origin_to_destination_ref = ref;
	}
	void set_waypoint_id(const std::string & id);
	void set_bearing_pos_to_destination(uint32_t t, char ref)
	{
		bearing_pos_to_destination = t;
		bearing_pos_to_destination_ref = ref;
	}
	void set_heading_to_steer_to_destination(uint32_t t, char ref)
	{
		heading_to_steer_to_destination = t;
		heading_to_steer_to_destination_ref = ref;
	}
};
}
}

#endif
