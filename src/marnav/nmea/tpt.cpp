#include "tpt.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * tpt::TAG;

tpt::tpt()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

tpt::tpt(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in tpt"};

	read(*(first + 0), range);
	read(*(first + 1), range_unit);
	read(*(first + 2), bearing);
	// separator omitted intentionally
	read(*(first + 4), depth);
	read(*(first + 5), depth_unit);
}

std::unique_ptr<sentence> tpt::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<tpt>(new tpt(talker, first, last));
}

std::vector<std::string> tpt::get_data() const
{
	return {to_string(range), to_string(range_unit), to_string(bearing), "P", to_string(depth),
		to_string(depth_unit)};
}
}
}
