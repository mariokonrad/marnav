#include "zda.hpp"
#include "io.hpp"
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

std::unique_ptr<sentence> zda::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in zda::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<zda>();
	result->set_talker(talker);
	zda & detail = static_cast<zda &>(*result);

	read(fields[0], detail.time_utc);
	read(fields[0], detail.day);
	read(fields[0], detail.month);
	read(fields[0], detail.year);
	read(fields[0], detail.local_zone_hours);
	read(fields[0], detail.local_zone_minutes);

	return result;
}

std::vector<std::string> zda::get_data() const
{
	return {to_string(time_utc), format(day, 2), format(month, 2), format(year, 4),
		format(local_zone_hours, 2), format(local_zone_minutes, 2)};
}
}
}
