#include <marnav/nmea/ttm.hpp>
#include "checks.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id ttm::ID;
constexpr const char * ttm::TAG;

ttm::ttm()
	: sentence(ID, TAG, talker::global_positioning_system)
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

	read(*(first + 0), target_number_);
	read(*(first + 1), target_distance_);
	read(*(first + 2), bearing_from_ownship_);
	read(*(first + 3), bearing_from_ownship_ref_);
	read(*(first + 4), target_speed_);
	read(*(first + 5), target_course_);
	read(*(first + 6), target_course_ref_);
	read(*(first + 7), distance_cpa_);
	read(*(first + 8), tcpa_);
	read(*(first + 9), unknown_);
	read(*(first + 10), target_name_);
	read(*(first + 11), target_status_);
	read(*(first + 12), reference_target_);
}

void ttm::append_data_to(std::string & s, const version &) const
{
	append(s, format(target_number_, 2));
	append(s, to_string(target_distance_));
	append(s, to_string(bearing_from_ownship_));
	append(s, to_string(bearing_from_ownship_ref_));
	append(s, to_string(target_speed_));
	append(s, to_string(target_course_));
	append(s, to_string(target_course_ref_));
	append(s, to_string(distance_cpa_));
	append(s, to_string(tcpa_));
	append(s, to_string(unknown_));
	append(s, to_string(target_name_));
	append(s, to_string(target_status_));
	append(s, to_string(reference_target_));
}
}
}
