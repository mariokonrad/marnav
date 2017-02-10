#include "stn.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * stn::TAG;

stn::stn()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

stn::stn(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 1)
		throw std::invalid_argument{"invalid number of fields in stn"};

	read(*(first + 0), number);
}

std::vector<std::string> stn::get_data() const
{
	return {to_string(number)};
}
}
}
