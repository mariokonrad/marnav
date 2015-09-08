#include "hfb.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * hfb::TAG;

hfb::hfb()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, distance_head_foot(0.0)
	, distance_head_foot_unit(unit::distance::METER)
	, distance_head_bottom(0.0)
	, distance_head_bottom_unit(unit::distance::METER)
{
}

std::unique_ptr<sentence> hfb::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 4)
		throw std::invalid_argument{"invalid number of fields in hfb::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<hfb>();
	result->set_talker(talker);
	hfb & detail = static_cast<hfb &>(*result);

	read(fields[0], detail.distance_head_foot);
	read(fields[1], detail.distance_head_foot_unit);
	read(fields[2], detail.distance_head_bottom);
	read(fields[3], detail.distance_head_bottom_unit);

	return result;
}

std::vector<std::string> hfb::get_data() const
{
	return {to_string(distance_head_foot), to_string(distance_head_foot_unit),
		to_string(distance_head_bottom), to_string(distance_head_bottom_unit)};
}
}
}
