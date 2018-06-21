#include "zfo.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id zfo::ID;
constexpr const char * zfo::TAG;

zfo::zfo()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

zfo::zfo(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in zfo"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), time_elapsed_);
	read(*(first + 2), waypoint_id_);
}

void zfo::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(time_elapsed_));
	append(s, to_string(waypoint_id_));
}
}
}
