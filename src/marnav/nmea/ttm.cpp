#include "ttm.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * ttm::TAG;

ttm::ttm()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

ttm::ttm(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	// according to http://catb.org/gpsd/NMEA.html#_ttm_tracked_target_message
	// there are fields 14 and 15, but not supported by this implementation.

	const auto dist = std::distance(first, last);

	if ((dist < 13) || (dist > 15))
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

void ttm::append_data_to(std::string & s) const
{
	append(s, format(target_number, 2));
	append(s, to_string(target_distance));
	append(s, to_string(bearing_from_ownship));
	append(s, to_string(bearing_from_ownship_ref));
	append(s, to_string(target_speed));
	append(s, to_string(target_course));
	append(s, to_string(target_course_ref));
	append(s, to_string(distance_cpa));
	append(s, to_string(tcpa));
	append(s, to_string(unknown));
	append(s, to_string(target_name));
	append(s, to_string(target_status));
	append(s, to_string(reference_target));
}
}
}
