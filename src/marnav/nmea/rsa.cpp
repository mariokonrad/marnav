#include "rsa.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(rsa)

constexpr const char * rsa::TAG;

rsa::rsa()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

rsa::rsa(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in rsa"};

	read(*(first + 0), rudder1);
	read(*(first + 1), rudder1_valid);
	read(*(first + 2), rudder2);
	read(*(first + 3), rudder2_valid);
}

void rsa::set_rudder1(double t) noexcept
{
	rudder1 = t;
	rudder1_valid = status::ok;
}

void rsa::set_rudder2(double t) noexcept
{
	rudder2 = t;
	rudder2_valid = status::ok;
}

std::vector<std::string> rsa::get_data() const
{
	return {format(rudder1, 1), to_string(rudder1_valid), format(rudder2, 1),
		to_string(rudder2_valid)};
}
}
}
