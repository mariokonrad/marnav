#include <marnav/nmea/zta.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id zta::ID;
constexpr const char * zta::TAG;

zta::zta()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

zta::zta(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in zta"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), time_arrival_);
	read(*(first + 2), waypoint_id_);
}

void zta::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(time_arrival_));
	append(s, to_string(waypoint_id_));
}
}
}
