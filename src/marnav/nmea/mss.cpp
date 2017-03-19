#include "mss.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * mss::TAG;

mss::mss()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

mss::mss(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in mss"};

	read(*(first + 0), signal_strength);
	read(*(first + 1), signal_to_noise_ratio);
	read(*(first + 2), beacon_frequency);
	read(*(first + 3), beacon_datarate);
	read(*(first + 4), unknown);
}

void mss::append_data_to(std::string & s) const
{
	append(s, format(signal_strength, 2));
	append(s, format(signal_to_noise_ratio, 2));
	append(s, format(beacon_frequency, 3));
	append(s, format(beacon_datarate, 3));
	append(s, to_string(unknown));
}
}
}
