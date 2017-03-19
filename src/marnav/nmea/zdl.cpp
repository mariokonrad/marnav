#include "zdl.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * zdl::TAG;

zdl::zdl()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

zdl::zdl(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in zdl"};

	read(*(first + 0), time_to_point);
	read(*(first + 1), distance);
	read(*(first + 2), type_point);
}

void zdl::append_data_to(std::string & s) const
{
	append(s, to_string(time_to_point));
	append(s, format(distance, 1));
	append(s, to_string(type_point));
}
}
}
