#include <marnav/nmea/fsi.hpp>
#include "checks.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id fsi::ID;
constexpr const char * fsi::TAG;

fsi::fsi()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

fsi::fsi(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in fsi"};

	read(*(first + 0), tx_frequency_);
	read(*(first + 1), rx_frequency_);
	read(*(first + 2), communications_mode_);
	read(*(first + 3), power_level_);
	read(*(first + 4), sentence_status_);
}

void fsi::set_power_level(uint32_t t)
{
	if (t > 9)
		throw std::invalid_argument{"invalid value for power_level (0..9)"};
	power_level_ = t;
}

void fsi::set_sentence_status(char t)
{
	check_value(t, {'R', 'C'}, "sentence_status");
	sentence_status_ = t;
}

void fsi::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(tx_frequency_));
	append(s, to_string(rx_frequency_));
	append(s, to_string(communications_mode_));
	append(s, to_string(power_level_));
	append(s, to_string(sentence_status_));
}
}
}
