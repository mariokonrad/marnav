#include <marnav/nmea/zte.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id zte::ID;
constexpr const char * zte::TAG;

zte::zte()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

zte::zte(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in zte"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), time_remaining_);
	read(*(first + 2), waypoint_id_);
}

void zte::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(time_remaining_));
	append(s, to_string(waypoint_id_));
}
}
}

