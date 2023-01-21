#include <marnav/nmea/apb.hpp>
#include "checks.hpp"
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id apb::ID;
constexpr const char * apb::TAG;

apb::apb()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

apb::apb(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto size = std::distance(first, last);
	if ((size < 14) || (size > 15))
		throw std::invalid_argument{"invalid number of fields in apb"};

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
	read(*(first + 10), bearing_pos_to_destination_);
	read(*(first + 11), bearing_pos_to_destination_ref_);
	read(*(first + 12), heading_to_steer_to_destination_);
	read(*(first + 13), heading_to_steer_to_destination_ref_);

	if (size > 14)
		read(*(first + 14), mode_ind_);

	check();
}

void apb::set_bearing_origin_to_destination(double t, reference ref)
{
	check_value(bearing_origin_to_destination_ref_, {reference::TRUE, reference::MAGNETIC},
		"bearing_origin_to_destination_ref");
	bearing_origin_to_destination_ = t;
	bearing_origin_to_destination_ref_ = ref;
}

void apb::set_bearing_pos_to_destination(double t, reference ref)
{
	check_value(bearing_pos_to_destination_ref_, {reference::TRUE, reference::MAGNETIC},
		"bearing_pos_to_destination_ref");
	bearing_pos_to_destination_ = t;
	bearing_pos_to_destination_ref_ = ref;
}

void apb::set_heading_to_steer_to_destination(double t, reference ref)
{
	check_value(heading_to_steer_to_destination_ref_, {reference::TRUE, reference::MAGNETIC},
		"heading_to_steer_to_destination_ref");
	heading_to_steer_to_destination_ = t;
	heading_to_steer_to_destination_ref_ = ref;
}

void apb::set_mode_indicator(mode_indicator t)
{
	check_value(t,
		{mode_indicator::invalid, mode_indicator::autonomous, mode_indicator::differential},
		"mode_indicator");
	mode_ind_ = t;
}

void apb::check() const
{
	check_status(loran_c_blink_warning_, "loran_c_blink_warning");
	check_status(loran_c_cycle_lock_warning_, "loran_c_cycle_lock_warning");

	check_value(direction_to_steer_, {side::left, side::right}, "direction_to_steer");
	check_value(cross_track_unit_, {unit::distance::nm, unit::distance::km}, "cross_talk_unit");
	check_status(status_arrival_, "status_arrival");
	check_status(status_perpendicular_passing_, "status_perpendicular_passing");

	if (bearing_origin_to_destination_ && !bearing_origin_to_destination_ref_)
		throw std::invalid_argument{"missing bearing_origin_to_destination_ref"};
	check_value(bearing_origin_to_destination_ref_, {reference::TRUE, reference::MAGNETIC},
		"bearing_origin_to_destination_ref");

	if (bearing_pos_to_destination_ && !bearing_pos_to_destination_ref_)
		throw std::invalid_argument{"missing bearing_pos_to_destination_ref"};
	check_value(bearing_pos_to_destination_ref_, {reference::TRUE, reference::MAGNETIC},
		"bearing_pos_to_destination_ref");

	if (heading_to_steer_to_destination_ && !heading_to_steer_to_destination_ref_)
		throw std::invalid_argument{"missing heading_to_steer_to_destination_ref"};
	check_value(heading_to_steer_to_destination_ref_, {reference::TRUE, reference::MAGNETIC},
		"heading_to_steer_to_destination_ref");

	check_value(mode_ind_,
		{mode_indicator::invalid, mode_indicator::autonomous, mode_indicator::differential},
		"mode_indicator");
}

void apb::append_data_to(std::string & s, const version &) const
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
	append(s, format(bearing_pos_to_destination_, 1));
	append(s, to_string(bearing_pos_to_destination_ref_));
	append(s, format(heading_to_steer_to_destination_, 1));
	append(s, to_string(heading_to_steer_to_destination_ref_));
	append(s, to_string(mode_ind_));
}
}
