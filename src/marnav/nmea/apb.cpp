#include "apb.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * apb::TAG;

apb::apb()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void apb::set_waypoint_id(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

void apb::set_bearing_origin_to_destination(uint32_t t, reference ref)
{
	check_value(bearing_origin_to_destination_ref, {reference::TRUE, reference::MAGNETIC},
		"bearing_origin_to_destination_ref");
	bearing_origin_to_destination = t;
	bearing_origin_to_destination_ref = ref;
}

void apb::set_bearing_pos_to_destination(uint32_t t, reference ref)
{
	check_value(bearing_pos_to_destination_ref, {reference::TRUE, reference::MAGNETIC},
		"bearing_pos_to_destination_ref");
	bearing_pos_to_destination = t;
	bearing_pos_to_destination_ref = ref;
}

void apb::set_heading_to_steer_to_destination(uint32_t t, reference ref)
{
	check_value(heading_to_steer_to_destination_ref, {reference::TRUE, reference::MAGNETIC},
		"heading_to_steer_to_destination_ref");
	heading_to_steer_to_destination = t;
	heading_to_steer_to_destination_ref = ref;
}

void apb::set_mode_indicator(positioning_system_mode_indicator t)
{
	check_value(t, {positioning_system_mode_indicator::invalid,
					   positioning_system_mode_indicator::autonomous,
					   positioning_system_mode_indicator::differential},
		"mode_indicator");
	mode_indicator = t;
}

void apb::check() const
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

	if (bearing_pos_to_destination && !bearing_pos_to_destination_ref)
		throw std::invalid_argument{"missing bearing_pos_to_destination_ref"};
	check_value(bearing_pos_to_destination_ref, {reference::TRUE, reference::MAGNETIC},
		"bearing_pos_to_destination_ref");

	if (heading_to_steer_to_destination && !heading_to_steer_to_destination_ref)
		throw std::invalid_argument{"missing heading_to_steer_to_destination_ref"};
	check_value(heading_to_steer_to_destination_ref, {reference::TRUE, reference::MAGNETIC},
		"heading_to_steer_to_destination_ref");

	check_value(mode_indicator, {positioning_system_mode_indicator::invalid,
									positioning_system_mode_indicator::autonomous,
									positioning_system_mode_indicator::differential},
		"mode_indicator");
}

std::unique_ptr<sentence> apb::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	const auto size = std::distance(first, last);
	if ((size < 14) || (size > 15))
		throw std::invalid_argument{"invalid number of fields in apb::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<apb>();
	result->set_talker(talker);
	apb & detail = static_cast<apb &>(*result);

	read(*(first + 0), detail.loran_c_blink_warning);
	read(*(first + 1), detail.loran_c_cycle_lock_warning);
	read(*(first + 2), detail.cross_track_error_magnitude);
	read(*(first + 3), detail.direction_to_steer);
	read(*(first + 4), detail.cross_track_unit);
	read(*(first + 5), detail.status_arrival);
	read(*(first + 6), detail.status_perpendicular_passing);
	read(*(first + 7), detail.bearing_origin_to_destination);
	read(*(first + 8), detail.bearing_origin_to_destination_ref);
	read(*(first + 9), detail.waypoint_id);
	read(*(first + 10), detail.bearing_pos_to_destination);
	read(*(first + 11), detail.bearing_pos_to_destination_ref);
	read(*(first + 12), detail.heading_to_steer_to_destination);
	read(*(first + 13), detail.heading_to_steer_to_destination_ref);

	if (size > 14)
		read(*(first + 14), detail.mode_indicator);

	detail.check();

	return result;
}

std::vector<std::string> apb::get_data() const
{
	return {to_string(loran_c_blink_warning), to_string(loran_c_cycle_lock_warning),
		format(cross_track_error_magnitude, 2), to_string(direction_to_steer),
		to_string(cross_track_unit), to_string(status_arrival),
		to_string(status_perpendicular_passing), format(bearing_origin_to_destination, 3),
		to_string(bearing_origin_to_destination_ref), to_string(waypoint_id),
		format(bearing_pos_to_destination, 3), to_string(bearing_pos_to_destination_ref),
		format(heading_to_steer_to_destination, 3),
		to_string(heading_to_steer_to_destination_ref), to_string(mode_indicator)};
}
}
}
