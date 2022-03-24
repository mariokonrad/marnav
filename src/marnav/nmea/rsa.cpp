#include <marnav/nmea/rsa.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id rsa::ID;
constexpr const char * rsa::TAG;

rsa::rsa()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

rsa::rsa(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in rsa"};

	read(*(first + 0), rudder1_);
	read(*(first + 1), rudder1_valid_);
	read(*(first + 2), rudder2_);
	read(*(first + 3), rudder2_valid_);
}

void rsa::set_rudder1(double t) noexcept
{
	rudder1_ = t;
	rudder1_valid_ = status::ok;
}

void rsa::set_rudder2(double t) noexcept
{
	rudder2_ = t;
	rudder2_valid_ = status::ok;
}

void rsa::append_data_to(std::string & s, const version &) const
{
	append(s, format(rudder1_, 1));
	append(s, to_string(rudder1_valid_));
	append(s, format(rudder2_, 1));
	append(s, to_string(rudder2_valid_));
}
}
}
