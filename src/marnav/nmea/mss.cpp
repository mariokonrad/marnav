#include <marnav/nmea/mss.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id mss::ID;
constexpr const char * mss::TAG;

mss::mss()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

mss::mss(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in mss"};

	read(*(first + 0), signal_strength_);
	read(*(first + 1), signal_to_noise_ratio_);
	read(*(first + 2), beacon_frequency_);
	read(*(first + 3), beacon_datarate_);
	read(*(first + 4), unknown_);
}

void mss::append_data_to(std::string & s, const version &) const
{
	append(s, format(signal_strength_, 2));
	append(s, format(signal_to_noise_ratio_, 2));
	append(s, format(beacon_frequency_, 3));
	append(s, format(beacon_datarate_, 3));
	append(s, to_string(unknown_));
}
}
