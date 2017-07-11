#include "rot.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * rot::TAG;

rot::rot()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

rot::rot(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in rot"};

	read(*(first + 0), deg_per_minute_);
	read(*(first + 1), data_valid_);
}

void rot::append_data_to(std::string & s) const
{
	append(s, format(deg_per_minute_, 1));
	append(s, to_string(data_valid_));
}
}
}
