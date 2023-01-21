#include <marnav/nmea/zfi.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id zfi::ID;
constexpr const char * zfi::TAG;

zfi::zfi()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

zfi::zfi(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in zfi"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), time_elapsed_);
	read(*(first + 2), waypoint_id_);
}

void zfi::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(time_elapsed_));
	append(s, to_string(waypoint_id_));
}
}
