#include "ttm.hpp"

#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(ttm)

constexpr const char * ttm::TAG;

ttm::ttm()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

ttm::ttm(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 13)
		throw std::invalid_argument{"invalid number of fields in ttm"};

	read(*(first + 0), target_number);
	read(*(first + 1), target_distance);
	read(*(first + 2), bearing_from_ownship);
	read(*(first + 3), bearing_from_ownship_ref);
	read(*(first + 4), target_speed);
	read(*(first + 5), target_course);
	read(*(first + 6), target_course_ref);
	read(*(first + 7), distance_cpa);
	read(*(first + 8), tcpa);
	read(*(first + 9), unknown);
	read(*(first + 10), target_name);
	read(*(first + 11), target_status);
	read(*(first + 12), reference_target);
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
