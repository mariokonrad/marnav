#include "tds.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * tds::TAG;

tds::tds()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

tds::tds(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in tds"};

	read(*(first + 0), distance);
	read(*(first + 1), distance_unit);
}

std::vector<std::string> tds::get_data() const
{
	return {to_string(distance), to_string(distance_unit)};
}
}
}
