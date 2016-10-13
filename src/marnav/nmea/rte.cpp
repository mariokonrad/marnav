#include "rte.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(rte)

constexpr const char * rte::TAG;

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

	read(*(first + 0), n_messages);
	read(*(first + 1), message_number);
	read(*(first + 2), message_mode);

	for (auto i = 0; (i < max_waypoints) && (i < (size - 3)); ++i) {
		read(*(first + i + 3), waypoint_id[i]);
	}
}

utils::optional<waypoint> rte::get_waypoint_id(int index) const
{
	if ((index < 0) || (index >= max_waypoints))
		throw std::out_of_range{"get_waypoint_id"};

	return waypoint_id[index];
}

void rte::set_waypoint_id(int index, const waypoint & id)
{
	if ((index < 0) || (index >= max_waypoints))
		throw std::out_of_range{"set_waypoint_id"};

	if (id.size() > 8)
		throw std::invalid_argument{"string size to large, only 8 characters allowed for id"};

	waypoint_id[index] = id;
}

std::vector<std::string> rte::get_data() const
{
	std::vector<std::string> v{
		to_string(n_messages), to_string(message_number), to_string(message_mode)};

	if (n_messages) {
		for (uint32_t i = 0; (i < n_messages) && (i < max_waypoints); ++i) {
			v.push_back(waypoint_id[i].value());
		}
	}

	return v;
}
}
}
