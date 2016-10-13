#include "zda.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(zda)

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

std::vector<std::string> zda::get_data() const
{
	return {to_string(time_utc), format(day, 2), format(month, 2), format(year, 4),
		format(local_zone_hours, 2), format(local_zone_minutes, 2)};
}
}
}
