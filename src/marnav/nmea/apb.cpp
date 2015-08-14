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

void apb::set_bearing_origin_to_destination(uint32_t t, reference ref) throw(
	std::invalid_argument)
{
	check_value(bearing_origin_to_destination_ref, {reference::TRUE, reference::MAGNETIC},
		"bearing_origin_to_destination_ref");
	bearing_origin_to_destination = t;
	bearing_origin_to_destination_ref = ref;
}

void apb::set_bearing_pos_to_destination(uint32_t t, reference ref) throw(std::invalid_argument)
{
	check_value(bearing_pos_to_destination_ref, {reference::TRUE, reference::MAGNETIC},
		"bearing_pos_to_destination_ref");
	bearing_pos_to_destination = t;
	bearing_pos_to_destination_ref = ref;
}

void apb::set_heading_to_steer_to_destination(uint32_t t, reference ref) throw(
	std::invalid_argument)
{
	check_value(heading_to_steer_to_destination_ref, {reference::TRUE, reference::MAGNETIC},
		"heading_to_steer_to_destination_ref");
	heading_to_steer_to_destination = t;
	heading_to_steer_to_destination_ref = ref;
}

void apb::set_mode_indicator(positioning_system_mode_indicator t) throw(std::invalid_argument)
{
	check_value(t, {positioning_system_mode_indicator::INVALID,
					   positioning_system_mode_indicator::AUTONOMOUS,
					   positioning_system_mode_indicator::DIFFERENTIAL},
		"mode_indicator");
	mode_indicator = t;
}

void apb::check() const throw(std::invalid_argument)
{
	check_status(loran_c_blink_warning, "loran_c_blink_warning");
	check_status(loran_c_cycle_lock_warning, "loran_c_cycle_lock_warning");

	check_value(direction_to_steer, {side::LEFT, side::RIGHT}, "direction_to_steer");
	check_value(cross_track_unit, {unit::distance::NM}, "cross_talk_unit");
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

	check_value(mode_indicator, {positioning_system_mode_indicator::INVALID,
									positioning_system_mode_indicator::AUTONOMOUS,
									positioning_system_mode_indicator::DIFFERENTIAL},
		"mode_indicator");
}

std::unique_ptr<sentence> apb::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if ((fields.size() < 14) || (fields.size() > 15))
		throw std::invalid_argument{"invalid number of fields in apb::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<apb>();
	result->set_talker(talker);
	apb & detail = static_cast<apb &>(*result);

	read(fields[0], detail.loran_c_blink_warning);
	read(fields[1], detail.loran_c_cycle_lock_warning);
	read(fields[2], detail.cross_track_error_magnitude);
	read(fields[3], detail.direction_to_steer);
	read(fields[4], detail.cross_track_unit);
	read(fields[5], detail.status_arrival);
	read(fields[6], detail.status_perpendicular_passing);
	read(fields[7], detail.bearing_origin_to_destination);
	read(fields[8], detail.bearing_origin_to_destination_ref);
	read(fields[9], detail.waypoint_id);
	read(fields[10], detail.bearing_pos_to_destination);
	read(fields[11], detail.bearing_pos_to_destination_ref);
	read(fields[12], detail.heading_to_steer_to_destination);
	read(fields[13], detail.heading_to_steer_to_destination_ref);

	if (fields.size() > 14)
		read(fields[14], detail.mode_indicator);

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
