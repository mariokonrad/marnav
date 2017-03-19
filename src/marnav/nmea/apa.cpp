#include "apa.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * apa::TAG;

apa::apa()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

apa::apa(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 10)
		throw std::invalid_argument{"invalid number of fields in apa"};

	read(*(first + 0), loran_c_blink_warning);
	read(*(first + 1), loran_c_cycle_lock_warning);
	read(*(first + 2), cross_track_error_magnitude);
	read(*(first + 3), direction_to_steer);
	read(*(first + 4), cross_track_unit);
	read(*(first + 5), status_arrival);
	read(*(first + 6), status_perpendicular_passing);
	read(*(first + 7), bearing_origin_to_destination);
	read(*(first + 8), bearing_origin_to_destination_ref);
	read(*(first + 9), waypoint_id);

	check();
}

void apa::set_bearing_origin_to_destination(double t, reference ref)
{
	check_value(bearing_origin_to_destination_ref, {reference::TRUE, reference::MAGNETIC},
		"bearing_origin_to_destination_ref");
	bearing_origin_to_destination = t;
	bearing_origin_to_destination_ref = ref;
}

void apa::check() const
{
	check_status(loran_c_blink_warning, "loran_c_blink_warning");
	check_status(loran_c_cycle_lock_warning, "loran_c_cycle_lock_warning");

	check_value(direction_to_steer, {side::left, side::right}, "direction_to_steer");
	check_value(cross_track_unit, {unit::distance::nm}, "cross_talk_unit");
	check_status(status_arrival, "status_arrival");
	check_status(status_perpendicular_passing, "status_perpendicular_passing");

	if (bearing_origin_to_destination && !bearing_origin_to_destination_ref)
		throw std::invalid_argument{"missing bearing_origin_to_destination_ref"};
	check_value(bearing_origin_to_destination_ref, {reference::TRUE, reference::MAGNETIC},
		"bearing_origin_to_destination_ref");
}

void apa::append_data_to(std::string & s) const
{
	append(s, to_string(loran_c_blink_warning));
	append(s, to_string(loran_c_cycle_lock_warning));
	append(s, format(cross_track_error_magnitude, 2));
	append(s, to_string(direction_to_steer));
	append(s, to_string(cross_track_unit));
	append(s, to_string(status_arrival));
	append(s, to_string(status_perpendicular_passing));
	append(s, format(bearing_origin_to_destination, 1));
	append(s, to_string(bearing_origin_to_destination_ref));
	append(s, to_string(waypoint_id));
}
}
}
