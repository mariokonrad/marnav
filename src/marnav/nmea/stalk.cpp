#include "stalk.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/seatalk/seatalk.hpp>


namespace marnav
{
namespace nmea
{
constexpr sentence_id stalk::ID;
constexpr const char * stalk::TAG;

stalk::stalk()
	: sentence(ID, TAG, talker_id::none)
{
}

stalk::stalk(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	seatalk::raw raw_data;
	if (std::distance(first, last) < 1)
		throw std::invalid_argument{"invalid number of fields in alk"};

	for(int i=0;i<std::distance(first, last);i++)
	{
		uint32_t num32;
		uint8_t num8;
		read(*(first + i), num32, data_format::hex);
		num8 = num32;
		raw_data.push_back(num8);
	}
	data_ = raw_data;
}

void stalk::append_data_to(std::string & s) const
{
}
}
}
