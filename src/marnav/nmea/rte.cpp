#include <marnav/nmea/rte.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id rte::ID;
constexpr const char * rte::TAG;
constexpr int rte::max_waypoints;

rte::rte()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

rte::rte(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto size = std::distance(first, last);
	if ((size < 4) || (size > (max_waypoints + 4)))
		throw std::invalid_argument{"invalid number of fields in rte"};

	read(*(first + 0), n_messages_);
	read(*(first + 1), message_number_);
	read(*(first + 2), message_mode_);
	read(*(first + 3), route_id_);

	waypoint_id_.reserve(max_waypoints);
	for (auto i = 0; (i < max_waypoints) && (i < (size - 4)); ++i) {
		std::optional<waypoint> wp;
		read(*(first + i + 4), wp);
		if (wp)
			waypoint_id_.push_back(wp);
	}
}

std::optional<waypoint> rte::get_waypoint_id(int index) const
{
	if (index < 0)
		throw std::out_of_range{"get_waypoint_id"};

	if (index >= get_n_waypoints())
		return {};

	return waypoint_id_[index];
}

int rte::get_n_waypoints() const
{
	return static_cast<int>(waypoint_id_.size());
}

void rte::add_waypoint_id(const waypoint & id)
{
	if (get_n_waypoints() >= max_waypoints)
		throw std::runtime_error{"to many waypoints"};

	waypoint_id_.push_back(id);
}

void rte::clear_waypoint_id()
{
	waypoint_id_.clear();
}

void rte::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(n_messages_));
	append(s, to_string(message_number_));
	append(s, to_string(message_mode_));
	append(s, to_string(route_id_));

	for (const auto & wp : waypoint_id_)
		append(s, wp.value());
}
}
}
