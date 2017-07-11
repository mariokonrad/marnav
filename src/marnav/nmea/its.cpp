#include "its.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * its::TAG;

its::its()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

its::its(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in its"};

	read(*(first + 0), distance_);
	read(*(first + 1), distance_unit_);
}

void its::append_data_to(std::string & s) const
{
	append(s, to_string(distance_));
	append(s, to_string(distance_unit_));
}
}
}
