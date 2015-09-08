#include "tpr.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * tpr::TAG;

tpr::tpr()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, range(0.0)
	, range_unit(unit::distance::METER)
	, bearing(0.0)
	, depth(0.0)
	, depth_unit(unit::distance::METER)
{
}

std::unique_ptr<sentence> tpr::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in tpr::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<tpr>();
	result->set_talker(talker);
	tpr & detail = static_cast<tpr &>(*result);

	read(fields[0], detail.range);
	read(fields[1], detail.range_unit);
	read(fields[2], detail.bearing);
	// separator omitted intentionally
	read(fields[4], detail.depth);
	read(fields[5], detail.depth_unit);

	return result;
}

std::vector<std::string> tpr::get_data() const
{
	return {to_string(range), to_string(range_unit), to_string(bearing), "P", to_string(depth),
		to_string(depth_unit)};
}
}
}
