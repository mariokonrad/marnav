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

	read(*(first + 0), loran_c_blink_warning_);
	read(*(first + 1), loran_c_cycle_lock_warning_);
	read(*(first + 2), cross_track_error_magnitude_);
	read(*(first + 3), direction_to_steer_);
	read(*(first + 4), cross_track_unit_);
	read(*(first + 5), status_arrival_);
	read(*(first + 6), status_perpendicular_passing_);
	read(*(first + 7), bearing_origin_to_destination_);
	read(*(first + 8), bearing_origin_to_destination_ref_);
	read(*(first + 9), waypoint_id_);

	check();
}

void apa::set_bearing_origin_to_destination(double t, reference ref)
{
	check_value(bearing_origin_to_destination_ref_, {reference::TRUE, reference::MAGNETIC},
		"bearing_origin_to_destination_ref");
	bearing_origin_to_destination_ = t;
	bearing_origin_to_destination_ref_ = ref;
}

void apa::check() const
{
	check_status(loran_c_blink_warning_, "loran_c_blink_warning");
	check_status(loran_c_cycle_lock_warning_, "loran_c_cycle_lock_warning");

	check_value(direction_to_steer_, {side::left, side::right}, "direction_to_steer");
	check_value(cross_track_unit_, {unit::distance::nm}, "cross_talk_unit");
	check_status(status_arrival_, "status_arrival");
	check_status(status_perpendicular_passing_, "status_perpendicular_passing");

	if (bearing_origin_to_destination_ && !bearing_origin_to_destination_ref_)
		throw std::invalid_argument{"missing bearing_origin_to_destination_ref"};
	check_value(bearing_origin_to_destination_ref_, {reference::TRUE, reference::MAGNETIC},
		"bearing_origin_to_destination_ref");
}

void apa::append_data_to(std::string & s) const
{
	append(s, to_string(loran_c_blink_warning_));
	append(s, to_string(loran_c_cycle_lock_warning_));
	append(s, format(cross_track_error_magnitude_, 2));
	append(s, to_string(direction_to_steer_));
	append(s, to_string(cross_track_unit_));
	append(s, to_string(status_arrival_));
	append(s, to_string(status_perpendicular_passing_));
	append(s, format(bearing_origin_to_destination_, 1));
	append(s, to_string(bearing_origin_to_destination_ref_));
	append(s, to_string(waypoint_id_));
}
}
}
