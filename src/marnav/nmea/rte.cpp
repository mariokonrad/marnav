#include "rte.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

rte::rte()
	: sentence(ID, "RTE", talker_id::global_positioning_system)
{
}

utils::optional<std::string> rte::get_waypoint_id(int index) const
{
	if ((index < 0)
		|| (index >= static_cast<int>((sizeof(waypoint_id) / sizeof(waypoint_id[0])))))
		throw std::out_of_range{"get_waypoint_id"};

	return waypoint_id[index];
}

void rte::set_waypoint_id(int index, const std::string & id)
{
	if ((index < 0)
		|| (index >= static_cast<int>((sizeof(waypoint_id) / sizeof(waypoint_id[0])))))
		throw std::out_of_range{"set_waypoint_id"};

	if (id.size() > 8)
		throw std::invalid_argument{"string size to large, only 8 characters allowed for id"};

	waypoint_id[index] = id;
}

std::unique_ptr<sentence> rte::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if ((fields.size() < 3) || (fields.size() > 13))
		throw std::invalid_argument{"invalid number of fields in rte::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rte>();
	result->set_talker(talker);
	rte & detail = static_cast<rte &>(*result);

	read(fields[0], detail.n_messages);
	read(fields[1], detail.message_number);
	read(fields[2], detail.message_mode);

	for (size_t i = 3; i < 10 && i < fields.size(); ++i) {
		read(fields[i], detail.waypoint_id[i - 3]);
	}

	return result;
}

std::vector<std::string> rte::get_data() const
{
	std::vector<std::string> v{
		to_string(n_messages), to_string(message_number), to_string(message_mode)};

	if (n_messages) {
		const auto n = n_messages.value();
		for (uint32_t i = 0; i < n; ++i) {
			v.push_back(waypoint_id[i].value());
		}
	}

	return v;
}
}
}
