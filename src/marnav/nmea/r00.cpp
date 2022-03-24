#include <marnav/nmea/r00.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id r00::ID;
constexpr const char * r00::TAG;
constexpr int r00::max_waypoint_ids;

r00::r00()
	: sentence(ID, TAG, talker::global_positioning_system)
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

void r00::append_data_to(std::string & s, const version &) const
{
	for (auto i = 0; i < max_waypoint_ids; ++i) {
		if (waypoint_id_[i]) {
			append(s, waypoint_id_[i].value());
		} else {
			append(s, "");
		}
	}
}

void r00::check_index(int index) const
{
	if ((index < 0) || (index >= max_waypoint_ids))
		throw std::out_of_range{"waypoint ID out of range"};
}

std::optional<waypoint> r00::get_waypoint_id(int index) const
{
	check_index(index);
	return waypoint_id_[index];
}

void r00::set_waypoint_id(int index, const waypoint & id)
{
	check_index(index);
	waypoint_id_[index] = id;
}
}
}
