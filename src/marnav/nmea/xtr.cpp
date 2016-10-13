#include "xtr.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(xtr)

constexpr const char * xtr::TAG;

xtr::xtr()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

xtr::xtr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in xtr"};

	read(*(first + 0), cross_track_error_magnitude);
	read(*(first + 1), direction_to_steer);
	read(*(first + 2), cross_track_unit);
}

std::vector<std::string> xtr::get_data() const
{
	return {to_string(cross_track_error_magnitude), to_string(direction_to_steer),
		to_string(cross_track_unit)};
}
}
}
