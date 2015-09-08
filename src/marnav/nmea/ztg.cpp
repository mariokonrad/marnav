#include "ztg.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * ztg::TAG;

ztg::ztg()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

void ztg::set_waypoint_id(const std::string & id)
{
	check_waypoint_id(id);
	waypoint_id = id;
}

std::unique_ptr<sentence> ztg::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 3)
		throw std::invalid_argument{"invalid number of fields in ztg::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<ztg>();
	result->set_talker(talker);
	ztg & detail = static_cast<ztg &>(*result);

	read(fields[0], detail.time_utc);
	read(fields[0], detail.time_remaining);
	read(fields[0], detail.waypoint_id);

	return result;
}

std::vector<std::string> ztg::get_data() const
{
	return {to_string(time_utc), to_string(time_remaining), to_string(waypoint_id)};
}
}
}
