#include "rsa.hpp"
#include "io.hpp"
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

void rsa::set_rudder1(double t)
{
	rudder1 = t;
	rudder1_valid = status::OK;
}

void rsa::set_rudder2(double t)
{
	rudder2 = t;
	rudder2_valid = status::OK;
}

std::unique_ptr<sentence> rsa::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 4)
		throw std::invalid_argument{"invalid number of fields in rsa::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rsa>();
	result->set_talker(talker);
	rsa & detail = static_cast<rsa &>(*result);

	read(fields[0], detail.rudder1);
	read(fields[1], detail.rudder1_valid);
	read(fields[2], detail.rudder2);
	read(fields[3], detail.rudder2_valid);

	return result;
}

std::vector<std::string> rsa::get_data() const
{
	return {format(rudder1, 1), to_string(rudder1_valid), format(rudder2, 1),
		to_string(rudder2_valid)};
}
}
}

