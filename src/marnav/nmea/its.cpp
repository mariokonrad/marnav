#include "its.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * its::TAG;

its::its()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, distance(0.0)
	, distance_unit(unit::distance::meter)
{
}

std::unique_ptr<sentence> its::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in its::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<its>();
	result->set_talker(talker);
	its & detail = static_cast<its &>(*result);

	read(*(first + 0), detail.distance);
	read(*(first + 1), detail.distance_unit);

	return result;
}

std::vector<std::string> its::get_data() const
{
	return {to_string(distance), to_string(distance_unit)};
}
}
}
