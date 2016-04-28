#include "tpt.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * tpt::TAG;

tpt::tpt()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, range(0.0)
	, range_unit(unit::distance::meter)
	, bearing(0.0)
	, depth(0.0)
	, depth_unit(unit::distance::meter)
{
}

std::unique_ptr<sentence> tpt::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in tpt::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<tpt>();
	result->set_talker(talker);
	tpt & detail = static_cast<tpt &>(*result);

	read(*(first + 0), detail.range);
	read(*(first + 1), detail.range_unit);
	read(*(first + 2), detail.bearing);
	// separator omitted intentionally
	read(*(first + 4), detail.depth);
	read(*(first + 5), detail.depth_unit);

	return result;
}

std::vector<std::string> tpt::get_data() const
{
	return {to_string(range), to_string(range_unit), to_string(bearing), "P", to_string(depth),
		to_string(depth_unit)};
}
}
}
