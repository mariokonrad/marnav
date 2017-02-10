#include "gbs.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * gbs::TAG;

gbs::gbs()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

gbs::gbs(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in gbs"};

	read(*(first + 0), time_utc);
	read(*(first + 1), err_lat);
	read(*(first + 2), err_lon);
	read(*(first + 3), err_alt);
	read(*(first + 4), satellite);
	read(*(first + 5), probability);
	read(*(first + 6), bias);
	read(*(first + 7), bias_dev);
}

std::vector<std::string> gbs::get_data() const
{
	return {format(time_utc, 2), to_string(err_lat), to_string(err_lon), to_string(err_alt),
		format(satellite, 3), to_string(probability), to_string(bias), to_string(bias_dev)};
}
}
}
