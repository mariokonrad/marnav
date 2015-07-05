#include "apb.hpp"
#include "io.hpp"
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

std::unique_ptr<sentence> apb::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 14)
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
		to_string(heading_to_steer_to_destination_ref)};
}
}
}
