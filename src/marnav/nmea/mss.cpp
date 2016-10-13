#include "mss.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(mss)

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

std::vector<std::string> mss::get_data() const
{
	return {format(signal_strength, 2), format(signal_to_noise_ratio, 2),
		format(beacon_frequency, 3), format(beacon_datarate, 3), to_string(unknown)};
}
}
}
