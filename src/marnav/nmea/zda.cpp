#include "zda.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * zda::TAG;

zda::zda()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

std::unique_ptr<sentence> zda::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in zda::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<zda>();
	result->set_talker(talker);
	zda & detail = static_cast<zda &>(*result);

	read(*(first + 0), detail.time_utc);
	read(*(first + 1), detail.day);
	read(*(first + 2), detail.month);
	read(*(first + 3), detail.year);
	read(*(first + 4), detail.local_zone_hours);
	read(*(first + 5), detail.local_zone_minutes);

	return result;
}

std::vector<std::string> zda::get_data() const
{
	return {to_string(time_utc), format(day, 2), format(month, 2), format(year, 4),
		format(local_zone_hours, 2), format(local_zone_minutes, 2)};
}
}
}
