#include "zda.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id zda::ID;
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

	read(*(first + 0), time_utc_);
	read(*(first + 1), day_);
	read(*(first + 2), month_);
	read(*(first + 3), year_);
	read(*(first + 4), local_zone_hours_);
	read(*(first + 5), local_zone_minutes_);
}

void zda::append_data_to(std::string & s) const
{
	append(s, to_string(time_utc_));
	append(s, format(day_, 2));
	append(s, format(month_, 2));
	append(s, format(year_, 4));
	append(s, format(local_zone_hours_, 2));
	append(s, format(local_zone_minutes_, 2));
}
}
}
