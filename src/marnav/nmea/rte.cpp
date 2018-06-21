#include "rte.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id rte::ID;
constexpr const char * rte::TAG;
constexpr int rte::max_waypoints;

rte::rte()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

rte::rte(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto size = std::distance(first, last);
	if ((size < 3) || (size > max_waypoints + 3))
		throw std::invalid_argument{"invalid number of fields in rte"};

	read(*(first + 0), n_messages_);
	read(*(first + 1), message_number_);
	read(*(first + 2), message_mode_);

	for (auto i = 0; (i < max_waypoints) && (i < (size - 3)); ++i) {
		read(*(first + i + 3), waypoint_id_[i]);
	}
}

utils::optional<waypoint> rte::get_waypoint_id(int index) const
{
	if ((index < 0) || (index >= max_waypoints))
		throw std::out_of_range{"get_waypoint_id"};

	return waypoint_id_[index];
}

void rte::set_waypoint_id(int index, const waypoint & id)
{
	if ((index < 0) || (index >= max_waypoints))
		throw std::out_of_range{"set_waypoint_id"};

	if (id.size() > 8)
		throw std::invalid_argument{"string size to large, only 8 characters allowed for id"};

	waypoint_id_[index] = id;
}

void rte::append_data_to(std::string & s) const
{
	append(s, to_string(n_messages_));
	append(s, to_string(message_number_));
	append(s, to_string(message_mode_));

	if (n_messages_) {
		for (uint32_t i = 0; (i < n_messages_) && (i < max_waypoints); ++i) {
			append(s, waypoint_id_[i].value());
		}
	}
}
}
}
