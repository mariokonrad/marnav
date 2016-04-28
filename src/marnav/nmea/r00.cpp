#include "r00.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * r00::TAG;

r00::r00()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

std::unique_ptr<sentence> r00::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != r00::max_waypoint_ids)
		throw std::invalid_argument{"invalid number of fields in r00::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<r00>();
	result->set_talker(talker);
	r00 & detail = static_cast<r00 &>(*result);

	for (auto i = 0; i < max_waypoint_ids; ++i) {
		std::string id;
		read(*(first + i), id);
		detail.set_waypoint_id(i, id);
	}

	return result;
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

utils::optional<std::string> r00::get_waypoint_id(int index) const
{
	check_index(index);
	return waypoint_id[index];
}

void r00::set_waypoint_id(int index, const std::string & id)
{
	check_index(index);
	waypoint_id[index] = id;
}
}
}
