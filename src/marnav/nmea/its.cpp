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

its::its(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in its"};

	read(*(first + 0), distance);
	read(*(first + 1), distance_unit);
}

std::unique_ptr<sentence> its::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<its>(new its(talker, first, last));
}

std::vector<std::string> its::get_data() const
{
	return {to_string(distance), to_string(distance_unit)};
}
}
}
