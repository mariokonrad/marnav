#include "tpr.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(tpr)

constexpr const char * tpr::TAG;

tpr::tpr()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

tpr::tpr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in tpr"};

	read(*(first + 0), range);
	read(*(first + 1), range_unit);
	read(*(first + 2), bearing);
	// separator omitted intentionally
	read(*(first + 4), depth);
	read(*(first + 5), depth_unit);
}

std::vector<std::string> tpr::get_data() const
{
	return {to_string(range), to_string(range_unit), to_string(bearing), "P", to_string(depth),
		to_string(depth_unit)};
}
}
}
