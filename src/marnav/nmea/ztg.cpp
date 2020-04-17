#include <marnav/nmea/ztg.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id ztg::ID;
constexpr const char * ztg::TAG;

ztg::ztg()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

ztg::ztg(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in ztg"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), time_remaining_);
	read(*(first + 2), waypoint_id_);
}

void ztg::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(time_remaining_));
	append(s, to_string(waypoint_id_));
}
}
}
