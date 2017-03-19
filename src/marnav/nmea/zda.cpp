#include "zda.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * zda::TAG;

zda::zda()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

zda::zda(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in zda"};

	read(*(first + 0), time_utc);
	read(*(first + 1), day);
	read(*(first + 2), month);
	read(*(first + 3), year);
	read(*(first + 4), local_zone_hours);
	read(*(first + 5), local_zone_minutes);
}

void zda::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc));
	append(s, format(day, 2));
	append(s, format(month, 2));
	append(s, format(year, 4));
	append(s, format(local_zone_hours, 2));
	append(s, format(local_zone_minutes, 2));
}
}
}
