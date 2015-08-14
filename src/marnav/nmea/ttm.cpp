#include "ttm.hpp"

#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * ttm::TAG;

ttm::ttm()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

std::unique_ptr<sentence> ttm::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if (fields.size() != 13)
		throw std::invalid_argument{"invalid number of fields in ttm::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<ttm>();
	result->set_talker(talker);
	ttm & detail = static_cast<ttm &>(*result);

	read(fields[0], detail.target_number);
	read(fields[1], detail.target_distance);
	read(fields[2], detail.bearing_from_ownship);
	read(fields[3], detail.bearing_from_ownship_ref);
	read(fields[4], detail.target_speed);
	read(fields[5], detail.target_course);
	read(fields[6], detail.target_course_ref);
	read(fields[7], detail.distance_cpa);
	read(fields[8], detail.tcpa);
	read(fields[9], detail.unknown);
	read(fields[10], detail.target_name);
	read(fields[11], detail.target_status);
	read(fields[12], detail.reference_target);

	return result;
}

std::vector<std::string> ttm::get_data() const
{
	return {format(target_number, 2), to_string(target_distance),
		to_string(bearing_from_ownship), to_string(bearing_from_ownship_ref),
		to_string(target_speed), to_string(target_course), to_string(target_course_ref),
		to_string(distance_cpa), to_string(tcpa), to_string(unknown), to_string(target_name),
		to_string(target_status), to_string(reference_target)};
}
}
}
