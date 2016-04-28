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

std::unique_ptr<sentence> ttm::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 13)
		throw std::invalid_argument{"invalid number of fields in ttm::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<ttm>();
	result->set_talker(talker);
	ttm & detail = static_cast<ttm &>(*result);

	read(*(first + 0), detail.target_number);
	read(*(first + 1), detail.target_distance);
	read(*(first + 2), detail.bearing_from_ownship);
	read(*(first + 3), detail.bearing_from_ownship_ref);
	read(*(first + 4), detail.target_speed);
	read(*(first + 5), detail.target_course);
	read(*(first + 6), detail.target_course_ref);
	read(*(first + 7), detail.distance_cpa);
	read(*(first + 8), detail.tcpa);
	read(*(first + 9), detail.unknown);
	read(*(first + 10), detail.target_name);
	read(*(first + 11), detail.target_status);
	read(*(first + 12), detail.reference_target);

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
