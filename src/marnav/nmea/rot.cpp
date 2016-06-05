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

rot::rot(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in rot"};

	read(*(first + 0), deg_per_minute);
	read(*(first + 1), data_valid);
}

std::unique_ptr<sentence> rot::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<rot>(new rot(talker, first, last));
}

std::vector<std::string> rot::get_data() const
{
	return {format(deg_per_minute, 1), to_string(data_valid)};
}
}
}
