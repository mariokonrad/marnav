#include "xte.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * xte::TAG;

xte::xte()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

std::unique_ptr<sentence> xte::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	const auto size = std::distance(first, last);
	if ((size < 5) || (size > 6))
		throw std::invalid_argument{"invalid number of fields in xte::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<xte>();
	result->set_talker(talker);
	xte & detail = static_cast<xte &>(*result);

	read(*(first + 0), detail.status1);
	read(*(first + 1), detail.status2);
	read(*(first + 2), detail.cross_track_error_magnitude);
	read(*(first + 3), detail.direction_to_steer);
	read(*(first + 4), detail.cross_track_unit);

	if (size == 6)
		read(*(first + 5), detail.mode_indicator);

	return result;
}

std::vector<std::string> xte::get_data() const
{
	return {to_string(status1), to_string(status2), to_string(cross_track_error_magnitude),
		to_string(direction_to_steer), to_string(cross_track_unit), to_string(mode_indicator)};
}
}
}
