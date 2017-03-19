#include "xtr.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
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

void xtr::append_data_to(std::string & s) const
{
	append(s, to_string(cross_track_error_magnitude));
	append(s, to_string(direction_to_steer));
	append(s, to_string(cross_track_unit));
}
}
}
