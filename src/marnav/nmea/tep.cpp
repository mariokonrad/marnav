#include <marnav/nmea/tep.hpp>
#include "checks.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav::nmea
{
constexpr sentence_id tep::ID;
constexpr const char * tep::TAG;

tep::tep()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

tep::tep(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in tep"};

	char degrees;

	read(*(first + 0), elevation_);
	read(*(first + 1), degrees);

	check_value(degrees, {'D'}, "elevation_unit");
}

void tep::append_data_to(std::string & s, const version &) const
{
	append(s, format(elevation_, 1));
	append(s, 'D');
}
}
