#include "rsa.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * rsa::TAG;

rsa::rsa()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
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

std::unique_ptr<sentence> rsa::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in rsa::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rsa>();
	result->set_talker(talker);
	rsa & detail = static_cast<rsa &>(*result);

	read(*(first + 0), detail.rudder1);
	read(*(first + 1), detail.rudder1_valid);
	read(*(first + 2), detail.rudder2);
	read(*(first + 3), detail.rudder2_valid);

	return result;
}

std::vector<std::string> rsa::get_data() const
{
	return {format(rudder1, 1), to_string(rudder1_valid), format(rudder2, 1),
		to_string(rudder2_valid)};
}
}
}
