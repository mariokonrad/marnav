#include "r00.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * r00::TAG;

r00::r00()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

r00::r00(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != r00::max_waypoint_ids)
		throw std::invalid_argument{"invalid number of fields in r00"};

	for (auto i = 0; i < max_waypoint_ids; ++i) {
		waypoint id;
		read(*(first + i), id);
		set_waypoint_id(i, id);
	}
}

std::vector<std::string> r00::get_data() const
{
	std::vector<std::string> result;
	result.reserve(max_waypoint_ids);

	for (auto i = 0; i < max_waypoint_ids; ++i) {
		if (waypoint_id[i]) {
			result.push_back(waypoint_id[i].value());
		} else {
			result.push_back("");
		}
	}

	return result;
}

void r00::check_index(int index) const
{
	if ((index < 0) || (index >= max_waypoint_ids))
		throw std::out_of_range{"waypoint ID out of range"};
}

utils::optional<waypoint> r00::get_waypoint_id(int index) const
{
	check_index(index);
	return waypoint_id[index];
}

void r00::set_waypoint_id(int index, const waypoint & id)
{
	check_index(index);
	waypoint_id[index] = id;
}
}
}
