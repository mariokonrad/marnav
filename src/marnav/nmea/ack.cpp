#include <marnav/nmea/ack.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id ack::ID;
constexpr const char * ack::TAG;

ack::ack()
	: sentence(ID, TAG, talker::integrated_navigation)
{
}

ack::ack(talker talk)
	: sentence(ID, TAG, talk)
{
}

ack::ack(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 1)
		throw std::invalid_argument{"invalid number of fields in ack"};

	read(*(first + 0), number_);
}

void ack::append_data_to(std::string & s) const
{
	append(s, to_string(number_));
}
}
}