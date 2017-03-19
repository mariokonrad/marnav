#include "xte.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * xte::TAG;

xte::xte()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

xte::xte(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto size = std::distance(first, last);
	if ((size < 5) || (size > 6))
		throw std::invalid_argument{"invalid number of fields in xte"};

	read(*(first + 0), status1);
	read(*(first + 1), status2);
	read(*(first + 2), cross_track_error_magnitude);
	read(*(first + 3), direction_to_steer);
	read(*(first + 4), cross_track_unit);

	if (size == 6)
		read(*(first + 5), mode_ind);
}

void xte::append_data_to(std::string & s) const
{
	append(s, to_string(status1));
	append(s, to_string(status2));
	append(s, to_string(cross_track_error_magnitude));
	append(s, to_string(direction_to_steer));
	append(s, to_string(cross_track_unit));
	append(s, to_string(mode_ind));
}
}
}
