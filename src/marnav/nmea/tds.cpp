#include "tds.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * tds::TAG;

tds::tds()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, distance(0.0)
	, distance_unit(nmea::unit::distance::meter)
{
}

std::unique_ptr<sentence> tds::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 2)
		throw std::invalid_argument{"invalid number of fields in tds::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<tds>();
	result->set_talker(talker);
	tds & detail = static_cast<tds &>(*result);

	read(*(first + 0), detail.distance);
	read(*(first + 1), detail.distance_unit);

	return result;
}

std::vector<std::string> tds::get_data() const
{
	return {to_string(distance), to_string(distance_unit)};
}
}
}
